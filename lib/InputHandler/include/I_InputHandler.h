#pragma once

#include <cstdint>

class I_InputHandler
{
private:
public:
    I_InputHandler(){

    };
    virtual ~I_InputHandler() = default;

    virtual void readInput() = 0;
};
