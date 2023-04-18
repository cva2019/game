

#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <windows.h>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static  SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

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
#define  STATE_MONEY2 14

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
    int start_x_;// vị trí của x  x=?? ở ô thứ 10 thì là 10*640 x
    int start_y_;//y
    int max_x_;  /// ở ô thứ bao nhiêu start x / 64 lấy phần nguyên//id_x
    int max_y_;   //id_y
    int tile[MAX_MAP_Y][MAX_MAP_X];// x là cột còn y là dòng 
    char* file_name_;// lưu tên file
} Map;


typedef struct GeometricFormat
{
public:
    GeometricFormat(int left, int top, int width, int height) { left_ = left; top_ = top; width_ = width; height_ = height; }
    int left_;
    int top_;
    int width_;
    int height_;
};

typedef struct ColorData
{
public:
    ColorData(Uint8 r, Uint8 g, Uint8 b) { red_ = r, green_ = g, blue_ = b; }
    Uint8 red_;
    Uint8 green_;
    Uint8 blue_;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif