#ifndef _MainMenuProgram_H_
#define _MainMenuProgram_H_

#include <GUISpace.h>

const uint8_t test_label[8] = {0xFF, 0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,};

class MainMenuProgram
{
private:
    GUISpace guiEnv_;
public:
    MainMenuProgram(GraphEnv &graph_env, SoftwareSerial &controllerInput) 
        :guiEnv_(graph_env, controllerInput)
    {
        std::shared_ptr<ButtonWidget> test_obj = std::make_shared<ButtonWidget>("test");
        test_obj->setLabel("test");
        guiEnv_.addInteractableWidget(test_obj);
    }
    ~MainMenuProgram();

    void start();
};

#endif