
#ifndef SDL_FUNCTION_H_
#define SDL_FUNCTION_H_

#include <iostream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 640;
const string WINDOW_TITLE = "NARUTO NINJA WAR";
//SDL_Event mainevent;

const int Colorkey_R = 255;
const int Colorkey_G = 255;
const int Colorkey_B = 255;

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

SDL_Texture* loadBackGround(string path, SDL_Renderer* renderer);

#define TILE_SIZE 64
#define MAX_X 400
#define MAX_Y 10

typedef struct Input
{
    int stand;
    int run;
    int jump;
};

typedef struct Map
{
    int start_x_;
    int start_y_;
    int vitri_x_;
    int vitri_y_;
    int tile[MAX_Y][MAX_X];
    const char* mapname;
};

#endif