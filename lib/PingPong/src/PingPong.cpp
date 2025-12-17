#include "PingPong.h"

// TODO: move this function into engine class or some utils class;
//implement bit map creation
void PingPong::generateScreenBorders(int screen_w, int screen_h, bool inside_screen, bool visible){
    auto bottom_border = std::make_shared<StaticObj>("bottomBorder");
    bottom_border->move(-1, screen_h+1);
    bottom_border->setBitmap(nullptr, screen_w, 1);
    
    auto top_border = std::make_shared<StaticObj>("topBorder");
    top_border->move(-1, -1);
    top_border->setBitmap(nullptr, screen_w, 1);
    
    auto left_border = std::make_shared<StaticObj>("leftBorder");
    left_border->move(-1, -1);
    left_border->setBitmap(nullptr, 1, screen_h);
    
    auto right_border = std::make_shared<StaticObj>("rightBorder");
    right_border->move(screen_w+1, -1);
    right_border->setBitmap(nullptr, 1, screen_h);

    this->gameEnv_.add_staticObj(bottom_border);
    this->gameEnv_.add_staticObj(top_border);
    this->gameEnv_.add_staticObj(left_border);
    this->gameEnv_.add_staticObj(right_border);
}

PingPong::~PingPong()
{
}

void PingPong::init(){
    if (onlinePlay_){ 
        gameEnv_.enableOnlinePlay();
        populateOnlineObjects();
    } else {
        gameEnv_.disableOnlinePlay();
        populateOfflineObjects();
    }
}

void PingPong::restart(){
    gameEnv_.interrupt();
    gameEnv_.clearObjects();
    gameEnv_.uninterrupt();
    init();
}

void PingPong::populateOnlineObjects(){
    this->generateScreenBorders(gameEnv_.getGraphicalEnv().getScreenW(), gameEnv_.getGraphicalEnv().getScreenH(), false, false);

    std::shared_ptr<Ball> ball_obj = std::make_shared<Ball>("ball");
    ball_obj->setBitmap(ball_bitmap, 12, 12);
    ball_obj->move(64, 32);
    this->gameEnv_.add_dynamicObj(ball_obj);

    std::shared_ptr<Player> p1_obj = std::make_shared<Player>("player1", P1_KEY_MAPPING);
    p1_obj->setBitmap(player_bitmap, 4, 32);
    p1_obj->move(10, 20);
    this->gameEnv_.add_controlableObj(p1_obj);

    std::shared_ptr<Player> p2_obj = std::make_shared<Player>("player2", P2_KEY_MAPPING);
    p2_obj->setBitmap(player_bitmap, 4, 32);
    p2_obj->move(110, 20);
    this->gameEnv_.add_controlableObj(p2_obj, OBJ_SERVER_CONTROLLED);
}


void PingPong::populateOfflineObjects(){
    this->generateScreenBorders(gameEnv_.getGraphicalEnv().getScreenW(), gameEnv_.getGraphicalEnv().getScreenH(), false, false);

    std::shared_ptr<Ball> ball_obj = std::make_shared<Ball>("ball");
    ball_obj->setBitmap(ball_bitmap, 12, 12);
    ball_obj->move(64, 32);
    this->gameEnv_.add_dynamicObj(ball_obj);

    std::shared_ptr<Player> p1_obj = std::make_shared<Player>("player1", P1_KEY_MAPPING);
    p1_obj->setBitmap(player_bitmap, 4, 32);
    p1_obj->move(10, 20);
    this->gameEnv_.add_controlableObj(p1_obj);

    std::shared_ptr<Player> p2_obj = std::make_shared<Player>("player2", P2_KEY_MAPPING);
    p2_obj->setBitmap(player_bitmap, 4, 32);
    p2_obj->move(110, 20);
    this->gameEnv_.add_controlableObj(p2_obj);
}

int askForOnlineViaGUI(GraphEnv &graph_env, SoftwareSerial &controllerInput){
    Serial.println("asking");
    GUISpace guiEnv_(graph_env, controllerInput);

    int yes = 0;

    std::shared_ptr<ButtonWidget> play_online_btn = std::make_shared<ButtonWidget>("online");
    play_online_btn->setLabel("online");
    play_online_btn->setGridI(0);
    play_online_btn->setGridJ(0);
    play_online_btn->move(0, 10);
    play_online_btn->setAButtonPressedCallback([&yes, &guiEnv_](InteractableWidget *w){
        guiEnv_.getSaturnRef().interrupt();
        yes = 1;
    });
    guiEnv_.addInteractableWidget(play_online_btn);

    std::shared_ptr<ButtonWidget> play_offline_btn = std::make_shared<ButtonWidget>("offline");
    play_offline_btn->setLabel("offline");
    play_offline_btn->setGridI(1);
    play_offline_btn->setGridJ(0);
    play_offline_btn->move(0, 30);
    play_offline_btn->setAButtonPressedCallback([&yes, &guiEnv_](InteractableWidget *w){
        guiEnv_.getSaturnRef().interrupt();
        yes = 0;
    });
    guiEnv_.addInteractableWidget(play_offline_btn);

    guiEnv_.init();
    guiEnv_.getSaturnRef().run();

    return yes;
}