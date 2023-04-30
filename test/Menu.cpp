#include "Menu.h"
TextObject play, menu, quit, next, restart, BrickBreaker, resume ,win,gameover;
SDL_Color TextColor = { 0,0,0 };
SDL_Color TextColor1 = { 255,0,0 };
SDL_Color TextColor2 = { 255,242,0 };
TTF_Font* Font1=NULL;
TTF_Font* Font2=NULL;

bool CreatText(SDL_Renderer* g_screen)
{   
	Font1 = TTF_OpenFont("Font/A.ttf",70);
    Font2 = TTF_OpenFont("Font/A.ttf",50);

	play.loadFromRenderedText("Play", TextColor, Font2, g_screen);
	menu.loadFromRenderedText("Menu", TextColor, Font2, g_screen);
	next.loadFromRenderedText("Next Level", TextColor, Font2, g_screen);
	restart.loadFromRenderedText("Restart", TextColor, Font2, g_screen);
	quit.loadFromRenderedText("Quit", TextColor, Font2, g_screen);
	resume.loadFromRenderedText("Resume", TextColor, Font2, g_screen);
	BrickBreaker.loadFromRenderedText("BRICK BREAKER", TextColor, Font1, g_screen);
	win.loadFromRenderedText("WIN", TextColor2, Font1, g_screen);
	gameover.loadFromRenderedText("GAME OVER", TextColor, Font1, g_screen);
	return true;
}

StatusGameStart GameSTART(SDL_Renderer* g_screen)
{   
	CreatText(g_screen);
	BaseObject menu_background;
	menu_background.LoadImg("picture/menu.jpg",g_screen);
	bool is_quit = false;
	play.SetRect(200, 400);
	quit.SetRect(600, 400);
	BrickBreaker.SetRect(100, 100);
	while (!is_quit)
	{

		fps_timer.start();
		while (SDL_PollEvent(&g_event) != 0)
		{   
			switch (g_event.type)
			{
			case SDL_QUIT:
			{
				is_quit = true;
			}
			break;
			case SDL_MOUSEMOTION:
			{
				int x = g_event.motion.x;
				int y = g_event.motion.y;
				if(play.checkwithmouse(x, y))
				{
					play.loadFromRenderedText("Play", TextColor1, Font2, g_screen);
				}
				else
				{
					play.loadFromRenderedText("Play", TextColor, Font2, g_screen);
				}
				play.SetRect(200, 400);
				if (quit.checkwithmouse(x, y))
				{
					quit.loadFromRenderedText("Quit", TextColor1, Font2, g_screen);
				}
				else
				{
					quit.loadFromRenderedText("Quit", TextColor, Font2, g_screen);
				}
				quit.SetRect(600, 400);
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{

				int x = g_event.motion.x;
				int y = g_event.motion.y;
				if (play.checkwithmouse(x, y))
				{
					return S_PLAY;
				}
				if (quit.checkwithmouse(x, y))
				{
					return S_QUIT;
				}
			}


			default:
				break;
			}


		}

		SDL_SetRenderDrawColor(g_screen, 195, 195, 195, 195);
		SDL_RenderClear(g_screen);
		menu_background.Render(g_screen, NULL);
		BrickBreaker.render(g_screen);
		play.render(g_screen);
		quit.render(g_screen);
		SDL_RenderPresent(g_screen);
		
		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;//MS
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0) SDL_Delay(delay_time);
		}
	}
	if(is_quit==true)
	return S_QUIT;
}

StatusGameWin GameWIN(SDL_Renderer* g_screen)
{
	CreatText(g_screen);
	BaseObject win_background;
	win_background.LoadImg("picture/win.jpg", g_screen);
	bool is_quit = false;
	next.SetRect(150, 400);
	menu.SetRect(600, 400);
	win.SetRect(350, 150);
	while (!is_quit)
	{

		fps_timer.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			switch (g_event.type)
			{
			case SDL_QUIT:
			{
				is_quit = true;
			}
			case SDL_MOUSEMOTION:
			{
				int x = g_event.motion.x;
				int y = g_event.motion.y;
				if (next.checkwithmouse(x, y))
				{
					next.loadFromRenderedText("Next level", TextColor1, Font2, g_screen);
				}
				else
				{
					next.loadFromRenderedText("Next level", TextColor, Font2, g_screen);
				}
				next.SetRect(150, 400);
				if (menu.checkwithmouse(x, y))
				{
					menu.loadFromRenderedText("Menu", TextColor1, Font2, g_screen);
				}
				else
				{
					menu.loadFromRenderedText("Menu", TextColor, Font2, g_screen);
				}
				menu.SetRect(600, 400);
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{

				int x = g_event.motion.x;
				int y = g_event.motion.y;
				if (next.checkwithmouse(x, y))
				{
					return W_NEXT;
				}
				if (menu.checkwithmouse(x, y))
				{
					return W_MENU;
				}
			}


			default:
				break;
			}


		}

		SDL_SetRenderDrawColor(g_screen, 195, 195, 195, 195);
		SDL_RenderClear(g_screen);
		win_background.Render(g_screen, NULL);
		win.render(g_screen);
		next.render(g_screen);
		menu.render(g_screen);
		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;//MS
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0) SDL_Delay(delay_time);
		}
	}
	if (is_quit == true)
		return W_MENU;
}

StatusGameLoss GameLOSE(SDL_Renderer* g_screen)
{
	CreatText(g_screen);
	BaseObject loss_background;
	loss_background.LoadImg("picture/loss.jpg", g_screen);
	bool is_quit = false;
	restart.SetRect(150, 400);
	menu.SetRect(600, 400);
	gameover.SetRect(200, 100);
	while (!is_quit)
	{

		fps_timer.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			switch (g_event.type)
			{
			case SDL_QUIT:
			{
				is_quit = true;
			}
			case SDL_MOUSEMOTION:
			{
				int x = g_event.motion.x;
				int y = g_event.motion.y;
				if (restart.checkwithmouse(x, y))
				{
					restart.loadFromRenderedText("Restart", TextColor1, Font2, g_screen);
				}
				else
				{
					restart.loadFromRenderedText("Restart", TextColor, Font2, g_screen);
				}
				restart.SetRect( 150, 400);
				if (menu.checkwithmouse(x, y))
				{
					menu.loadFromRenderedText("Menu", TextColor1, Font2, g_screen);
				}
				else
				{
					menu.loadFromRenderedText("Menu", TextColor, Font2, g_screen);
				}
				menu.SetRect(600, 400);
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{

				int x = g_event.motion.x;
				int y = g_event.motion.y;
				if (restart.checkwithmouse(x, y))
				{
					return L_RESTART;
				}
				if (menu.checkwithmouse(x, y))
				{
					return L_MENU;
				}
			}


			default:
				break;
			}


		}

		SDL_SetRenderDrawColor(g_screen, 195, 195, 195, 195);
		SDL_RenderClear(g_screen);
		loss_background.Render(g_screen, NULL);
		gameover.render(g_screen);
		restart.render(g_screen);
		menu.render(g_screen);
		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;//MS
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0) SDL_Delay(delay_time);
		}
	}
	if (is_quit == true)
	return L_MENU;
}
