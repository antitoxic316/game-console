#ifndef _DummyGame_H_
#define _DummyGame_H_

#include <Saturn.h>

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
};

#endif