#include <PingPong.h>
#include <DummyGame.h>
#include <MainMenuProgram.h>


void setup() {
  Serial.begin(19200);
  delay(100);

  SoftwareSerial controllerSerial = SoftwareSerial(0, 1);

  GraphEnv graphEnv(128, 64);

  while(true){
    PingPong game(graphEnv, controllerSerial);
    Dummygame game2(graphEnv, controllerSerial);

    game.start();
    game2.start();
  }
}

void loop() {
}