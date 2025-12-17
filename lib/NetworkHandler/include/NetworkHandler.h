#pragma once

#include <queue>
#include <memory>

#include "NetworkedObj.h"

#include "Program.h"


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>

enum SESSION_STATUS {
  SESSION_DISCONNECTED,
  SESSION_CONNECTED,
  SESSION_UNITIALIZED,
  SESSION_INITIALIZED,
  SESSION_WAITING_FOR_GAME,
  SESSION_ACTIVE,
};

class NetworkHandler : public Program
{
private:
  unsigned int netwPort_ = 4210;
  WiFiUDP udp_;
  WiFiClient tcpCli_;

  std::vector<NetworkedObj> clientControlled_;
  std::vector<NetworkedObj> serverControlled_;

  SESSION_STATUS gameSessionStatus_;

protected:
  void sendUdpPackets();
  void recvUdpPackets();
public:
  NetworkHandler():
  gameSessionStatus_(SESSION_DISCONNECTED){
  }
  void run() override;
  void syncServer();
  void registerObj(std::shared_ptr<Obj>, uint16_t flags);
  void clearObjects(){
    clientControlled_.clear();
    serverControlled_.clear();
  }
  void unregisterObj(char *obj_name);
  void WPA2Connect(const char *ssid, const char *pass);
  void gameSyncInit();
  SESSION_STATUS getSessionStatus(){
    return gameSessionStatus_;
  }


};