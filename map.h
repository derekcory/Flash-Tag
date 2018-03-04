#pragma once
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

//#include "SDL_mixer.h"

const int TILE_WIDTH = 20;
const int TILE_HEIGHT = 20;

const int MAX_MAP_Y = 30;
const int MAX_MAP_X = 40;

const int LEVEL_WIDTH = MAX_MAP_X * TILE_WIDTH;
const int LEVEL_HEIGHT = MAX_MAP_Y * TILE_HEIGHT;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//const int SCREEN_WIDTH = 1280;
//const int SCREEN_HEIGHT = 800;

const int VIEW_DISTANCE = 8;

extern int currentPowerUpX;
extern int currentPowerUpY;
extern int powerTileValue;
extern int currentPowerUp;

extern SDL_Rect DestR;



typedef struct Map
{
    int tile[MAX_MAP_Y][MAX_MAP_X];
} Map;

inline Map loadMap(char *name, Map board)
{
    std::ifstream MapFile(name);
    if(MapFile)
    {
        for(int y = 0; y < MAX_MAP_Y; y++)
        {
            for(int x = 0; x < MAX_MAP_X; x++)
            {
                MapFile >> board.tile[y][x];
            }
        }
        return board;
    }
    else
        printf("Failed to open %s \n", name);
}

inline void printMap(Map board)
{
    for(int y = 0; y < MAX_MAP_Y; y++)
    {
        for(int x = 0; x < MAX_MAP_X; x++)
        {
            std::cout << board.tile[y][x] << " ";
        }
        std::cout << "\n";
    }
}

inline void drawMap(SDL_Renderer *renderer, Map board, int playerX, int playerY, int viewDistance, char lastMove, SDL_Texture* mapBorder, SDL_Texture* houseWall, SDL_Texture* houseFloor, SDL_Texture* grass, SDL_Texture* aiPlayerImage, SDL_Texture* aikillerImage)
{
    SDL_RenderClear(renderer);

    int x = 0;
    int y = 0;
    int quad = 0;

    /** Draws field of view based on movement **/

    while(quad < 2)
    {
        int temp = viewDistance;
        int i = 0;
        int j = 0;

        switch(lastMove)
        {
        case 'w':
            if(quad == 0)
            {
                i = -1;
                j = -1;
            }
            else
            {
                i = 1;
                j = -1;
            }
            break;

        case 'a':
            if(quad == 0)
            {
                i = -1;
                j =  -1;
            }
            else
            {
                i = 1;
                j = -1;
            }
            break;

        case 's':
            if(quad == 0)
            {
                i = -1;
                j =  1;
            }
            else
            {
                i = 1;
                j = 1;
            }
            break;

        case 'd':
            if(quad == 0)
            {
                i = -1;
                j = 1;
            }
            else
            {
                i = 1;
                j = 1;
            }
            break;

        default:
            break;
        }

        for(int row = 0; row < temp; row++)
        {
            for(int col = 0; col < row; col++)
            {
                /** Draw FOV octant **/
                if (quad == 0)
                {
                    if(lastMove == 'a' || lastMove =='d')
                    {
                        x = playerX + row*j;
                        y = playerY + col*i;
                    }
                    else
                    {
                        x = playerX + col*i;
                        y = playerY + row*j;
                    }
                }
                /** Draw 2nd FOV octant**/
                if (quad == 1)
                {
                    if(lastMove == 'a' || lastMove =='d')
                    {
                        x = playerX + row*j;
                        y = playerY + col*i;
                    }
                    else
                    {
                        x = playerX + col*i;
                        y = playerY + row*j;
                    }
                }
                if (board.tile[y][x] == 9)
                {
                    DestR.x = x*TILE_WIDTH;
                    DestR.y = y*TILE_HEIGHT;
                    DestR.w = TILE_WIDTH;
                    DestR.h = TILE_HEIGHT;
                    SDL_RenderCopy(renderer, aikillerImage, NULL, &DestR);
                }
                if (board.tile[y][x] == 8)
                {
                    DestR.x = x*TILE_WIDTH;
                    DestR.y = y*TILE_HEIGHT;
                    DestR.w = TILE_WIDTH;
                    DestR.h = TILE_HEIGHT;
                    SDL_RenderCopy(renderer, houseFloor, NULL, &DestR);
                }

                if (board.tile[y][x] == 7)
                {
                    DestR.x = x*TILE_WIDTH;
                    DestR.y = y*TILE_HEIGHT;
                    DestR.w = TILE_WIDTH;
                    DestR.h = TILE_HEIGHT;
                    SDL_RenderCopy(renderer, mapBorder, NULL, &DestR);
                }

                if (board.tile[y][x] == 6)
                {
                    DestR.x = x*TILE_WIDTH;
                    DestR.y = y*TILE_HEIGHT;
                    DestR.w = TILE_WIDTH;
                    DestR.h = TILE_HEIGHT;
                    SDL_RenderCopy(renderer, aiPlayerImage, NULL, &DestR);
                }

                if (board.tile[y][x] == 1)
                {
                    DestR.x = x*TILE_WIDTH;
                    DestR.y = y*TILE_HEIGHT;
                    DestR.w = TILE_WIDTH;
                    DestR.h = TILE_HEIGHT;
                    SDL_RenderCopy(renderer, houseWall, NULL, &DestR);
                }

                if (board.tile[y][x] == 0)
                {
                    DestR.x = x*TILE_WIDTH;
                    DestR.y = y*TILE_HEIGHT;
                    DestR.w = TILE_WIDTH;
                    DestR.h = TILE_HEIGHT;
                    SDL_RenderCopy(renderer, grass, NULL, &DestR);
                }
            }
        }
        quad++;
    }
    /** Draws view around player **/
    for(int row = -2; row < 3; row++)
    {
        y = playerY + row;
        for(int col = -2; col < 3; col++)
        {
            x = playerX + col;
            if (board.tile[y][x] == 9)
            {
                DestR.x = x*TILE_WIDTH;
                DestR.y = y*TILE_HEIGHT;
                DestR.w = TILE_WIDTH;
                DestR.h = TILE_HEIGHT;
                SDL_RenderCopy(renderer, aikillerImage, NULL, &DestR);
            }
            if (board.tile[y][x] == 8)
            {
                DestR.x = x*TILE_WIDTH;
                DestR.y = y*TILE_HEIGHT;
                DestR.w = TILE_WIDTH;
                DestR.h = TILE_HEIGHT;
                SDL_RenderCopy(renderer, houseFloor, NULL, &DestR);
            }

            if (board.tile[y][x] == 7)
            {
                DestR.x = x*TILE_WIDTH;
                DestR.y = y*TILE_HEIGHT;
                DestR.w = TILE_WIDTH;
                DestR.h = TILE_HEIGHT;
                SDL_RenderCopy(renderer, mapBorder, NULL, &DestR);
            }

            if (board.tile[y][x] == 6)
            {
                DestR.x = x*TILE_WIDTH;
                DestR.y = y*TILE_HEIGHT;
                DestR.w = TILE_WIDTH;
                DestR.h = TILE_HEIGHT;
                SDL_RenderCopy(renderer, aiPlayerImage, NULL, &DestR);
            }

            if (board.tile[y][x] == 1)
            {
                DestR.x = x*TILE_WIDTH;
                DestR.y = y*TILE_HEIGHT;
                DestR.w = TILE_WIDTH;
                DestR.h = TILE_HEIGHT;
                SDL_RenderCopy(renderer, houseWall, NULL, &DestR);
            }

            if (board.tile[y][x] == 0)
            {
                DestR.x = x*TILE_WIDTH;
                DestR.y = y*TILE_HEIGHT;
                DestR.w = TILE_WIDTH;
                DestR.h = TILE_HEIGHT;
                SDL_RenderCopy(renderer, grass, NULL, &DestR);
            }
        }
    }
}

inline int getMapValue(Map board, int xPos, int yPos)
{
    return board.tile[yPos][xPos];
}

inline Map generatePowerupLocation(Map board)
{
    srand(time(NULL));
    int done = 0;
    while(done != 1)
    {
        int tempX = ((rand()%MAX_MAP_X));
        int tempY =  ((rand()%MAX_MAP_Y));
        if((board.tile[tempY][tempX] == 0) || (board.tile[tempY][tempX] == 8))
        {
            powerTileValue = board.tile[tempY][tempX];
            currentPowerUpX = tempX;
            currentPowerUpY = tempY;
            done = 1;
        }
    }
}

inline void displayPowerUp(SDL_Renderer* renderer, Map board, SDL_Texture* breakWallPower, SDL_Texture* doublePointsPower, SDL_Texture* increasedVisionPower, SDL_Texture* increaseTimePower)
{
    if(board.tile[currentPowerUpY][currentPowerUpX] == 2)
    {
        DestR.x = currentPowerUpX*TILE_WIDTH;
        DestR.y = currentPowerUpY*TILE_HEIGHT;
        DestR.w = TILE_WIDTH;
        DestR.h = TILE_HEIGHT;
        SDL_RenderCopy(renderer, doublePointsPower, NULL, &DestR);
    }

    else if(board.tile[currentPowerUpY][currentPowerUpX] == 3)
    {
        DestR.x = currentPowerUpX*TILE_WIDTH;
        DestR.y = currentPowerUpY*TILE_HEIGHT;
        DestR.w = TILE_WIDTH;
        DestR.h = TILE_HEIGHT;
        SDL_RenderCopy(renderer, increasedVisionPower, NULL, &DestR);
    }

    else if(board.tile[currentPowerUpY][currentPowerUpX] == 4)
    {
        DestR.x = currentPowerUpX*TILE_WIDTH;
        DestR.y = currentPowerUpY*TILE_HEIGHT;
        DestR.w = TILE_WIDTH;
        DestR.h = TILE_HEIGHT;
        SDL_RenderCopy(renderer, increaseTimePower, NULL, &DestR);
    }

    else if(board.tile[currentPowerUpY][currentPowerUpX] == 5)
    {
        DestR.x = currentPowerUpX*TILE_WIDTH;
        DestR.y = currentPowerUpY*TILE_HEIGHT;
        DestR.w = TILE_WIDTH;
        DestR.h = TILE_HEIGHT;
        SDL_RenderCopy(renderer, breakWallPower, NULL, &DestR);
    }
}

inline Map resetPowerUp(Map board)
{
    board.tile[currentPowerUpY][currentPowerUpX] = powerTileValue;
    //currentPowerUpX = NULL;
    //currentPowerUpY = NULL;
    return board;
}

inline int generatePowerUp()
{
    srand(time(NULL));
    int done = 0;
    while(done != 1)
    {
        int tempPower = rand()%5;
        if(tempPower == 2 || tempPower == 3 || tempPower == 4)//if(tempPower == 2 || tempPower == 3 || tempPower == 4 || tempPower == 5)
        {
            return tempPower; //needs to be changed to tempPower to ensure all power ups can spawn
        }
    }
}
