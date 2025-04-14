#include "saturn.h"

const std::unordered_map<uint8_t, ControlKeys> DEFAULT_KEY_MAPPING = {
    {1, ControlKeys::LEFT},
    {2, ControlKeys::RIGHT},
    {4, ControlKeys::UP},
    {8, ControlKeys::DOWN}
};

Saturn::Saturn(){

}

Saturn::~Saturn(){
    
}

void Saturn::update_frame(void){
    this->graph_env->clearDisplay();

    this->processInput();

    for(auto &obj: this->dynamic_objects) {
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

        auto obj_colls = this->getObjectCollisions(obj.get());

        if(!obj_colls){
            continue;
        }

        for(auto obj_collision: *obj_colls){
            obj->onCollision(obj_collision);
        }
    }

    for(auto &obj: this->controlable_objects){
        
        this->graph_env->drawBitmap(
            obj->getX(), obj->getY(),
            obj->getBitmap(),
            obj->getWidth(), obj->getHeight(),
            1);
    }

    this->graph_env->display();
}

void Saturn::processInput(){
    uint8_t input = this->inputBuffer.get();
    if(!input){
        return;
    }
    for(auto &obj: this->controlable_objects){
        ControlKeys key = DEFAULT_KEY_MAPPING.at(input);
        if(!key){
            return;
        }
        obj->onKeyInput(key);
    }
}

void Saturn::setGraphicalEnv(Adafruit_SSD1306 *graph_env){
    this->graph_env = graph_env;

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!this->graph_env->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        for(;;); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    this->graph_env->display();
    delay(2000);

    this->graph_env->clearDisplay();
}

std::unique_ptr<std::vector<Collision>> Saturn::getObjectCollisions(DynamicObj *obj){
    auto collided_objs = std::make_unique<std::vector<Collision>>();
    
    for(auto &dynamic_obj_p: this->dynamic_objects){
        if(this->areObjectsCollided(obj, dynamic_obj_p.get())){
            Collision coll_info = this->getCollisionInfo(obj, dynamic_obj_p.get());
            collided_objs->push_back(coll_info);
        }
    }

    for(auto &static_obj_p: this->static_objects){
        if(this->areObjectsCollided(obj, static_obj_p.get())){
            Collision coll_info = this->getCollisionInfo(obj, static_obj_p.get());
            collided_objs->push_back(coll_info);
        }
    }

    for(auto &controlable_obj_p: this->controlable_objects){
        if(this->areObjectsCollided(obj, controlable_obj_p.get())){
            Collision coll_info = this->getCollisionInfo(obj, controlable_obj_p.get());
            collided_objs->push_back(coll_info);
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

Collision Saturn::getCollisionInfo(Obj *objA, Obj *objB){
    int objALeftBorder = objA->getX();
    int objARightBorder = objA->getX() + objA->getWidth();
    int objATopBorder = objA->getY();
    int objABottomBorder = objA->getY() + objA->getHeight();
    
    int objBLeftBorder = objB->getX();
    int objBRightBorder = objB->getX() + objB->getWidth();
    int objBTopBorder = objB->getY();
    int objBBottomBorder = objB->getY() + objB->getHeight();

    int overlapLeft = objARightBorder - objBLeftBorder;
    int overlapRight = objBRightBorder - objALeftBorder;
    int overlapTop = objABottomBorder - objBTopBorder;
    int overlapBottom = objBBottomBorder - objATopBorder;

    Collision coll_info;
    coll_info.obj = objB;

    if (overlapLeft > 0 && overlapRight > 0 && overlapTop > 0 && overlapBottom > 0) {
        int aCenterX = (objALeftBorder + objARightBorder) / 2;
        int aCenterY = (objATopBorder + objABottomBorder) / 2;
        int bCenterX = (objBLeftBorder + objBRightBorder) / 2;
        int bCenterY = (objBTopBorder + objBBottomBorder) / 2;

        // Calculate direction vector from A to B
        int dx = bCenterX - aCenterX;
        int dy = bCenterY - aCenterY;

        // Determine primary collision axis
        if (abs(dx) > abs(dy)) {
            // Horizontal collision dominant
            coll_info.collision_side = (dx > 0) ? 
                Collision::Side::RIGHT : Collision::Side::LEFT;
        } else {
            // Vertical collision dominant
            coll_info.collision_side = (dy > 0) ? 
                Collision::Side::BOTTOM : Collision::Side::TOP;
        }
    }

    return coll_info;
}

void Saturn::start(){
    Serial.begin(9600);
    delay(100);

    ulong start_time = millis();

    while(true){
        if(Serial.available()) {
            
            uint8_t b_control = Serial.read();
            Serial.print("Received: ");
            Serial.println(b_control);
            this->inputBuffer.put(b_control);
        }

        ulong current_time = millis();
        if((current_time - start_time) > 1000/this->frame_rate){
            start_time = current_time;
            this->update_frame();    
        }

        delay(1);
    }
}