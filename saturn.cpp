#include "saturn.h"

Saturn::Saturn(){

}

Saturn::~Saturn(){
    
}

void Saturn::update_frame(void){
    this->graph_env->clearDisplay();

        for(auto &obj: this->dynamic_objects) {
            std::unique_ptr<std::vector<Obj*>> obj_colls;

            obj->onFramePassed();
            Serial.println("on frame passed");
            this->graph_env->drawBitmap(
                obj->getX(), obj->getY(),
                obj->getBitmap(),
                obj->getWidth(), obj->getHeight(),
                1);

            obj_colls = this->getObjectCollisions(obj.get());

            if(!obj_colls){
                continue;
            }

            for(auto *obj_collision: *obj_colls){
                obj->onCollision(obj_collision->getName());
            }
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

std::unique_ptr<std::vector<Obj*>> Saturn::getObjectCollisions(DynamicObj *obj){
    std::unique_ptr<std::vector<Obj*>> objs;
    objs = std::make_unique<std::vector<Obj*>>();
    for(auto &coll_obj: this->dynamic_objects){
        objs->push_back(static_cast<Obj*>(coll_obj.get()));
    }

    return objs;
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