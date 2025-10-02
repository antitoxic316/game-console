#pragma once

#ifndef _WiFiChoser_H_
#define _WiFiChoser_H_

#include <GUISpace.h>
#include <Keyboard.h>
#include <TextBufferWidget.h>
#include <IDispatchable.h>

class WiFiChoser : public IDispatchable
{
private:
    GUISpace guiEnv_;
public:
    WiFiChoser(GraphEnv &graph_env, SoftwareSerial &controllerInput) 
        :guiEnv_(graph_env, controllerInput)
    {
    }
    ~WiFiChoser() = default;

    void init();
    void start() {
        guiEnv_.getSaturnRef().run();
    };

    Program* getProgramPtr() override{
      return &(guiEnv_.getSaturnRef());
    }
};

#endif