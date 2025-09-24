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
  
  ProgramDispatcher pd;

  //PingPong game(graphEnv, controllerSerial);
  //Dummygame game2(graphEnv, controllerSerial);
  WiFiChoser wifiprog(graphEnv, controllerSerial);

  //game.init();

  //game2.init();  
  wifiprog.init();

  //pd.registerProgram("pingpong", game.getSaturnPtr());
  //pd.registerProgram("test", game2.getSaturnPtr());
  pd.registerProgram("wifi", wifiprog.getSaturnPtr());

  MainMenuProgram mainmenu(graphEnv, controllerSerial, pd);
  mainmenu.init();

  Serial.printf("%d    %d\r\n\r", __LINE__, ESP.getFreeHeap());

  mainmenu.start();
}

void loop() {
  Serial.println("inside the main loop");
  delay(50);
}