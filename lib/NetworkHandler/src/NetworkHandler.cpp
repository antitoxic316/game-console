#include <NetworkHandler.h>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "secrets.h"

void NetworkHandler::run(){
  
}


void NetworkHandler::registerObj(std::shared_ptr<Obj> obj, uint16_t flags){
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
      while(msg.startsWith("GAME_STARTED")){
        if(!confirmed){
          udp_.beginPacket("192.168.1.26", netwPort_);
          udp_.write('r');
          udp_.endPacket();
          delay(100);
        }
        unsigned long wait_time = 0;
        unsigned long t = millis();
        int r = -1;
        while(r == -1 || wait_time <= 1000ul){
          r = tcpCli_.peek();
          if(r != -1){
            Serial.println("trying to read server reply :(");
            msg = tcpCli_.readString();
          }
          wait_time = millis() - t;
        }
      }

      gameSessionStatus_ = SESSION_ACTIVE;
  }
}
