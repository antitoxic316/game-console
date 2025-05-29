#ifndef _GUISpace_H_
#define _GUISpace_H_

#include <Saturn.h>

#include "ButtonWidget.h"
#include "ObjGrid.h"

class GUISpace
{
private:
    Saturn gameEnv_;
public:
    GUISpace(GraphEnv &graph_env) 
      : gameEnv_(graph_env)
    {
    };
    ~GUISpace() = default;

    void start();
};

#endif