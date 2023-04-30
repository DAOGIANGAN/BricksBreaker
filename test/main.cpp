#include "Common.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "game_map.h"
#include "ImpTimer.h"
#include"BallObject.h"
#include "Header.h"
#include "Menu.h"
//BaseObject g_background;
//MainObject p_player;
//GameMap map1;
//ImpTimer fps_timer;
BallObject ball;
bool Init()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (ret < 0) return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Bricks Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		success = false;
	}
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				success = false;
			}
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool ret = g_background.LoadImg("picture//background.jpg", g_screen);if (ret == false) return false;
	if(p_player.LoadImg("picture//thanhdo.png",g_screen)!= true) return false;
	if (ball.LoadImg("picture//quabong.png", g_screen) != true) return false;
	collide = Mix_LoadWAV("sound_effect//collide1.wav");
	if (collide == NULL) return false;
	brick_break = Mix_LoadWAV("sound_effect//brick_break3.wav");
	if (brick_break == NULL) return false;
	WIN = Mix_LoadWAV("sound_effect//win1.wav");
	if (WIN== NULL) return false;
	GAMEOVER = Mix_LoadWAV("sound_effect//gameover.wav");
	if (GAMEOVER == NULL) return false;
	return true;
}
void close()
{
	g_background.Free();
	p_player.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}
GameMap map_;
BallObject ball_;
MainObject p_player_;
bool gamerun(GameMap& Map_,BallObject& BALL,MainObject& P_PLAYER)
{
	map_ = Map_;
	ball_ = BALL;
	p_player_ = P_PLAYER;
	bool is_quit = false;
	bool win = false;
	while (!is_quit)
	{

		fps_timer.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}
			p_player_.HandelinputAction(g_event, g_screen);
			ball_.HandelinputAction(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, 195, 195, 195, 195);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);

		map_.Drawmap(g_screen);

		p_player_.DoPlayer();
		p_player_.Show(g_screen);

		ball_.DoBall(p_player_, map_);
		ball_.Show(g_screen);
		if (ball_.checkLoss())
		{
			is_quit = true;
			win = false;
			Mix_PlayChannel(-1,GAMEOVER, 0);
		}
		if (ball_.checkWin(map_))
		{
			is_quit = true;
			win = true;
			Mix_PlayChannel(-1, WIN, 0);

		}
		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;//MS
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0) SDL_Delay(delay_time);
		}
	}
	return win;
}

int main(int argc, char* argv[])
{
	if (Init() == false)
		return -1;
	if (loadMedia() == false)
		return -1;
	
	map1.LoadMap("TileMap/Map1.dat");
	map1.LoadTiles(g_screen);

	map2.LoadMap("TileMap/Map2.dat");
	map2.LoadTiles(g_screen);

	map3.LoadMap("TileMap/Map3.dat");
	map3.LoadTiles(g_screen);

	p_player.set_clip();
	
	bool is_quit = false;
	bool menu = true;
	bool restart = false;

	bool win_map1 = false;
	bool win_map2 = false;
	bool win_map3 = false;

	while (!is_quit)
	{   
		if (menu == true)
		{   
			win_map1 = false;
			win_map2 = false;
			win_map3 = false;
			restart = false;
			if (GameSTART(g_screen) == S_QUIT)
			{
				is_quit = true;
				break;
			}
		}

		if (is_quit == false)
		{
			if (win_map1 == false)
			{
				if (gamerun(map1, ball, p_player) == false)
				{
					if (GameLOSE(g_screen) == L_MENU)
					{
						menu = true;
					}
					else
					{
						menu = false;
					}
				}
				else
				{
					win_map1 = true;
					if (GameWIN(g_screen) == L_MENU)
					{
						menu = true;
					}
					else
					{
						menu = false;
					}
				}
			}
			
			if (win_map2 == false && win_map1==true)
			{
				if (gamerun(map2, ball, p_player) == false)
				{
					if (GameLOSE(g_screen) == L_MENU)
					{
						menu = true;
					}
					else
					{
						menu = false;
					}
				}
				else
				{
					win_map2 = true;
					if (GameWIN(g_screen) == W_MENU)
					{
						menu = true;
					}
					else
					{
						menu = false;
					}
				}
			}
			if (win_map3 == false && win_map2 == true)
			{
				if (gamerun(map3, ball, p_player) == false)
				{
					if (GameLOSE(g_screen) == L_MENU)
					{
						menu = true;
					}
					else
					{
						menu = false;
					}
				}
				else
				{
					win_map3 = true;
					if (GameWIN(g_screen) == W_MENU)
					{
						menu = true;
					}
					else
					{
						menu = true;
					}
				}
			}
		}
	}
	close();
	return 0;
}