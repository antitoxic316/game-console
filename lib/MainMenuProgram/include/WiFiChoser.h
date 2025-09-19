#pragma once

#ifndef _MainMenuProgram_H_
#define _MainMenuProgram_H_

#include <GUISpace.h>
#include <ProgramDispatcher.h>
#include <Keyboard.h>

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
        std::shared_ptr<Keyboard> keyboard = std::make_shared<Keyboard>("keyboard");
        keyboard->setGridI(1);
        keyboard->setGridJ(0);
        keyboard->move(20, 0);
        

        std::shared_ptr<Widget> text_buffer = std::make_shared<Widget>("txt_buff");
        text_buffer->move(0, 0);
    }
    ~MainMenuProgram();

    void init();
    void start();
};

#endif