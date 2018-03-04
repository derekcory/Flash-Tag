#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL_ttf.h>
#include "player.h"

using namespace std;

inline void displayScore(SDL_Renderer* renderer, SDL_Color white, TTF_Font* font, int currentScore, int gameLength, int powerup)
{

    stringstream scoreText;
    scoreText.str("");
    scoreText <<"Score: " << currentScore;

    stringstream timer;
    timer.str("");
    timer <<"Timer: " << (gameLength - SDL_GetTicks()/1000);

    stringstream invent;
    invent.str("");
    if(powerup == 0)
    {
        invent <<"Power up:";
    }
    else if(powerup == 2)
    {
        invent <<"Power up: Double Points";
    }
    else
    {
        invent <<"Power up: Super Flashlight";
    }

    SDL_Texture* message = NULL;
    SDL_Texture* scoreboard = NULL;
    SDL_Texture* inventory = NULL;

    SDL_Surface* timerSurface = TTF_RenderText_Solid(font, timer.str().c_str(), white);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.str().c_str(), white);
    SDL_Surface* inventsurface = TTF_RenderText_Solid(font, invent.str().c_str(), white);


    inventory = SDL_CreateTextureFromSurface(renderer, inventsurface);
    message = SDL_CreateTextureFromSurface(renderer, timerSurface);
    scoreboard = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    SDL_FreeSurface(timerSurface);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(inventsurface);

    SDL_Rect Rect = {0, 0, 100, 75/3};
    SDL_Rect ScoreRect = {110, 0, 100, 75/3};
    SDL_Rect inventRect = {220, 0, 100, 75/3};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderCopy(renderer, inventory, NULL, &inventRect);
    SDL_RenderCopy(renderer, scoreboard, NULL, &ScoreRect);
    SDL_RenderCopy(renderer, message, NULL, &Rect);

    SDL_DestroyTexture(inventory);
    SDL_DestroyTexture(message);
    SDL_DestroyTexture(scoreboard);
}

int addTime(int gameLength)
{
    gameLength += 1;
    return gameLength;
}

int addScore(int currentScore)
{
    currentScore += 1;
    return currentScore;
}

