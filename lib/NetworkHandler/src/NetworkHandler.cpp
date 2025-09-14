#include "NetworkHandler.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "secrets.h"

void NetworkHandler::run(){
  
}


void NetworkHandler::registerObj(std::shared_ptr<Obj> obj, uint16_t flags){
  NetworkedObj n_obj = NetworkedObj(obj);

  if(flags & OBJ_CLIENT_CONTROLLED){
    if(WiFi.status() == WL_CONNECTED){
      //send obj data to server
      tcpCli_.println(n_obj.serialize().c_str());
    }
    clientControlled_.push_back(n_obj);
  }

  if(flags & OBJ_SERVER_CONTROLLED){
    if(WiFi.status() == WL_CONNECTED){
      //send obj data to server
      tcpCli_.println(n_obj.serialize().c_str());
    }
    serverControlled_.push_back(n_obj);
  }
}


void NetworkHandler::syncServer(){
  if(serverControlled_.size() < 1){
    return;
  }

  auto o = serverControlled_.at(0);
  InetMsg m;
  o.processPacket(m);
}

void NetworkHandler::unregisterObj(std::string obj_name){
  for(auto it = clientControlled_.begin(); it != clientControlled_.end(); it++){
    NetworkedObj o = *it;
    if(o.getBaseObj()->getName() == obj_name){
      clientControlled_.erase(it);
      break;
    }
  }

  for(auto it = serverControlled_.begin(); it != serverControlled_.end(); it++){
    NetworkedObj o = *it;
    if(o.getBaseObj()->getName() == obj_name){
      serverControlled_.erase(it);
      break;
    }
  }
}


void NetworkHandler::WPA2Connect(const char *ssid, const char *pass){
  WiFi.begin(ssid, pass);
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void NetworkHandler::gameSyncInit(){
  Serial.println("initializing udp socket");
  udp_.begin(netwPort_);
  Serial.print("udp socket initialized on port: ");
  Serial.print(netwPort_);

  Serial.println("initializing tcp socket");
  IPAddress server(SERVER_IP_EXPR);
  int res = tcpCli_.connect(server, netwPort_);
  if(!res){
    Serial.println("failed to connect to server");
    return;
  }
  Serial.print("tcp socket initialized on port: ");
  Serial.print(netwPort_);  

  for(int i = 0; i < clientControlled_.size(); i++){
    Serial.println(clientControlled_[i].serialize().c_str());
    tcpCli_.println(clientControlled_[i].serialize().c_str());
  }
}
