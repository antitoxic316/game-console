#include "MainMenuProgram.h"

MainMenuProgram::~MainMenuProgram()
{
}

void MainMenuProgram::init(){
    guiEnv_.init();
}

void MainMenuProgram::start(){
    guiEnv_.getSaturnRef().run();
}