#pragma once

#ifndef _WiFiChoser_H_
#define _WiFiChoser_H_

#include <GUISpace.h>
#include <Keyboard.h>

class WiFiChoser
{
private:
    GUISpace guiEnv_;
public:
    WiFiChoser(GraphEnv &graph_env, SoftwareSerial &controllerInput) 
        :guiEnv_(graph_env, controllerInput)
    {
        init();
    }
    ~WiFiChoser() = default;

    void init();
    void start() {
        guiEnv_.getSaturnRef().run();
    };

    Saturn* getSaturnPtr(){
      return &(guiEnv_.getSaturnRef());
    }
};

#endif