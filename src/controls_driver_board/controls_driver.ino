#include <SoftwareSerial.h>

SoftwareSerial sSerial(12,11);

#define LEFT_BYTE 0b0001
#define RIGHT_BYTE 0b0010
#define UP_BYTE 0b0100
#define DOWN_BYTE 0b1000

#define PRESSED 0
#define RELEASED 1

#define HEADER_BYTE 0xF2

int left_prev_state = 0;
int left_state = 0;
int right_prev_state = 0;
int right_state = 0;
int up_prev_state = 0;
int up_state = 0;
int down_prev_state = 0;
int down_state = 0;

int xPosPrev = 512;
int yPosPrev = 512;

int unpress_button_bit = 1 << 62;

void send_data(int data);

void setup() {
  pinMode(7, INPUT_PULLUP);
  
  sSerial.begin(9600);
  delay(100);

  Serial.begin(9600);
  delay(100);
}

void loop() {
  left_state = 1;
  right_state = 1;
  up_state = 1;
  down_state = 1;

  int xPos = analogRead(A1);
  int yPos = analogRead(A0);
  // Read the button state (LOW when pressed due to pull-up resistor)
  int buttonState = digitalRead(7);

  long long final_data = 0;

  int x_v = xPos - xPosPrev;
  xPosPrev = xPos;
  int y_v = yPos - yPosPrev;
  yPosPrev = yPos;

/*
  x_v &= 0xFF;
  x_v <<= 16;
  y_v &= 0xFF;
  y_v <<= 24;

  final_data |= x_v;

  final_data |= y_v;
*/
  uint16_t keys_data = 0;

  if(xPos > 600){
    right_state = PRESSED;  
  }
  if(xPos < 400){
    left_state = PRESSED;
  }
  if(yPos > 600){
    up_state = PRESSED;
  }
  if(yPos < 400){
    down_state = PRESSED;
  }
  

  if(left_state == PRESSED && left_prev_state == RELEASED){
    keys_data |= LEFT_BYTE;
    left_prev_state = left_state;

    final_data |= keys_data;
    send_data(final_data);
  }
  if(left_state == RELEASED && left_prev_state == PRESSED){
    keys_data |= LEFT_BYTE;
    keys_data |= unpress_button_bit;
    left_prev_state = left_state;

    final_data |= keys_data;
    send_data(final_data);
  }

  if(right_state == PRESSED && right_prev_state == RELEASED){
    keys_data |= RIGHT_BYTE;
    right_prev_state = right_state;

    final_data |= keys_data;
    send_data(final_data);
  }
  if(right_state == RELEASED && right_prev_state == PRESSED){
    keys_data |= RIGHT_BYTE;
    keys_data |= unpress_button_bit;
    right_prev_state = right_state;

    final_data |= keys_data;
    send_data(final_data);
  }

  if(up_state == PRESSED && up_prev_state == RELEASED){
    keys_data |= UP_BYTE;
    up_prev_state = up_state;

    final_data |= keys_data;
    send_data(final_data);
  }
  if(up_state == RELEASED && up_prev_state == PRESSED){
    keys_data |= UP_BYTE;
    keys_data |= unpress_button_bit;
    up_prev_state = up_state;

    final_data |= keys_data;

    send_data(final_data);
  }
  

  if(down_state == PRESSED && down_prev_state == RELEASED){
    keys_data |= DOWN_BYTE;
    down_prev_state = down_state;

    final_data |= keys_data;
    send_data(final_data);
  }
  if(down_state == RELEASED && down_prev_state == PRESSED){
    keys_data |= DOWN_BYTE;
    keys_data |= unpress_button_bit;
    down_prev_state = down_state;

    final_data |= keys_data;
    send_data(final_data);
  }

  delay(1);
}

void send_data(long long data){
  sSerial.write(HEADER_BYTE);
  sSerial.write((char*)&data, 8);
}

