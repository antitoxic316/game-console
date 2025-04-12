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
        if(!obj->getBitmap()){
            goto skip_drawing_object;
        }
        this->graph_env->drawBitmap(
            obj->getX(), obj->getY(),
            obj->getBitmap(),
            obj->getWidth(), obj->getHeight(),
            1);
skip_drawing_object:

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
}

std::unique_ptr<std::vector<Obj*>> Saturn::getObjectCollisions(DynamicObj *obj){
    auto collided_objs = std::make_unique<std::vector<Obj*>>();
    
    for(auto &dynamic_obj_p: this->dynamic_objects){
        if(this->areObjectsCollided(obj, dynamic_obj_p.get())){
            collided_objs->push_back(dynamic_obj_p.get());
        }
    }

    for(auto &static_obj_p: this->static_objects){
        if(this->areObjectsCollided(obj, static_obj_p.get())){
            collided_objs->push_back(static_obj_p.get());
        }
    }

    return collided_objs;
}

bool Saturn::areObjectsCollided(Obj *objA, Obj *objB){
    //top left corner is x=0, y=0

    int objALeftBorder = objA->getX();
    int objARightBorder = objA->getX() + objA->getWidth();
    int objATopBorder = objA->getY();
    int objABottomBorder = objA->getY() + objA->getHeight();
    
    int objBLeftBorder = objB->getX();
    int objBRightBorder = objB->getX() + objB->getWidth();
    int objBTopBorder = objB->getY();
    int objBBottomBorder = objB->getY() + objB->getHeight();

    bool x_aligned = false;
    bool y_aligned = false;

    if(objARightBorder >= objBLeftBorder && objALeftBorder <= objBRightBorder){
        x_aligned = true;
    }
    if(objABottomBorder >= objBTopBorder && objATopBorder <= objBBottomBorder){
        y_aligned = true;
    }

    return x_aligned && y_aligned;
}

void Saturn::start(){
    ulong start_time = millis();

    while(true){
        ulong current_time = millis();
        if((current_time - start_time) > 1000/this->frame_rate){
            start_time = current_time;
            
            this->update_frame();
        }
    }
}