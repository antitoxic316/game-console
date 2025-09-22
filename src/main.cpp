#include <PingPong.h>
#include <DummyGame.h>
#include <MainMenuProgram.h>
#include <ProgramDispatcher.h>
#include <NetworkHandler.h>
#include <WiFiChoser.h>

SoftwareSerial controllerSerial = SoftwareSerial(0, 1);

void setup() {
  GraphEnv graphEnv(128, 64);

  Serial.begin(19200);
  delay(2000);

  uint32_t free_mem;
  
  ProgramDispatcher pd;

  //PingPong game(graphEnv, controllerSerial);
  //Dummygame game2(graphEnv, controllerSerial);
  WiFiChoser wifiprog(graphEnv, controllerSerial);

  Serial.printf("%d    %d\r\n\r", __LINE__, ESP.getFreeHeap());



  //game.init();

  Serial.printf("%d    %d\r\n\r", __LINE__, ESP.getFreeHeap());

  //game2.init();  
  //wifiprog.init();
  
  Serial.printf("%d    %d\r\n\r", __LINE__, ESP.getFreeHeap());


  //pd.registerProgram("pingpong", game.getSaturnPtr());
  //pd.registerProgram("test", game2.getSaturnPtr());
  pd.registerProgram("wifi", wifiprog.getSaturnPtr());
  
  Serial.printf("%d    %d\r\n\r", __LINE__, ESP.getFreeHeap());


  MainMenuProgram mainmenu(graphEnv, controllerSerial, pd);
  
  Serial.printf("%d    %d\r\n\r", __LINE__, ESP.getFreeHeap());

  mainmenu.init();

  Serial.printf("%d    %d\r\n\r", __LINE__, ESP.getFreeHeap());

  mainmenu.start();
}

void loop() {
  Serial.println("inside the main loop");
  delay(50);
}