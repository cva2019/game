

#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "TextObject.h"
#include "BaseObject.h"

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Chunk* gsound1=NULL;
static Mix_Chunk* gsound2=NULL;
static Mix_Chunk* gsound3=NULL;


//Screen
const int FRAMES_PER_SECOND = 30;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int SPEED_SCREEN = 2;

const int RENDER_DRAW_COLOR = 0XFF;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

static char g_name_main_right[]               = {"img//player_right.png"};
static char g_name_main_left[]              = {"img//player_left.png"};

#define TILE_SIZE 64
#define BLANK_TILE 0

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 1
#define POWER 5
#define USE_AUDIO


typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
} Input;


typedef struct Map
{
    int start_x_;
    int start_y_;
    int max_x_; 
    int max_y_;  
    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
}Map;

namespace SDLCommonFunction
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font, 
                     const std::string& menu1, 
                   const std::string& menu2,
                    const std::string& img_name);
}

#endif