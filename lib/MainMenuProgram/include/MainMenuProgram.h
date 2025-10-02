#ifndef _MainMenuProgram_H_
#define _MainMenuProgram_H_

#include <GUISpace.h>
#include <ProgramDispatcher.h>
#include <IDispatchable.h>

const uint8_t test_label[8] = {0xFF, 0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,};

class MainMenuProgram : public IDispatchable
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
        test_game_button->setGridJ(3);
        test_game_button->move(30, 10);
        test_game_button->setAButtonPressedCallback([this](InteractableWidget *w){
            pd_.enqueueProgram("test");
        });
        guiEnv_.addInteractableWidget(test_game_button);
        

        std::shared_ptr<ButtonWidget> pingpong_game_button = std::make_shared<ButtonWidget>("pingpong");
        pingpong_game_button->setLabel("pingpong");
        pingpong_game_button->setGridI(9);
        pingpong_game_button->setGridJ(1);
        pingpong_game_button->move(10, 45);
        pingpong_game_button->setAButtonPressedCallback([this](InteractableWidget *w){
            pd_.enqueueProgram("pingpong");
        });
        guiEnv_.addInteractableWidget(pingpong_game_button);


        std::shared_ptr<ButtonWidget> wifi_button = std::make_shared<ButtonWidget>("wifi");
        wifi_button->setLabel("wifi");
        wifi_button->setGridI(5);
        wifi_button->setGridJ(9);
        wifi_button->move(78, 30);
        wifi_button->setAButtonPressedCallback([this](InteractableWidget *w){
            pd_.enqueueProgram("wifi");
        });
        guiEnv_.addInteractableWidget(wifi_button);
    }
    ~MainMenuProgram();

    void init();
    void start();

    Program* getProgramPtr() override{
      return &(guiEnv_.getSaturnRef());
    }
};

#endif