#include <NetworkHandler.h>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "secrets.h"

void NetworkHandler::run(){
  
}


void NetworkHandler::registerObj(std::shared_ptr<DynamicObj> obj, uint16_t flags){
  NetworkedObj n_obj = NetworkedObj(obj);

  if(flags & OBJ_CLIENT_CONTROLLED){
    if(WiFi.status() == WL_CONNECTED){
      //send obj data to server
      tcpCli_.println(n_obj.serializeObjInfo().c_str());
    }
    clientControlled_.push_back(n_obj);
  }

  if(flags & OBJ_SERVER_CONTROLLED){
    serverControlled_.push_back(n_obj);
  }
}


void NetworkHandler::syncServer(){
  if(WiFi.status() != WL_CONNECTED){
    return;
  }

  if(gameSessionStatus_ != SESSION_ACTIVE){
    return;
  }

  recvTcpPackets();
  sendTcpPackets();

  recvUdpPackets();
  sendUdpPackets();
}

void NetworkHandler::sendUdpPackets(){
  for(auto &obj: clientControlled_){
    udp_.beginPacket("192.168.1.26", netwPort_);
    udp_.printf("%s\r\n", obj.serializeData().c_str());
    udp_.endPacket();
  }
}


void NetworkHandler::recvUdpPackets(){
  size_t nbuff = 256;
  char *buff = (char *)calloc(nbuff, 1);
  
  int len = udp_.parsePacket();
  if(len){
    int r = udp_.read(buff, 256-1);
  }

  for(auto &obj: serverControlled_){
    obj.handlePacket(buff);
  }

  free(buff);
}

void NetworkHandler::unregisterObj(char *obj_name){
  for(auto it = clientControlled_.begin(); it != clientControlled_.end(); it++){
    NetworkedObj o = *it;
    if(!strcmp(o.getBaseObj()->getName(), obj_name)){
      clientControlled_.erase(it);
      break;
    }
  }

  for(auto it = serverControlled_.begin(); it != serverControlled_.end(); it++){
    NetworkedObj o = *it;
    if(!strcmp(o.getBaseObj()->getName(), obj_name)){
      serverControlled_.erase(it);
      break;
    }
  }
}


void NetworkHandler::WPA2Connect(const char *ssid, const char *pass){
    WiFi.begin(ssid, pass);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
}

void NetworkHandler::gameSyncInit(){
  String msg = "";
  int res;
  IPAddress server(SERVER_IP_EXPR);

  switch (gameSessionStatus_)
  {
    case SESSION_DISCONNECTED:
      Serial.println("initializing tcp socket");
      res = tcpCli_.connect(server, netwPort_);
      if(!res){
        Serial.println("failed to connect to server");
        return;
      }
      Serial.print("tcp socket initialized on port: ");
      Serial.println(netwPort_);  

      gameSessionStatus_ = SESSION_CONNECTED;
      //break; no break intended

    case SESSION_CONNECTED:
      while(msg != "INIT_STARTED"){
        while(!tcpCli_.available()){
          delay(100);
        }

        msg = tcpCli_.readStringUntil('\r');
      }
      gameSessionStatus_ = SESSION_UNITIALIZED;
      //break; no break intended

    case SESSION_UNITIALIZED:
      Serial.println("sending objects");
      for(int i = 0; i < clientControlled_.size(); i++){
        Serial.println(clientControlled_[i].serializeObjInfo().c_str());
        tcpCli_.println(clientControlled_[i].serializeObjInfo().c_str());
      }

      tcpCli_.print("READY\r\n");
      gameSessionStatus_ = SESSION_WAITING_FOR_GAME;
      //break; no break intended

    case SESSION_WAITING_FOR_GAME:
      String buff;

      Serial.println("initializing udp socket");
      udp_.begin(netwPort_);
      Serial.print("udp socket initialized on port: ");
      Serial.println(netwPort_);
      delay(100);

      bool confirmed = false;
      while(!msg.startsWith("GAME_STARTED")){
        if(!confirmed){
          udp_.beginPacket("192.168.1.26", netwPort_);
          udp_.write('r');
          udp_.endPacket();
          delay(100);
        }
    
        Serial.println("trying to read server reply :(");
        msg = tcpCli_.readString();
      }

      gameSessionStatus_ = SESSION_ACTIVE;
  }
}

void NetworkHandler::sendTcpPackets(){
  if(tcpCli_.availableForWrite()){
    for(ObjEvent &ev = netwEvents_.front(); netwEvents_.size() > 0; netwEvents_.pop()){
      tcpCli_.printf(serializeEvent(ev).c_str());
      if(ev.data) free(ev.data);
    }
  }
}

void NetworkHandler::recvTcpPackets(){
  size_t nbuff = 256;
  uint8_t buff[nbuff] = {'\0'};

  int r = 0, i = 0;
  while(r != -1){
    r = tcpCli_.read();
    buff[i++] = r;
    if(i >= nbuff){
      break;
    }
  }

  if(i == nbuff-1){
    Serial.println("buffer overload");
    return;
  }
  handleTcpPacket(buff);
}


void NetworkHandler::handleTcpPacket(uint8_t *buff){
  JsonDocument j;
  DeserializationError err;

  err = deserializeJson(j, buff);

  if(err){
    Serial.println(err.c_str());
    return;
  }

  if(!strcmp(j["type"], "event")){
    if(!j.containsKey("packet")) return;
    JsonObject packet = j["packet"].as<JsonObject>();

    if(!packet.containsKey("ev_name")) return;
    if(!packet.containsKey("ev_data")) return;

    std::string ev_name = packet["ev_name"];
    char *ev_data = strdup(packet["ev_data"]);

    //for now the first server controlled object will just emit all network events
    if(serverControlled_.size() == 0) return;
    if(ev_name == "") return;
    serverControlled_.at(0).getBaseObj()->emitEvent(ev_name, (void*)ev_data);
  }
}

std::string NetworkHandler::serializeEvent(ObjEvent ev){
  JsonDocument j;

  size_t nbuff = 256;
  char buff[nbuff] = {0, };

  j["type"] = "event";
  j["packet"]["ev_name"] = ev.ev_name;
  if(ev.data){
    j["packet"]["ev_data"] = std::string((char*)ev.data);
    free(ev.data);
  } else {
    j["packet"]["ev_data"] = "";
  }

  j["echo"] = true;
  j["server_processed"] = true;

  serializeJson(j, buff, nbuff);

  if(buff[nbuff-1] != '\0'){
    // buffer overflow
    Serial.println("event not parsed: buffer overflow");
    return nullptr;
  }

  return std::string(buff);
} 

void NetworkHandler::duplicateEvent(ObjEvent ev){
  if(ev.data)
    ev.data = (void*)strdup((char*)ev.data);

  netwEvents_.push(ev);
}