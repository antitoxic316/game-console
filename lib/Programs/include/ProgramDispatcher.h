#pragma once

#include "Program.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include <Arduino.h>

class ProgramDispatcher
{
private:
    std::unordered_map<std::string, Program *> progMap_;
    //std::vector<ProgramPriority> bgProgs_;
public:
    ProgramDispatcher(){

    }
    void registerProgram(const std::string &prog_name,  Program *prog){
        progMap_[prog_name] = prog;
    }

    void callProgram(Program &caller, const std::string &prog_name){
        Serial.print("called program: ");
        Serial.println(prog_name.c_str());

        caller.interrupt();

        auto prog_entry = progMap_.find(prog_name);
        if(prog_entry == progMap_.end()){
            Serial.println("no program with such name");
            return;
        }

        Program *pr = progMap_.at(prog_name);

        pr->uninterrupt();
        pr->run();

        caller.uninterrupt();
    }

    void yieldControl(){
        // run programs in round robin
    }
};