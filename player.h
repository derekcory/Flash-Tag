#pragma once
#include "map.h"
#include <vector>
#include "SDL_Mixer.h"

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Player
{
public:

    static const int PLAYER_WIDTH = 20;
    static const int PLAYER_HEIGHT = 20;

    //Init a Player
    Player();

    void drawPlayer(SDL_Renderer *renderer, SDL_Texture* player);

    void playerPrintMap(Map board);

    void generateMove( SDL_Event& e, Map board);

    void setCamera(SDL_Rect& camera);

    void setStartPos(Map board);

    void addPowerUp(int power);

    void printPowerUps();

    int getscore();

    void usePowerUp();

    void playMovementSound();
    void taggedSound();

    //Position accessors
    int getPosX();
    int getPosY();
    char getLastMove();
    int getViewDistance();
    int puinvent();

    //Position setters
    void setPosX(int newX);
    void setPosY(int newY);
    bool powerUpEnabled;
    int powerUpInUse;
    double powerExpire;
    int viewDistance;
    int pointMultiplier;

private:
    int posX, posY;
    char lastMove;
    std::vector<int> powerUp;
//		int pointMultiplier;
    int visionRange;
    int score;
};
