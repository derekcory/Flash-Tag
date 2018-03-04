#include "map.h"
#include <vector>
#include "player.h"
//#include "SDL_Mixer.h"

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class aiplayer
{
public:

    static const int aiplayer_WIDTH = 20;
    static const int aiplayer_HEIGHT = 20;

    //Init a aiplayer
    aiplayer();

    void drawaiplayer(SDL_Renderer *renderer, SDL_Texture* aiplayer);

    void generateAiMove(Map board);

    void generateAikillerMove(Map board, Player play);

    void setAiStartPos(Map board);

    void playAIMovementSound();

    //Position accessors
    int getAIPosX();
    int getAIPosY();

    //Position setters
    void setAIPosX(int newX);
    void setAIPosY(int newY);

private:
    int posX, posY;
    char lastMove;
    std::vector<int> powerUp;
    int pointMultiplier;
    int visionRange;
};
