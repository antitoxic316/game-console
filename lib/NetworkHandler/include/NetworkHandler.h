#pragma once

#include <queue>
#include <list>
#include <memory>

#include "NetworkedObj.h"
#include "DynamicObj.h"
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
  std::queue<ObjEvent, std::list<ObjEvent>> netwEvents_;

  unsigned int netwPort_ = 4210;
  WiFiUDP udp_;
  WiFiClient tcpCli_;

  std::vector<NetworkedObj> clientControlled_;
  std::vector<NetworkedObj> serverControlled_;

  SESSION_STATUS gameSessionStatus_;

protected:
  void sendTcpPackets();
  void recvTcpPackets();
  void sendUdpPackets();
  void recvUdpPackets();
public:
  NetworkHandler():
  gameSessionStatus_(SESSION_DISCONNECTED){
  }
  void run() override;
  void syncServer();
  void registerObj(std::shared_ptr<DynamicObj>, uint16_t flags);
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

  void handleTcpPacket(uint8_t *buff);
  std::string serializeEvent(ObjEvent ev);

  void duplicateEvent(ObjEvent ev);
};