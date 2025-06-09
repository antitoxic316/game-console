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
        std::shared_ptr<ButtonWidget> test_game_button = std::make_shared<ButtonWidget>("test");
        test_game_button->setLabel("test");
        test_game_button->setGridI(0);
        test_game_button->setGridJ(0);
        //test_game_button->setAButtonPressedCallback();
        guiEnv_.addInteractableWidget(test_game_button);
        
        std::shared_ptr<ButtonWidget> pingpong_game_button = std::make_shared<ButtonWidget>("test");
        pingpong_game_button->setLabel("pingpong");
        pingpong_game_button->setGridI(1);
        pingpong_game_button->setGridJ(0);
        //pingpong_game_button->setAButtonPressedCallback();
        guiEnv_.addInteractableWidget(pingpong_game_button);
    }
    ~MainMenuProgram();

    void start();
};

#endif