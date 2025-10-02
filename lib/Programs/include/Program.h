#pragma once

#include <Arduino.h>

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