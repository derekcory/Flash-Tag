#include <SDL.h>
#include "aiplayer.h"
#include "player.h"
#include "map.h"
#include <ctime>
#include <vector>

extern SDL_Rect DestR;
extern int powerTileValue;

aiplayer::aiplayer()
{
    posX = 5; //Arbitrary values. Spawn point is randomly generated
    posY = 12;
    lastMove = NULL;
    pointMultiplier = 1;
    visionRange = 1;
    srand(time(NULL));  //allows random position thats different from player
}

int aiplayer::getAIPosX()
{
    return posX;
}

int aiplayer::getAIPosY()
{
    return posY;
}

void aiplayer::setAIPosX(int newX)
{
    posX = newX;
}

void aiplayer::setAIPosY(int newY)
{
    posY = newY;
}

void aiplayer::drawaiplayer(SDL_Renderer *renderer, SDL_Texture* aiplayer)
{
    DestR.x = getAIPosY()*TILE_WIDTH;
    DestR.y = getAIPosX()*TILE_HEIGHT;
    DestR.w = TILE_WIDTH;
    DestR.h = TILE_HEIGHT;
    SDL_RenderCopy(renderer, aiplayer, NULL, &DestR);
}

void aiplayer::generateAiMove(Map board)
{
    int tempMove;
    int action = rand() % 4 + 1;    // random 1 -4
    switch( action )
    {
    case 1:
    {
        tempMove = getAIPosX() - 1;
        if(tempMove < 0)
        {
            // Do nothing
        }
        else
        {
            if ((getMapValue(board, getAIPosY(), tempMove) == 1) || (getMapValue(board, getAIPosY(), tempMove) == 7) || (getMapValue(board, getAIPosY(), tempMove) == 9) || (getMapValue(board, getAIPosY(), tempMove) == 6))
            {
                // Do Nothing
            }
            else
            {
//                        playAIMovementSound();
                //lastMove = 'w';
                setAIPosX(tempMove);
            }
        }
        //  std::cout << "X: " << getAIPosY() << " Y: " << getAIPosX() << std::endl;
        //  std::cout << "Value is: " << getMapValue(board, getAIPosY(), getAIPosX()) << std::endl;
        //  std::cout << "Power ups: " << std::endl;
//                printPowerUps();
        break;
    }

    case 2:
    {
        tempMove = getAIPosX() + 1;
        if(tempMove > (MAX_MAP_Y - 1))
        {
            // Do nothing
        }
        else
        {
            if ((getMapValue(board, getAIPosY(), tempMove) == 1) || (getMapValue(board, getAIPosY(), tempMove) == 7) || (getMapValue(board, getAIPosY(), tempMove) == 9) || (getMapValue(board, getAIPosY(), tempMove) == 6))
            {
                // Do Nothing
            }
            else
            {
                //                 playAIMovementSound();
                //lastMove = 's';
                setAIPosX(tempMove);
            }
        }
        //std::cout << "X: " << getAIPosY() << " Y: " << getAIPosX() << std::endl;
        //std::cout << "Value is: " << getMapValue(board, getAIPosY(), getAIPosX()) << std::endl;
        //std::cout << "Power ups: " << std::endl;
//                printPowerUps();
        break;
    }

    case 3:
    {
        tempMove = getAIPosY() - 1;
        if(tempMove < 0)
        {
            // Do nothing
        }
        else
        {
            if ((getMapValue(board, tempMove, getAIPosX())== 1) || (getMapValue(board, tempMove, getAIPosX())== 7) || (getMapValue(board, getAIPosX(), tempMove) == 9) || (getMapValue(board, getAIPosX(), tempMove) == 6))
            {
                // Do Nothing
            }
            else
            {
//                       playAIMovementSound();
                // lastMove = 'a';
                setAIPosY(tempMove);
            }
        }
        //std::cout << "X: " << getAIPosY() << " Y: " << getAIPosX() << std::endl;
        //std::cout << "Value is: " << getMapValue(board, getAIPosY(), getAIPosX()) << std::endl;
        //std::cout << "Power ups: " << std::endl;
//                printPowerUps();
        break;
    }

    case 4:
    {
        tempMove = getAIPosY() + 1;
        if(tempMove > (MAX_MAP_X - 1))
        {
            // Do nothing
        }
        else
        {
            if ((getMapValue(board, tempMove, getAIPosX()) == 1) || (getMapValue(board, tempMove, getAIPosX()) == 7) || (getMapValue(board, getAIPosX(), tempMove) == 9) || (getMapValue(board, getAIPosX(), tempMove) == 6))
            {
                // Do Nothing
            }
            else
            {
                //                     playAIMovementSound();
                // lastMove = 'd';
                setAIPosY(tempMove);
            }
        }
        //std::cout << "X: " << getAIPosY() << " Y: " << getAIPosX() << std::endl;
        //std::cout << "Value is: " << getMapValue(board, getAIPosY(), getAIPosX()) << std::endl;
        //std::cout << "Power ups: " << std::endl;
//                printPowerUps();
        break;
    }

    default:
        break; //End of default case
    }
}

void aiplayer::generateAikillerMove(Map board, Player play)
{
    int tempMove;

    if(play.getPosX() == getAIPosX() - 1 || play.getPosX() == getAIPosX() - 2 || play.getPosX() == getAIPosX() - 3 || (play.getPosX() == getAIPosX() - 1 && play.getPosY() == getAIPosY() + 1 ) || (play.getPosX() == getAIPosX() - 2 && play.getPosY() == getAIPosY() + 2 ) || (play.getPosX() == getAIPosX() - 3 && play.getPosY() == getAIPosY() + 3 ) || (play.getPosX() == getAIPosX() - 1 && play.getPosY() == getAIPosY() - 1 ) || (play.getPosX() == getAIPosX() - 2 && play.getPosY() == getAIPosY() - 2 ) || (play.getPosX() == getAIPosX() - 3 && play.getPosY() == getAIPosY() - 3 ))
    {
        tempMove = getAIPosX() - 1;
        if ((getMapValue(board, getAIPosY(), tempMove) == 1) || (getMapValue(board, getAIPosY(), tempMove) == 7) || (getMapValue(board, getAIPosY(), tempMove) == 9) || (getMapValue(board, getAIPosY(), tempMove) == 6))
        {
            generateAiMove(board);
        }
        else
        {
            setAIPosX(tempMove);
        }
    }
    else if(play.getPosX() == getAIPosX() + 1 || play.getPosX() == getAIPosX() + 2 || play.getPosX() == getAIPosX() + 3 || (play.getPosX() == getAIPosX() + 1 && play.getPosY() == getAIPosY() + 1 ) || (play.getPosX() == getAIPosX() + 2 && play.getPosY() == getAIPosY() + 2 ) || (play.getPosX() == getAIPosX() + 3 && play.getPosY() == getAIPosY() + 3 ) || (play.getPosX() == getAIPosX() + 1 && play.getPosY() == getAIPosY() - 1 ) || (play.getPosX() == getAIPosX() + 2 && play.getPosY() == getAIPosY() - 2 ) || (play.getPosX() == getAIPosX() + 3 && play.getPosY() == getAIPosY() - 3 ))
    {
        tempMove = getAIPosX() + 1;
        if ((getMapValue(board, getAIPosY(), tempMove) == 1) || (getMapValue(board, getAIPosY(), tempMove) == 7) || (getMapValue(board, getAIPosY(), tempMove) == 9) || (getMapValue(board, getAIPosY(), tempMove) == 6))
        {
            generateAiMove(board);
        }
        else
        {
            setAIPosX(tempMove);
        }
    }
    else if(play.getPosY() == getAIPosY() - 1 || play.getPosY() == getAIPosY() - 2 || play.getPosY() == getAIPosY() - 3)
    {
        tempMove = getAIPosY() - 1;
        if ((getMapValue(board, tempMove, getAIPosX())== 1) || (getMapValue(board, tempMove, getAIPosX())== 7) || (getMapValue(board, getAIPosX(), tempMove) == 9) || (getMapValue(board, getAIPosX(), tempMove) == 6))
        {
            generateAiMove(board);
        }
        else
        {
            setAIPosY(tempMove);
        }
    }
    else if(play.getPosY() == getAIPosY() + 1 || play.getPosY() == getAIPosY() + 2 || play.getPosY() == getAIPosY() + 3)
    {
        tempMove = getAIPosY() + 1;
        if ((getMapValue(board, tempMove, getAIPosX()) == 1) || (getMapValue(board, tempMove, getAIPosX()) == 7) || (getMapValue(board, getAIPosX(), tempMove) == 9) || (getMapValue(board, getAIPosX(), tempMove) == 6))
        {
            generateAiMove(board);
        }
        else
        {
            setAIPosY(tempMove);
        }
    }
    else
    {
        generateAiMove(board);
    }
}

void aiplayer::setAiStartPos(Map board)
{
    bool done = false;

    while(!done)
    {
        int tempX = (rand()%MAX_MAP_Y);
        int tempY = (rand()%MAX_MAP_X);

        if((getMapValue(board, tempY, tempX) == 0) || (getMapValue(board, tempY, tempX) == 8))
        {
            setAIPosX(tempX);
            setAIPosY(tempY);
            done = true;
        }

        else
        {
            done = false;
        }
    }
}



/*void aiplayer::playAIMovementSound()
{
    Mix_Chunk *movementSound = Mix_LoadWAV("footsteps.wav");
    Mix_VolumeChunk(movementSound, MIX_MAX_VOLUME);
    if(!movementSound)
        printf("There is no footstep sound!");
    else
        Mix_PlayChannel( -1, movementSound, 0 );
}*/
