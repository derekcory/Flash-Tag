#include <SDL.h>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <SDL_ttf.h>
#include "Timer_Scoreboard.h"
#include "SDL_image.h"
#include "map.h"
#include "player.h"
#include "randmap.h"
#include "aiplayer.h"
#include "SDL_Mixer.h"

using namespace std;

int currentPowerUpX = 1;
int currentPowerUpY = 2;
int powerTileValue = 0;
int currentPowerUp = 0;
int ai_count = 5;
const int POWERUP_DELAY = 20;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* houseWall = NULL;
SDL_Texture* playerImage = NULL;
SDL_Texture* houseFloor = NULL;
SDL_Texture* mapBorder = NULL;
SDL_Texture* aiPlayerImage = NULL;
SDL_Texture* aikillerImage = NULL;
SDL_Texture* visionpu = NULL;
SDL_Texture* dppu = NULL;
SDL_Texture* timepu = NULL;
SDL_Texture* grass = NULL;
SDL_Texture* breakWallPower = NULL;
SDL_Texture* doublePointsPower = NULL;
SDL_Texture* increasedVisionPower = NULL;
SDL_Texture* increaseTimePower = NULL;
TTF_Font *font = NULL;
SDL_Color white = {255, 255, 255};

SDL_Texture* LoadTexture( const std::string &str )
{
    SDL_Surface* surface = IMG_Load( str.c_str() );
    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_FreeSurface( surface );
    return texture;
}

int main(int argc, char *argv[])
{
    Map board;
    Player player;
    string score;
    string timer;
    int currentScore = 0;
    int gameLength = 30;
    aiplayer ai_player[ai_count];
    aiplayer ai_killer[ai_count];

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("Not initialize");
    }

    else
    {
        window = SDL_CreateWindow("Tile Board", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(window == NULL)
        {
            //printf("window could not be created");
        }

        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer == NULL)
            {
               // printf("Renderer could not be created");
            }

            else
            {
                TTF_Init();
                font = TTF_OpenFont("arial.ttf", 24);
                aiPlayerImage = LoadTexture("blue-circle.png");
                aikillerImage = LoadTexture("purple-circle.png");
                visionpu = LoadTexture("red-circle_vision.png");
                dppu = LoadTexture("red-circle_dp.png");
                timepu = LoadTexture("red-circle_time.png");
                mapBorder = LoadTexture("mapBorder2.png");
                houseWall = LoadTexture("houseWall.jpg");
                playerImage = LoadTexture("red-circle.png");
                houseFloor = LoadTexture("houseFloor.png");
                grass = LoadTexture("grass.png");
                breakWallPower = LoadTexture("hammer.png");
                doublePointsPower = LoadTexture("doublePoints.png");
                increasedVisionPower = LoadTexture("vision.png");
                increaseTimePower = LoadTexture("timer.png");
                createRandomMap(); //testing random map creation here
                board = loadMap("Map.txt", board);
                drawMap(renderer, board, player.getPosY(), player.getPosX(), player.getLastMove(),player.viewDistance, mapBorder, houseWall, houseFloor, grass, aiPlayerImage, aikillerImage);
            }
        }
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf ("SDL MIXER ERROR: %s", Mix_GetError());
    }

    Mix_Music *bgMusic = Mix_LoadMUS("bgMusic.wav");

    if (bgMusic == NULL){

    }
        //printf("There is no music");

    int quit = 0;
    SDL_Event e;

    time_t begin, end;
    double elapsed;
    time(&begin);
    player.setStartPos(board);
    for(int q = 0; q < ai_count; q++)
    {
        //places all the ai
        ai_player[q].setAiStartPos(board);
        board.tile[ai_player[q].getAIPosX()][ai_player[q].getAIPosY()] = 6;
        ai_killer[q].setAiStartPos(board);
        board.tile[ai_killer[q].getAIPosX()][ai_killer[q].getAIPosY()] = 9;
    }


    player.setStartPos(board);
    while(!quit)
    {
        if(!Mix_PlayingMusic())
        {
            Mix_PlayMusic(bgMusic, -1);
            Mix_VolumeMusic(MIX_MAX_VOLUME/16);
        }
        int elapsedTime = SDL_GetTicks()/1000;
        if(elapsedTime == gameLength)
        {

            Mix_Chunk *gameover2 = Mix_LoadWAV("gameover.wav");
            Mix_VolumeChunk(gameover2, MIX_MAX_VOLUME);
            Mix_PlayChannel( -1, gameover2, 0 );
            string name2 = "";
            std::ofstream myfile;
            myfile.open("highscore.txt", std::ofstream::app);
            cout << "Please Enter Name: ";
            getline(cin, name2);
            myfile << name2 << ": "<< player.getscore();
            myfile << "\n";
            myfile.close();
            string filename = "notepad \"highscore\"";
            system(filename.c_str());
            quit = 1;
        }

        if(player.powerUpEnabled && player.powerExpire < SDL_GetTicks())
        {
            player.powerUpInUse = 0;
            player.drawPlayer(renderer, playerImage);
            player.pointMultiplier = 1;
            player.viewDistance = 8;
            player.powerUpEnabled = false;
        }

        elapsed = difftime(end, begin);
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = 1;
            else if (e.type == SDL_KEYDOWN)
            {
                player.generateMove(e, board);
                if(board.tile[player.getPosX()][player.getPosY()] == 6)
                {
                    gameLength += 5;
                    for(int q = 0; q < ai_count; q++)
                    {
                        if(player.getPosX() == ai_player[q].getAIPosX() && player.getPosY() == ai_player[q].getAIPosY())
                        {
                            board.tile[ai_player[q].getAIPosX()][ai_player[q].getAIPosY()] = 0;
                            ai_player[q].setAiStartPos(board);
                            board.tile[ai_player[q].getAIPosX()][ai_player[q].getAIPosY()] = 6;
                            break;
                        }
                    }
                }
                for(int q = 0; q < ai_count; q++)
                {
                    // generates move after player, so player will land on AI and then AI will move
                    board.tile[ai_player[q].getAIPosX()][ai_player[q].getAIPosY()] = 0;
                    ai_player[q].generateAiMove(board);
                    board.tile[ai_player[q].getAIPosX()][ai_player[q].getAIPosY()] = 6;
                    board.tile[ai_killer[q].getAIPosX()][ai_killer[q].getAIPosY()] = 0;
                    ai_killer[q].generateAikillerMove(board, player);
                    board.tile[ai_killer[q].getAIPosX()][ai_killer[q].getAIPosY()] = 9;
                }
                if(board.tile[player.getPosX()][player.getPosY()] == 9)
                {
                    /*for(int q = 0; q < ai_count; q++)
                    {
                    board.tile[ai_killer[q].getAIPosX()][ai_killer[q].getAIPosY()] = 0;
                    ai_killer[q].setAiStartPos(board);
                    board.tile[ai_killer[q].getAIPosX()][ai_killer[q].getAIPosY()] = 9;
                    }*/
                    Mix_Chunk *gameover = Mix_LoadWAV("gameover.wav");
                    Mix_VolumeChunk(gameover, MIX_MAX_VOLUME);
                    Mix_PlayChannel( -1, gameover, 0 );
                    string name = "";
                    std::ofstream myfile;
                    myfile.open("highscore.txt", std::ofstream::app);
                    cout << "Please Enter Name: ";
                    getline(cin, name);
                    myfile << name << ": "<< player.getscore();
                    myfile << "\n";
                    myfile.close();
                    string filename = "notepad \"highscore\"";
                    system(filename.c_str());
                    quit = 1;
                    break;
                }
            }
        }
        drawMap(renderer, board, player.getPosY(), player.getPosX(), player.getViewDistance(), player.getLastMove(), mapBorder, houseWall, houseFloor, grass, aiPlayerImage, aikillerImage);

        if(((int)elapsed % 20) == 0)
        {
            board = resetPowerUp(board);
            generatePowerupLocation(board);
            currentPowerUp = generatePowerUp();
            board.tile[currentPowerUpY][currentPowerUpX] = currentPowerUp;
        }

        else
        {

            if(player.getPosY() == currentPowerUpX && player.getPosX() == currentPowerUpY)
            {
                if(currentPowerUp == 4)
                {
                    currentPowerUp = 0;
                    board = resetPowerUp(board);
                    gameLength += 10;
                }
                board = resetPowerUp(board);
            }
        }
        /*for(int z = 0; z < ai_count; z++)             easyyyy mode
        {  //draws AI
            ai_player[z].drawaiplayer(renderer, aiPlayerImage);
        }*/


        currentScore = player.getscore();
        displayScore(renderer, white, font, currentScore, gameLength, player.puinvent());

        displayPowerUp(renderer, board, breakWallPower, doublePointsPower, increasedVisionPower, increaseTimePower);
        if(player.powerUpInUse == 0 || player.powerUpInUse == 4)
        {
            //cout <<"current is " << player.powerUpInUse <<"\n";
            player.drawPlayer(renderer, playerImage);
        }
        else if (player.powerUpInUse == 2)
        {
            //cout <<"current is " << player.powerUpInUse <<"\n";
            player.drawPlayer(renderer, dppu);
        }
        else if (player.powerUpInUse == 3)
        {
            // cout <<"current is " << player.powerUpInUse <<"\n";
            player.drawPlayer(renderer, visionpu);
        }

        SDL_RenderPresent(renderer);
        time(&end);
    }
    //cout << currentScore;
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(mapBorder);
    SDL_DestroyTexture(houseWall);
    SDL_DestroyTexture(playerImage);
    SDL_DestroyTexture(aiPlayerImage);
    SDL_DestroyTexture(aikillerImage);
    SDL_DestroyTexture(visionpu);
    SDL_DestroyTexture(dppu);
    SDL_DestroyTexture(timepu);
    SDL_DestroyTexture(houseFloor);
    SDL_DestroyTexture(breakWallPower);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
