#include <PingPong.h>

void setup() {
  PingPong game;
  game.start();

  Serial.begin(19200);
  delay(100);
}

void loop() {
}