#include <PingPong.h>
#include <DummyGame.h>

void setup() {
  Serial.begin(19200);
  delay(100);

  GraphEnv graphEnv(128, 64);

  while(true){
    PingPong game(graphEnv);
    Dummygame game2(graphEnv);

    game.start();
    game2.start();
  }
}

void loop() {
}