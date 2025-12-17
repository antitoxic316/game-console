#include <Keyboard.h>


void Keyboard::loadChunk(int chunkI, int chunkJ){
    Serial.printf("chunking I: %d J: %d\n\r", chunkI, chunkJ);
    if(chunkSize_*chunkI >= keys_H || chunkSize_*chunkJ >= keys_W){
        Serial.printf("chunk coordinates are out of limits");
        return;
    }

    lastLoadedChunkI_ = chunkI;
    lastLoadedChunkJ_ = chunkJ;

    for(int i = chunkSize_ * chunkI; i < chunkSize_ * (chunkI+1); i++){
        for(int j = chunkSize_ * chunkJ; j < chunkSize_ * (chunkJ+1); j++){
            char btn_name[4] = {'\0',};
            btn_name[0] = ((i*keys_H + j)+32);

            if(btn_name[0] == ' '){
                btn_name[0] = '\'';
                btn_name[1] = ' ';
                btn_name[2] = '\'';
            }

            Serial.printf("adding indexes i: %d j: %d\r\n", i, j);

            std::shared_ptr<ButtonWidget> key_btn = std::make_shared<ButtonWidget>(btn_name);

            key_btn->setLabel(btn_name);
            key_btn->setGridI(i);
            key_btn->setGridJ(j);
            key_btn->move(j+keysOffsetDistance_*j + margin_, i+keysOffsetDistance_*i + margin_);
            key_btn->setAButtonPressedCallback([this, btn_name](InteractableWidget *w){
                Serial.print(btn_name);
                Serial.println(" key pressed");
                w->emitEvent("char typed", (void *)(w->getName())); //first char is the CHARACTER
            });
            key_btn->setParentWidget(this);
            placeWidget(key_btn, key_btn->getGridI(), key_btn->getGridJ());
        }
    }
}

void Keyboard::unloadChunk(int chunkI, int chunkJ){
    for(int i = chunkI*chunkSize_; i < chunkI * (chunkSize_+1); i++){
        for(int j = chunkJ * chunkSize_; j < chunkJ * (chunkSize_+1); j++){
            widgetGrid_[i][j] = NULL;
        }
    }
}


std::shared_ptr<InteractableWidget> Keyboard::getNearestWidget(int i_v, int j_v){
    std::shared_ptr<InteractableWidget> widg(nullptr);

    // almost all cells are populated
    if(i_v){
        int i = currentI_;
        int j = currentJ_;
        while(true){
            Serial.printf("i_v: %d i: %d j: %d", i_v, i, j);

            if(i == chunkSize_-1 && i_v == 1){
                loadChunk(lastLoadedChunkI_+1, lastLoadedChunkJ_);
                unloadChunk(lastLoadedChunkI_-1, lastLoadedChunkJ_);
            }
            if(i == chunkSize_ && i_v == -1){
                loadChunk(lastLoadedChunkI_-1, lastLoadedChunkJ_);
                unloadChunk(lastLoadedChunkI_+1, lastLoadedChunkJ_);
            
            }
 
            i += i_v;
            if(i >= widgGridH_ || i < 0){
                break;
            }
            if(widgetGrid_[i][j]){
                widg = widgetGrid_[i][j];
                currentI_ = i;
                currentJ_ = j;
                return widg; 
            }
        }
    }
    
    if(j_v){
        int i = currentI_;
        int j = currentJ_;
        while(true){
            Serial.printf("j_v: %d i: %d j: %d", j_v, i, j);
            if(j == chunkSize_-1 && j_v == 1){
                loadChunk(lastLoadedChunkI_, lastLoadedChunkJ_+1);
                unloadChunk(lastLoadedChunkI_, lastLoadedChunkJ_-1);
            }
            if(j == chunkSize_ && j_v == -1){
                loadChunk(lastLoadedChunkI_, lastLoadedChunkJ_-1);
                unloadChunk(lastLoadedChunkI_, lastLoadedChunkJ_+1);    
            }

            j += j_v;
            if(j >= widgGridH_ || j < 0){
                break;
            }
            if(widgetGrid_[i][j]){
                widg = widgetGrid_[i][j];
                currentI_ = i;
                currentJ_ = j;
                return widg; 
            }
        }
    }

    // no widget found
    return nullptr;
}


void Keyboard::drawCallback(GraphEnv &env) {
    env.drawLine(getX(), getY(), getX(), env.getScreenH());
    env.drawLine(getX(), getY(), env.getScreenW(), getY());

    for(int i = 0; i < keys_H; i++){
        for(int j = 0 ; j < keys_W; j++){
            /*env.drawText(
                j+keysOffsetDistance_*j + margin_, 
                i+keysOffsetDistance_*i + margin_, 
                asciiChars[(i*keys_H + j)+32],
                1
            );
            */
        }
    }
}