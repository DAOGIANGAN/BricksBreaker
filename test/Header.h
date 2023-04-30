
#ifndef HEADER_H_
#define HEADER_H_
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "BallObject.h"

extern BaseObject g_background;
extern MainObject p_player;

extern GameMap map1;
extern GameMap map2;
extern GameMap map3;

extern ImpTimer fps_timer;
extern Mix_Chunk* collide;
extern Mix_Chunk* brick_break;
extern Mix_Chunk* WIN;
extern Mix_Chunk* GAMEOVER;
//extern BallObject ball;

#endif // HEADER_H_

