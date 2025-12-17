#pragma once

#include <InteractableGrid.h>
#include <ButtonWidget.h>

#define keys_W 8
#define keys_H 8

class Keyboard : public InteractableGrid
{
private:
  int chunkSize_ = keys_W / 2;

  int lastLoadedChunkI_ = 0;
  int lastLoadedChunkJ_ = 0;

  int keysOffsetDistance_ = 7;
  int margin_ = 2;
protected:
  std::shared_ptr<InteractableWidget> getNearestWidget(int i_v, int j_v) override;
public:
  Keyboard(const std::string &name) :
    InteractableGrid(name)
  { 
    loadChunk(0,0);
    currentI_ = 0;
    currentJ_ = 0;
  }

  void drawCallback(GraphEnv &env) override;

  void loadChunk(int i, int j);
  void unloadChunk(int i, int j);
};