#ifndef MENU_H_
#define MENU_H_
#include "Common.h"
#include "TextObject.h"
#include "Header.h"
enum StatusGameStart
{
	S_PLAY,
	S_QUIT,
	NONE,
};
enum StatusGameWin
{
	W_NEXT,
	W_MENU,
	W_NONE,
};
enum StatusGameLoss
{
	L_RESTART,
	L_MENU,
	L_NONE,
};
//int x=0 ;
//int y=0 ;
bool CreatText(SDL_Renderer* g_screen);
StatusGameStart GameSTART(SDL_Renderer* g_screen);
StatusGameWin GameWIN(SDL_Renderer* g_screen);
StatusGameLoss GameLOSE(SDL_Renderer* g_screen);
#endif // !MENU_H_

