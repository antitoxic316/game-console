#include <PingPong.h>
#include <DummyGame.h>
#include <MainMenuProgram.h>
#include <ProgramDispatcher.h>
#include <NetworkHandler.h>
#include <WiFiChoser.h>

SoftwareSerial controllerSerial = SoftwareSerial(0, 1);


void setup() {
  GraphEnv graphEnv(128, 64);
  ProgramDispatcher pd;

  Serial.begin(19200);
  delay(4000);

  pd.registerProgram("pingpong", std::make_unique<ProgramShell>(
    [&graphEnv]() -> std::shared_ptr<IDispatchable> 
    {
      return std::make_shared<PingPong>(graphEnv, controllerSerial);
    }
  ));

  pd.registerProgram("test", std::make_unique<ProgramShell>(
      [&graphEnv]() -> std::shared_ptr<IDispatchable> 
    {
      return std::make_shared<Dummygame>(graphEnv, controllerSerial);
    }));
  
  pd.registerProgram("wifi", std::make_shared<ProgramShell>(
    [&graphEnv]() -> std::shared_ptr<WiFiChoser> 
    {
      return std::make_shared<WiFiChoser>(graphEnv, controllerSerial);
    }));
  
  pd.registerProgram("mainmenu", std::make_shared<ProgramShell>(
    [&graphEnv, &pd]() -> std::shared_ptr<MainMenuProgram> 
    {
      return std::make_shared<MainMenuProgram>(graphEnv, controllerSerial, pd);
    }));
  


  while(1){
    Serial.printf("%d    %d\r\n\r", __LINE__, ESP.getFreeHeap());
    pd.enqueueProgram("mainmenu");
    pd.eventLoop();
  }
}

void loop() {
  Serial.println("inside the main loop");
  delay(50);
}