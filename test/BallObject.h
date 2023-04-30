
#ifndef BALL_OBJECT_H_
#define BALL_OBJECT_H_

#include "BaseObject.h"
#include "Common.h"
#include "MainObject.h"
#include "cmath"
#include "game_map.h"
#include "Header.h"
#define ANPHA 75
#define BALL_SPEED 7

class BallObject : public BaseObject
{
public:
	BallObject();
	~BallObject();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandelinputAction(SDL_Event events, SDL_Renderer* screen);
	
	bool check_collide_with_bar(MainObject& p_player);
	bool check_collide_with_map();
	save_location check_collide_with_brick(GameMap& Map_);
	void DoBall(MainObject& p_player,GameMap& Map_);
	bool checkLoss();
	bool checkWin(GameMap& Map_);
	
private:
	//Input space_;
	float x_speed_;
	float y_speed_;
	float x_pos_;
	float y_pos_;
	int y_limit = SCREEN_HEGHT;
	int width_frame_;
	int height_frame_;
	
	bool collide_with_brick;
	bool space_pressed;

	save_location brick;
	
	
};

#endif // !BALL_OBJECT_H_

