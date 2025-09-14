#include <PingPong.h>
#include <DummyGame.h>
#include <MainMenuProgram.h>
#include <ProgramDispatcher.h>
#include <NetworkHandler.h>

SoftwareSerial controllerSerial = SoftwareSerial(0, 1);

void setup() {
  Serial.begin(19200);
  delay(100);


  GraphEnv graphEnv(128, 64);

  ProgramDispatcher pd;

  PingPong game(graphEnv, controllerSerial);
  Dummygame game2(graphEnv, controllerSerial);

  game.init();
  game2.init();  

  pd.registerProgram("pingpong", game.getSaturnPtr());
  pd.registerProgram("test", game2.getSaturnPtr());

  MainMenuProgram mainmenu(graphEnv, controllerSerial, pd);

  mainmenu.init();
  mainmenu.start();
}

void loop() {
  Serial.println("inside the main loop");
  delay(50);
}