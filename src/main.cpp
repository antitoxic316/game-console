#include <PingPong.h>

void setup() {
  PingPong game(128, 64);
  game.start();

  Serial.begin(19200);
  delay(100);
}

void loop() {
}