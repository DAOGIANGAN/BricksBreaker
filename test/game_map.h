#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "Common.h"
#include "BaseObject.h"
#define MAX_TILES 20
class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};
class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void Drawmap(SDL_Renderer* screen);
	Map game_map_;
private:
	
	TileMap tile_map[MAX_TILES];
};

#endif // !GAME_MAP_H_
