#include "game_map.h"

void GameMap::LoadMap(const char* name)
{
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL)
	{
		return;
	}
	game_map_.max_x_ = 0;
	game_map_.max_y_ = 0;
	for (int i = 0; i < MAX_MAP_Y/TILE_SIZE; ++i)
	{
		for (int j = 0; j < MAX_MAP_X/TILE_SIZE; ++j)
		{
			fscanf_s(fp, "%d", &game_map_.tile[i][j]);
			int val = game_map_.tile[i][j];
			if (val > 0)
			{
				if (j > game_map_.max_x_)
				{
					game_map_.max_x_ = j;
				}
				if (i > game_map_.max_y_)
				{
					game_map_.max_y_ = i;
				}
			}
		}
	}
	game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
	game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;
	game_map_.start_x_ = 0;
	game_map_.start_y_ = 0;
	//game_map_.file_name_ = name;
	fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
	char file_img[20];
	FILE* fp = NULL;
	for (int i = 0; i < MAX_TILES; ++i)
	{
		sprintf_s(file_img, "map//%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
		{
			continue;
		}
		fclose(fp);
		tile_map[i].LoadImg(file_img, screen);
	}
}

void GameMap::Drawmap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = SCREEN_WIDTH;

	int y1 = 0;
	int y2 = SCREEN_HEGHT;

	for (int i = y1; i < y2/TILE_SIZE; i++)
	{
		for (int j = x1; j < x2/TILE_SIZE; j++)
		{
			int val = game_map_.tile[i][j];
			if (val > 0)
			{
				tile_map[val].SetRect(j*TILE_SIZE , i*TILE_SIZE);
				tile_map[val].Render(screen);
			}
		}
	}
}
