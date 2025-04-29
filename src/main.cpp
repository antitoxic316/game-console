#include <DummyGame.h>

void setup() {
  Dummygame game(128, 64);
  game.start();

  Serial.begin(19200);
  delay(100);
}

void loop() {
}