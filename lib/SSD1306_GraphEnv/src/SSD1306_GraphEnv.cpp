#include "SSD1306_GraphEnv.h"

void GraphEnv::init(){
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display_.begin(SSD1306_SWITCHCAPVCC, screenAdr_)) {
        for(;;); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display_.display();
    delay(100);

    display_.clearDisplay();
}

void GraphEnv::drawBitMap(int x, int y, const uint8_t *data, int w, int h){
    display_.drawBitmap(x, y, data, w, h, 1);
}

void GraphEnv::drawText(int x, int y, const char *text, int size){
    display_.setCursor(x, y);
    display_.setTextColor(1);
    display_.setTextSize(size);
    for(const char *c = text; *c != '\0'; c++){
        display_.write(*c);
    }
    this->display();
}

void GraphEnv::display(){
    display_.display();
}

void GraphEnv::clearDisplay(){
    display_.clearDisplay();
}