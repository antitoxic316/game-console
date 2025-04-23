#include "dummygame.h"

void setup() {
  Dummygame game;
  game.start();

  Serial.begin(19200);
  delay(100);
}

void loop() {
}