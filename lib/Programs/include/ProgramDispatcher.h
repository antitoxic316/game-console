#pragma once

#include "Program.h"

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <stack>
#include <queue>

#include <Arduino.h>

#include <IDispatchable.h>
#include <ProgramShell.h>

class ProgramDispatcher
{
private:
    std::map<std::string, std::shared_ptr<ProgramShell>> progMap_;
    
    std::stack<std::shared_ptr<ProgramShell>> progStack_;
public:
    ProgramDispatcher(){

    }
    void registerProgram(const std::string prog_name,  std::shared_ptr<ProgramShell> prog){
        progMap_[prog_name] = std::move(prog);
    }

    void enqueueProgram(const std::string prog_name, bool save_caller = false);

    void eventLoop();
};