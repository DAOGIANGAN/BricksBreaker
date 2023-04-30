#include "Header.h"
 BaseObject g_background;
 MainObject p_player;

 GameMap map1;
 GameMap map2;
 GameMap map3;

 ImpTimer fps_timer;
 Mix_Chunk* collide=NULL;
 Mix_Chunk* brick_break=NULL;
 Mix_Chunk* WIN=NULL;
 Mix_Chunk* GAMEOVER=NULL;

 //BallObject ball;