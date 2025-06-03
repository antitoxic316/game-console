#include <SoftwareSerial.h>

SoftwareSerial sSerial(12,11);

#define PRESSED 0
#define RELEASED 1

#define HEADER_BYTE 0xF2

// virtual because joystick left is also consodered button
typedef struct VirtualKey_ {
  const char *name;
  const int16_t transmitVal;
  int prevState = 0;
  int state = 0;
} VirtualKey;

VirtualKey p1_left = {"p1_left", 1};
VirtualKey p1_right = {"p1_right", 2};
VirtualKey p1_up = {"p1_up", 4};
VirtualKey p1_down = {"p1_down", 8};
VirtualKey p1_x = {"p1_x", 16};
VirtualKey p1_y = {"p1_y", 32};
VirtualKey p1_b = {"p1_b", 64};
VirtualKey p1_a = {"p1_a", 128};

VirtualKey p2_left = {"p2_left", 256};
VirtualKey p2_right = {"p2_right", 512};
VirtualKey p2_up = {"p2_up", 1024};
VirtualKey p2_down = {"p2_down", 2048};
VirtualKey p2_x = {"p2_x", 4096};
VirtualKey p2_y = {"p2_y", 8192};
VirtualKey p2_b = {"p2_b", 16384};
VirtualKey p2_a = {"p2_a", 32768};

#define VIRTUAL_KEYS_NUM 16
VirtualKey virtualKeys[VIRTUAL_KEYS_NUM] = {
  p1_left, p1_right, p1_up, p1_down, p1_x, p1_y, p1_b, p1_a,
  p2_left, p2_right, p2_up, p2_down, p2_x, p2_y, p2_b, p2_a
};


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

uint32_t unpress_button_bit = 0x80000000;

void send_data(uint32_t data);

void setup() {
  pinMode(7, INPUT_PULLUP);
  
  sSerial.begin(9600);
  delay(100);

  Serial.begin(19200);
  delay(100);
}

void loop() {
  uint32_t final_data = 0;

  left_state = 1;
  right_state = 1;
  up_state = 1;
  down_state = 1;

  int xPos = analogRead(A0);
  int yPos = analogRead(A2);
  // Read the button state (LOW when pressed due to pull-up resistor)
  int buttonState = digitalRead(7);

  int x_v = xPos - xPosPrev;
  xPosPrev = xPos;
  int y_v = yPos - yPosPrev;
  yPosPrev = yPos;


  x_v &= 0xFF;
  x_v <<= 16;
  y_v &= 0xFF;
  y_v <<= 24;

  final_data |= x_v;

  final_data |= y_v;

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

  for(int i = 0; i < VIRTUAL_KEYS_NUM; i++){
    VirtualKey *v_key = &virtualKeys[i];
    if(v_key->state == PRESSED && v_key->prevState == RELEASED){
      keys_data |= v_key->transmitVal;
      v_key->prevState = v_key->state;

      final_data |= keys_data;
      send_data(final_data);
      return;
    }
    if(v_key->state == RELEASED && v_key->prevState == PRESSED){
      keys_data |= v_key->transmitVal;
      final_data |= unpress_button_bit;
      v_key->prevState = v_key->state;

      final_data |= keys_data;
      send_data(final_data);
      return;
    }
  }

  delay(10);
}

void send_data(uint32_t data){
  sSerial.write(HEADER_BYTE);
  sSerial.write((char*)&data, 4);
}

