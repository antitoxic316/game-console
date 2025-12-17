#pragma once

#include <Arduino.h>
#include <map>
#include <string>
#include <vector>

struct PROG_CONTEXT {
    std::map<std::string, std::vector<std::string>> entries;
};

class Program
{
private:
protected:
  bool _interrupted = false;
public:
  Program(){
    
  }
  virtual ~Program() = default;
  virtual void run(){
  }
  virtual void interrupt(){
    _interrupted = true;
  }
  virtual void uninterrupt(){
    _interrupted = false;
  }

  bool isInterrupted(){
    return _interrupted;
  }
};