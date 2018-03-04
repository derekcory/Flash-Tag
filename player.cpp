#pragma once
#include <SDL.h>
#include "player.h"
#include "map.h"
#include <ctime>
#include <vector>
#include "aiplayer.h"

SDL_Rect DestR;
extern int currentPowerUpX;
extern int currentPowerUpY;
extern int powerTileValue;
extern int currentPowerUp;

Player::Player()
{
    posX = 5; //Arbitrary values. Spawn point is randomly generated
    posY = 12;
    lastMove = NULL;
    powerUp;
    pointMultiplier = 1;
    visionRange = 1;
    score = 0;  //keeps score
    powerUpEnabled = false;
    powerUpInUse = 0;
    powerExpire;
    viewDistance = 8;
}

int Player::getPosX()
{
    return posX;
}

int Player::getPosY()
{
    return posY;
}

char Player::getLastMove()
{
    return lastMove;
}

int Player::getViewDistance()
{
    return viewDistance;
}

void Player::setPosX(int newX)
{
    posX = newX;
}

void Player::setPosY(int newY)
{
    posY = newY;
}

int Player::getscore()
{
    return score;
}

void Player::drawPlayer(SDL_Renderer *renderer, SDL_Texture* player)
{
    DestR.x = getPosY()*TILE_WIDTH;
    DestR.y = getPosX()*TILE_HEIGHT;
    DestR.w = TILE_WIDTH;
    DestR.h = TILE_HEIGHT;
    SDL_RenderCopy(renderer, player, NULL, &DestR);
}

void Player::generateMove(SDL_Event& e, Map board)
{
    int tempMove;
    if( e.type == SDL_KEYDOWN)
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
        {
            lastMove = 'w';
            tempMove = getPosX() - 1;
            if(tempMove < 0)
            {
                // Do nothing
            }
            else
            {
                if ((getMapValue(board, getPosY(), tempMove) == 6))
                {
                    score = 1 * pointMultiplier + score;    //increase score if tags ai
                    taggedSound();
                }
                if ((getMapValue(board, getPosY(), tempMove) == 1) || (getMapValue(board, getPosY(), tempMove) == 7))
                {
                    // Do Nothing
                }
                else
                {
                    playMovementSound();
                    setPosX(tempMove);
                    if((getMapValue(board, getPosY(), tempMove) == 2) || (getMapValue(board, getPosY(), tempMove) == 3) || (getMapValue(board, getPosY(), tempMove) == 4))
                    {
                        addPowerUp((getMapValue(board, getPosY(), tempMove)));
                    }
                }
            }
            //  std::cout << "X: " << getPosY() << " Y: " << getPosX() << std::endl;
            // std::cout << "Value is: " << getMapValue(board, getPosY(), getPosX()) << std::endl;
            //std::cout << "Power ups: " << std::endl;
//                printPowerUps();
            break;
        }

        case SDLK_s:
        {
            lastMove = 's';
            tempMove = getPosX() + 1;
            if(tempMove > (MAX_MAP_Y - 1))
            {
                // Do nothing
            }
            else
            {
                if ((getMapValue(board, getPosY(), tempMove) == 6))
                {
                    score = 1 * pointMultiplier + score; //increase score if tags ai
                    taggedSound();
                }
                if ((getMapValue(board, getPosY(), tempMove) == 1) || (getMapValue(board, getPosY(), tempMove) == 7))
                {
                    // Do Nothing
                }
                else
                {
                    playMovementSound();
                    setPosX(tempMove);
                    if((getMapValue(board, getPosY(), tempMove) == 2) || (getMapValue(board, getPosY(), tempMove) == 3) || (getMapValue(board, getPosY(), tempMove) == 4))
                    {
                        addPowerUp((getMapValue(board, getPosY(), tempMove)));
                    }
                }
            }
            //    std::cout << "X: " << getPosY() << " Y: " << getPosX() << std::endl;
            //   std::cout << "Value is: " << getMapValue(board, getPosY(), getPosX()) << std::endl;
            //  std::cout << "Power ups: " << std::endl;
//                printPowerUps();
            break;
        }

        case SDLK_a:
        {
            lastMove = 'a';
            tempMove = getPosY() - 1;
            if(tempMove < 0)
            {
                // Do nothing
            }
            else
            {
                if ((getMapValue(board, tempMove, getPosX()) == 6))
                {
                    score = 1 * pointMultiplier + score; //increase score if tags ai
                    taggedSound();
                }
                if ((getMapValue(board, tempMove, getPosX())== 1) || (getMapValue(board, tempMove, getPosX())== 7))
                {
                    // Do Nothing
                }
                else
                {
                    playMovementSound();
                    setPosY(tempMove);
                    if((getMapValue(board, getPosY(), getPosX()) == 2) || (getMapValue(board, getPosY(), getPosX()) == 3) || (getMapValue(board, getPosY(), getPosX()) == 4))
                    {
                        addPowerUp((getMapValue(board, tempMove, getPosX())));
                    }
                }
            }
            // std::cout << "X: " << getPosY() << " Y: " << getPosX() << std::endl;
            //std::cout << "Value is: " << getMapValue(board, getPosY(), getPosX()) << std::endl;
            //std::cout << "Power ups: " << std::endl;
//                printPowerUps();
            break;
        }

        case SDLK_d:
        {
            lastMove = 'd';
            tempMove = getPosY() + 1;
            if(tempMove > (MAX_MAP_X - 1))
            {
                // Do nothing
            }
            else
            {
                if ((getMapValue(board, tempMove, getPosX()) == 6))
                {
                    score = 1 * pointMultiplier + score; //increase score if tags ai
                    taggedSound();
                }
                if ((getMapValue(board, tempMove, getPosX()) == 1) || (getMapValue(board, tempMove, getPosX()) == 7))
                {
                    // Do Nothing
                }
                else
                {
                    playMovementSound();
                    setPosY(tempMove);
                    if((getMapValue(board, getPosY(), getPosX()) == 2) || (getMapValue(board, getPosY(), getPosX()) == 3) || (getMapValue(board, getPosY(), getPosX()) == 4))
                    {
                        addPowerUp((getMapValue(board, tempMove, getPosX())));
                    }
                }
            }
            //std::cout << "X: " << getPosY() << " Y: " << getPosX() << std::endl;
            //std::cout << "Value is: " << getMapValue(board, getPosY(), getPosX()) << std::endl;
            //std::cout << "Power ups: " << std::endl;
//                printPowerUps();
            break;
        }

        case SDLK_SPACE:
        {
            //std::cout << "Power ups before use: " << std::endl;
//                printPowerUps();
            usePowerUp();
            //std::cout << "Power ups after use: " << std::endl;
//                printPowerUps();
            break;
        }

        default:
            break; //End of default case
        }
    }
}

void Player::playerPrintMap(Map board)
{
    for(int y = 0; y < MAX_MAP_Y; y++)
    {
        for(int x = 0; x < MAX_MAP_X; x++)
        {
            std::cout << board.tile[y][x];
        }
        std::cout << "\n";
    }
}

void Player::setStartPos(Map board)
{
    srand(time(NULL));
    bool done = false;

    while(!done)
    {
        int tempX = (rand()%MAX_MAP_Y);
        int tempY = (rand()%MAX_MAP_X);

        if((getMapValue(board, tempY, tempX) == 0) || (getMapValue(board, tempY, tempX) == 8))
        {
            setPosX(tempX);
            setPosY(tempY);
            done = true;
        }

        else
        {
            done = false;
        }
    }
}

void Player::addPowerUp(int power)
{
    if(powerUp.size() == 0)
    {
        powerUp.push_back(power);
    }
    else
    {
        powerUp.erase(powerUp.begin());
        powerUp.push_back(power);
    }
}

int Player::puinvent()
{
    if(powerUp.empty())
    {
        return 0;
    }
    else if(powerUp.at(0)==2)
    {
        return 2;
    }
    else if(powerUp.at(0)==3)
    {
        return 3;
    }
}

void Player::usePowerUp()
{
    pointMultiplier = 1;
    viewDistance = 8;

    if(!powerUp.empty())
    {
        double startTime = SDL_GetTicks();
        powerExpire = startTime + 20000;
        int tempPowerUp = powerUp.at(0);
        powerUp.erase(powerUp.begin());
        powerUpEnabled = true;
        powerUpInUse = tempPowerUp;

        switch(tempPowerUp)
        {
        case 2:
        {
           // std::cout << "You used the double points power up!" << std::endl;
            pointMultiplier = 2;
            break;
        }

        case 3:
        {
           // std::cout << "You used the increased vision power up!" << std::endl;
            viewDistance = 14;
            break;
        }

        default:
            break;
        }
    }
    else
    {
       // std::cout << "You don't have any PowerUps to use!" << std::endl;
    }
}

void Player::playMovementSound()
{
    Mix_Chunk *movementSound = Mix_LoadWAV("footsteps.wav");
    Mix_VolumeChunk(movementSound, MIX_MAX_VOLUME);
    if(!movementSound){

    }
    else
        Mix_PlayChannel( -1, movementSound, 0 );
}

void Player::taggedSound()
{
    Mix_Chunk *tagSound = Mix_LoadWAV("tagged.wav");
    Mix_VolumeChunk(tagSound, MIX_MAX_VOLUME);
    if(!tagSound){}
    else
        Mix_PlayChannel( -1, tagSound, 0 );
}
