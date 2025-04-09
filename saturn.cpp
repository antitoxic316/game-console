#include "saturn.h"

Saturn::Saturn(){

}

Saturn::~Saturn(){
    
}

void Saturn::update_frame(void){
        for(auto &obj: this->dynamic_objects) {
            obj->onFramePassed();
            this->graph_env.drawBitmap(
                obj->getX(), obj->getY(),
                obj->getBitMap(),
                obj->getWidth(), obj->getHeight(),
                1);
        }
}

void Saturn::setGraphicalEnv(Adafruit_SSD1306 &graph_env){
        this->graph_env = graph_env;
        Serial.begin(9600);

        // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
        if(!this->graph_env.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
            Serial.println(F("SSD1306 allocation failed"));
            for(;;); // Don't proceed, loop forever
        }

        // Show initial display buffer contents on the screen --
        // the library initializes this with an Adafruit splash screen.
        this->graph_env.display();
        delay(2000); // Pause for 2 seconds

        // Clear the buffer
        this->graph_env.clearDisplay();
}   

void Saturn::start(){
    std::time_t start_time = std::time(nullptr);

    while(true){
        std::time_t current_time = std::time(nullptr);
        if((current_time - start_time) / this->frame_rate > 1){
            start_time = current_time;
            this->update_frame();
        }
    }
}
