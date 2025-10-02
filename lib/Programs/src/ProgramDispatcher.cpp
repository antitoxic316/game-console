#include "ProgramDispatcher.h"

void ProgramDispatcher::enqueueProgram(const std::string prog_name, bool save_caller){
  Serial.print(F("called program: "));
  Serial.println(prog_name.c_str());

  std::shared_ptr<ProgramShell> callerSH;
  if(!progStack_.empty()){
    callerSH = progStack_.top();
    callerSH->getProgram()->interrupt();
  }

  auto prog_entry = progMap_.find(prog_name);
  if(prog_entry == progMap_.end()){
      Serial.println(F("no program with such name"));
      if(callerSH){
        callerSH->getProgram()->uninterrupt();
      }
      return;
  }

  if(!save_caller && !progStack_.empty()){
      progStack_.pop();
  }

  std::shared_ptr<ProgramShell> sh = progMap_.at(prog_name);

  //the object is initialized from that shell copy
  progStack_.push(std::make_shared<ProgramShell>(*sh)); 
}


void ProgramDispatcher::eventLoop(){
  while(true){
    Serial.println("entered main loop of pd");
    Serial.println(progStack_.size());
    delay(100);
    if(progStack_.empty()){
        return;
    }
    std::shared_ptr<ProgramShell> active = progStack_.top();
    active->startProgram(); // creates instance of a program subclass

    Serial.println("started program");

    Program *prog = active->getProgram();
    prog->uninterrupt();
    prog->run();

    Serial.println("active prg exited");

    delay(1);
  }
}
