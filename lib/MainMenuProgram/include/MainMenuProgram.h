#ifndef _MainMenuProgram_H_
#define _MainMenuProgram_H_

#include <GUISpace.h>
#include <ProgramDispatcher.h>

const uint8_t test_label[8] = {0xFF, 0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,};

class MainMenuProgram
{
private:
    GUISpace guiEnv_;
    ProgramDispatcher &pd_;
    
public:
    MainMenuProgram(GraphEnv &graph_env, SoftwareSerial &controllerInput, ProgramDispatcher &pd) 
        :guiEnv_(graph_env, controllerInput),
         pd_(pd)
    {
        std::shared_ptr<ButtonWidget> test_game_button = std::make_shared<ButtonWidget>("test");
        test_game_button->setLabel("test");
        test_game_button->setGridI(0);
        test_game_button->setGridJ(0);
        test_game_button->move(10, 10);
        test_game_button->setAButtonPressedCallback([this](InteractableWidget *w){
            Serial.println("a pressed from: ");
            Serial.println(w->getName().c_str());
            pd_.callProgram(guiEnv_.getSaturnRef(), "test");
        });
        guiEnv_.addInteractableWidget(test_game_button);
        

        std::shared_ptr<ButtonWidget> pingpong_game_button = std::make_shared<ButtonWidget>("pingpong");
        pingpong_game_button->setLabel("pingpong");
        pingpong_game_button->setGridI(1);
        pingpong_game_button->setGridJ(0);
        pingpong_game_button->move(10, 40);
        pingpong_game_button->setAButtonPressedCallback([this](InteractableWidget *w){
            Serial.println("a pressed from: ");
            Serial.println(w->getName().c_str());
            pd_.callProgram(guiEnv_.getSaturnRef(), "pingpong");
        });
        guiEnv_.addInteractableWidget(pingpong_game_button);
    }
    ~MainMenuProgram();

    void init();
    void start();
};

#endif