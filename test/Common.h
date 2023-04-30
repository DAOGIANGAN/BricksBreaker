#ifndef COMMON_H_
#define COMMON_H_
#include <SDL.h>
#include <stdio.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <SDL_image.h>
#include <string>
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
// screen
const int FRAME_PER_SECOND = 65;//FPS

const int SCREEN_WIDTH = 900;
const int SCREEN_HEGHT = 540;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 195;
const int COLOR_KEY_G = 195;
const int COLOR_KEY_B = 195;
const int RENDER_DRAW_COLOR = 0xff;

#define TILE_SIZE 30
#define MAX_MAP_X 900
#define MAX_MAP_Y 540 
typedef struct Map
{
	int start_x_;
	int start_y_;
	int max_x_;
	int max_y_;
	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};
typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	
};
typedef struct save_location
{
	int x;
	int y;
	int edge;
};


#endif // !COMMON_H_
