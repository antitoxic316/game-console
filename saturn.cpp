#include "saturn.h"

Saturn::Saturn(){

}

Saturn::~Saturn(){
    
}

void Saturn::update_frame(void){
    this->graph_env->clearDisplay();

        for(auto &obj: this->dynamic_objects) {


            char* ccx = new char[obj->getName().length() + 1];
            std::copy(obj->getName().begin(), obj->getName().end(), ccx);
            Serial.println(ccx);

            Serial.println((uint8_t)pgm_read_word(obj->getBitmap()));


            obj->onFramePassed();
            Serial.println("on frame passed");
            this->graph_env->drawBitmap(
                obj->getX(), obj->getY(),
                obj->getBitmap(),
                obj->getWidth(), obj->getHeight(),
                1);
            
        }

    this->graph_env->display();
}

void Saturn::setGraphicalEnv(Adafruit_SSD1306 *graph_env){
        this->graph_env = graph_env;

        // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
        if(!this->graph_env->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
            Serial.println(F("SSD1306 allocation failed"));
            for(;;); // Don't proceed, loop forever
        }

        // Show initial display buffer contents on the screen --
        // the library initializes this with an Adafruit splash screen.
        this->graph_env->display();
        delay(2000); // Pause for 2 seconds

        // Clear the buffer
        this->graph_env->clearDisplay();
        Serial.println("cleared buffer");
}   

void Saturn::start(){
    ulong start_time = millis();

    while(true){
        ulong current_time = millis();
        if((current_time - start_time) > 1000/(float)this->frame_rate){
            start_time = current_time;
            
            this->update_frame();

            Serial.println(start_time);
            Serial.println(current_time);
            Serial.println(1.0/(float)this->frame_rate);
        }
    }
    
}
