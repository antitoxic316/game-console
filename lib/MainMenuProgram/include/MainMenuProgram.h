#ifndef _MainMenuProgram_H_
#define _MainMenuProgram_H_

#include <GUISpace.h>

class MainMenuProgram
{
private:
    GUISpace guiEnv_;
public:
    MainMenuProgram(GraphEnv &graph_env) 
        :guiEnv_(graph_env)
    {
        std::shared_ptr<ButtonWidget> ball_obj = std::make_shared<ButtonWidget>("test");
    }
    ~MainMenuProgram();

    void start();
};

#endif