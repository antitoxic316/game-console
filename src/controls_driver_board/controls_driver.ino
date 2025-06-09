#include <SoftwareSerial.h>

SoftwareSerial sSerial(12,11);

#define PRESSED 0
#define RELEASED 1

#define HEADER_BYTE 0xF2

// virtual because joystick left is also consodered button
struct VirtualKey {
  VirtualKey(const char *n, const int16_t serialVal)
  : name(name), transmitVal(serialVal), prevState(RELEASED), state(RELEASED){
  } 
  const char *name;
  const uint16_t transmitVal;
  int prevState;
  int state;
};

VirtualKey p1_left("p1_left", 1);
VirtualKey p1_right("p1_right", 2);
VirtualKey p1_up("p1_up", 4);
VirtualKey p1_down("p1_down", 8);
VirtualKey p1_x("p1_x", 16);
VirtualKey p1_y("p1_y", 32);
VirtualKey p1_b("p1_b", 64);
VirtualKey p1_a("p1_a", 128);

VirtualKey p2_left("p2_left", 256);
VirtualKey p2_right("p2_right", 512);
VirtualKey p2_up("p2_up", 1024);
VirtualKey p2_down("p2_down", 2048);
VirtualKey p2_x("p2_x", 4096);
VirtualKey p2_y("p2_y", 8192);
VirtualKey p2_b("p2_b", 16384);
VirtualKey p2_a("p2_a", 32768);

#define VIRTUAL_KEYS_NUM 16
VirtualKey *virtualKeys[VIRTUAL_KEYS_NUM] = {
  &p1_left, &p1_right, &p1_up, &p1_down, &p1_x, &p1_y, &p1_b, &p1_a,
  &p2_left, &p2_right, &p2_up, &p2_down, &p2_x, &p2_y, &p2_b, &p2_a
};

int xPosJ1Prev = 512;
int yPosJ1Prev = 512;

int xPosJ2Prev = 512;
int yPosJ2Prev = 512;

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
  //check for pressing continuity
  for(int i = 0; i < VIRTUAL_KEYS_NUM; i++){
    virtualKeys[i]->state = RELEASED;
  }

  uint32_t final_data = 0;

  int xPosJ1 = analogRead(A0);
  int yPosJ1 = analogRead(A1);
  int J1Button = digitalRead(7);

  int xPosJ2 = analogRead(A3);
  int yPosJ2 = analogRead(A4);
  int J2Button = digitalRead(8);

  int xv_J1 = xPosJ1 - xPosJ1Prev;
  xPosJ1Prev = xPosJ1;
  int yv_J1 = yPosJ1 - yPosJ1Prev;
  yPosJ1Prev = yPosJ1;

  xv_J1 &= 0xFF;
  xv_J1 <<= 16;
  yv_J1 &= 0xFF;
  yv_J1 <<= 24;

  final_data |= xv_J1;

  final_data |= yv_J1;

  uint16_t keys_data = 0;

  if(xPosJ1 > 600){
    virtualKeys[0]->state = PRESSED;  
  }
  if(xPosJ1 < 400){
    virtualKeys[1]->state = PRESSED;
  }
  if(yPosJ1 > 600){
    virtualKeys[2]->state = PRESSED;
  }
  if(yPosJ1 < 400){
    virtualKeys[3]->state = PRESSED;
  }

  if(xPosJ2 > 600){
    virtualKeys[8]->state = PRESSED;  
  }
  if(xPosJ2 < 400){
    virtualKeys[9]->state = PRESSED;
  }
  if(yPosJ2 > 600){
    virtualKeys[10]->state = PRESSED;
  }
  if(yPosJ2 < 400){
    virtualKeys[11]->state = PRESSED;
  }

  if(!J1Button){
    virtualKeys[7]->state = PRESSED;
  }

  for(int i = 0; i < VIRTUAL_KEYS_NUM; i++){
    VirtualKey *v_key = virtualKeys[i];
    if(v_key->state == PRESSED && v_key->prevState == RELEASED){
      keys_data |= v_key->transmitVal;
      v_key->prevState = v_key->state;

      Serial.print("prevState: ");
      Serial.println(v_key->prevState);


      Serial.print("state: ");
      Serial.println(v_key->state);

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
  Serial.println("sent");
  sSerial.write(HEADER_BYTE);
  sSerial.write((char*)&data, 4);
}