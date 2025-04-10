#include "dummygame.h"

void setup() {
  Serial.begin(9600);
  delay(100);

  Dummygame game;
  game.start();
}

void loop() {
}