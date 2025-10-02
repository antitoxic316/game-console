#pragma once

#include <functional>
#include <IDispatchable.h>

#include <memory>

class ProgramShell
{
private:
  std::function<std::shared_ptr<IDispatchable> (void)> startProgramCallback_;
  std::shared_ptr<IDispatchable> pr_;
public:
  ProgramShell(std::function<std::shared_ptr<IDispatchable> (void)> cb) 
  : startProgramCallback_(cb),
  pr_(nullptr)
  {
  };

  void setInitCallback(std::function<std::shared_ptr<IDispatchable>(void)> cb){
    startProgramCallback_ = cb;
  }

  void startProgram(){
    pr_ = startProgramCallback_();
    Serial.printf("%d    %d\r\n\r", __LINE__, ESP.getFreeHeap());
    pr_->init();
    Serial.printf("%d    %d\r\n\r", __LINE__, ESP.getFreeHeap());

  }

  Program *getProgram(){
    return pr_->getProgramPtr();
  }
};