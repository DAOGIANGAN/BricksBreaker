#include "BallObject.h"

BallObject::BallObject()
{
	x_speed_ = 0;
	y_speed_ = 10;
	x_pos_ = 450;
	y_pos_ = 450;
	width_frame_ = 0;
	height_frame_ = 0;
	space_pressed = false;

	collide_with_brick= false;
    
	//space_.down_ = 2;
	brick.x = 0;
	brick.y = 0;
	brick.edge = 0;//trái 1, dưới 2,phải 3, trên 4

}

BallObject::~BallObject()
{
}

bool BallObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w;
		height_frame_ = rect_.h;
	}
	return ret;
}

void BallObject::Show(SDL_Renderer* des)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };
	SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
}

void BallObject::HandelinputAction(SDL_Event events, SDL_Renderer* screen)
  {
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_SPACE:
		{
			if (!space_pressed)
			{
				space_pressed = true;
			} 
			
		}
		break;
		default:
			break;
		}
	}
 }

bool BallObject::check_collide_with_bar(MainObject& p_player)
{
	SDL_Rect a = rect_;
	a.x += x_speed_;
	a.y += y_speed_;
	float x_bar = p_player.GetRect().x;
	float y_bar = p_player.GetRect().y;
	float w_bar = p_player.GetRect().w;
	float h_bar = p_player.GetRect().h;
	if (a.y + a.h > y_bar && a.x + (a.w / 2) > x_bar && a.x + (a.w / 2) < x_bar + w_bar && a.y + a.h < y_bar + h_bar)
	{
		return true;
	}
	return false;
}

bool BallObject::check_collide_with_map()
{
	SDL_Rect a = rect_;
	a.x += x_speed_;
	a.y += y_speed_;
	if (a.y<0||a.x+width_frame_>SCREEN_WIDTH||a.x<0)
	{
		return true;
	}
	return false;

}

save_location BallObject::check_collide_with_brick(GameMap& Map_)
{
	
    SDL_Rect a = rect_;
	a.x += x_speed_;
	a.y += y_speed_;
	
	int x1 = int(a.x / TILE_SIZE);
	int y1 = int(a.y / TILE_SIZE);
	int x2 = int((a.x + a.w) / TILE_SIZE);
	int y2 = int((a.y + a.h) / TILE_SIZE);
	if (Map_.game_map_.tile[y1][x1] != 0)
	{
		brick.y = y1;
		brick.x = x1;
		collide_with_brick = true;
		return brick;
	}
	if (Map_.game_map_.tile[y1][x2] != 0)
	{
		brick.y = y1;
		brick.x = x2;
		collide_with_brick = true;
		return brick;
	}
	if (Map_.game_map_.tile[y2][x1] != 0)
	{
		brick.y = y2;
		brick.x = x1;
		collide_with_brick = true;
		return brick;
	}
	if (Map_.game_map_.tile[y2][x2] != 0)
	{
		brick.y = y2;
		brick.x = x2;
		collide_with_brick = true;
		return brick;
	}
	return brick;
}

void BallObject::DoBall(MainObject& p_player, GameMap& Map_)
{
	if (!space_pressed) return;

	if (check_collide_with_bar(p_player))
	{
		float x_bar = p_player.GetRect().x;
		float y_bar = p_player.GetRect().y;
		float w_bar = p_player.GetRect().w;
		float h_bar = p_player.GetRect().h;

		y_pos_ = y_bar - height_frame_;
		x_pos_ += (y_bar - y_pos_ - height_frame_) * x_speed_ / y_speed_;

		float y_bar_center = x_bar + (w_bar / 2);
		float y_ball_center = x_pos_ + (width_frame_ / 2);

		float a = (ANPHA * M_PI / 180) * ((y_ball_center - y_bar_center) / (w_bar / 2));

		y_speed_ = -BALL_SPEED * cos(a);
		x_speed_ = BALL_SPEED * sin(a);
		Mix_PlayChannel(-1, collide, 0);
		y_pos_ += y_speed_;
		x_pos_ += x_speed_;

	}
	if (check_collide_with_map())
	{
		if (y_pos_ + y_speed_ < 0)
		{
			y_pos_ = 0;
			x_pos_ += (y_pos_ / abs(y_speed_)) * x_speed_;
			y_speed_ = -y_speed_;
			Mix_PlayChannel(-1, collide, 0);
		}
		if (x_pos_ + x_speed_ + width_frame_ > SCREEN_WIDTH)
		{
			y_pos_ += ((SCREEN_WIDTH - x_pos_ - width_frame_) / x_speed_) * y_speed_;
			x_pos_ = SCREEN_WIDTH - width_frame_;
			x_speed_ = -x_speed_;
			Mix_PlayChannel(-1, collide, 0);
		}
		if (x_pos_ + x_speed_ < 0)
		{
			y_pos_ += (x_pos_ / abs(x_speed_)) * y_speed_;
			x_pos_ = 0;
			x_speed_ = -x_speed_;
			Mix_PlayChannel(-1, collide, 0);

		}
		if (y_pos_ + y_speed_ > SCREEN_HEGHT)
		{
			y_pos_ = SCREEN_HEGHT+10;
			x_pos_ = 10;
			x_speed_ = 0;
			y_speed_ = 0;
		}
	}

	check_collide_with_brick(Map_);
	SDL_Rect a = rect_;
	a.x += x_speed_;
	a.y += y_speed_;


	if (collide_with_brick == true)
	{
		collide_with_brick = false;

		if (x_speed_ >= 0 && y_speed_ >= 0)
		{
			if (x_pos_ + width_frame_ >= brick.x * TILE_SIZE) brick.edge = 4;
			else
			{
				if (y_pos_ + height_frame_ >= brick.y * TILE_SIZE) brick.edge = 1;
				else
				{
					float c = float((brick.x * TILE_SIZE - x_pos_ - width_frame_) / abs(x_speed_));
					float d = float((brick.y * TILE_SIZE - y_pos_ - height_frame_) / abs(y_speed_));
					if (c > d) brick.edge = 1;
					else  brick.edge = 4;
				}
			}
		}
		if (x_speed_ >= 0 && y_speed_ <= 0)
		{
			if (x_pos_ + width_frame_ >= brick.x * TILE_SIZE) brick.edge = 2;
			else
			{
				if (y_pos_ <= (brick.y + 1) * TILE_SIZE) brick.edge = 1;
				else
				{
					float d = float((y_pos_ - (brick.y + 1) * TILE_SIZE) / abs(y_speed_));
					float c = float((brick.x * TILE_SIZE - x_pos_ - width_frame_) / abs(x_speed_));
					if (c > d) brick.edge = 1;
					else brick.edge = 2;
				}
			}
		}
		if (x_speed_ <= 0 && y_speed_ <= 0)
		{
			if (x_pos_ <= (brick.x + 1) * TILE_SIZE) brick.edge = 2;
			else
			{
				if (y_pos_ <= (brick.y + 1) * TILE_SIZE) brick.edge = 3;
				else
				{
					float c = float((x_pos_ - (brick.x + 1) * TILE_SIZE) / abs(x_speed_));
					float d = float((y_pos_ - (brick.y + 1) * TILE_SIZE) / abs(y_speed_));
					if (c > d) brick.edge = 3;
					else brick.edge = 2;
				}
			}


		}
		if (x_speed_ <= 0 && y_speed_ >= 0)
		{
			if (x_pos_ <= (brick.x + 1) * TILE_SIZE) brick.edge = 4;
			else
			{
				if (y_pos_ + height_frame_ >= brick.y * TILE_SIZE) brick.edge = 3;
				else
				{
					float c = float((x_pos_ - (brick.x + 1) * TILE_SIZE) / abs(x_speed_));
					float d = float((brick.y * TILE_SIZE - y_pos_ - height_frame_) / abs(y_speed_));
					if (c > d) brick.edge = 3;
					else brick.edge = 4;
				}
			}
		}

		if (brick.edge == 1)
		{
			x_pos_ = TILE_SIZE * brick.x - width_frame_;
			y_pos_ = a.y;
			x_speed_ = -x_speed_;
		}
		if (brick.edge == 2)
		{
			y_pos_ = (brick.y + 1) * TILE_SIZE;
			x_pos_ = a.x;
			y_speed_ = -y_speed_;
		}
		if (brick.edge == 3)
		{
			x_pos_ = (brick.x + 1) * TILE_SIZE;
			y_pos_ = a.y;
			x_speed_ = -x_speed_;
		}
		if (brick.edge == 4)
		{
			y_pos_ = brick.y * TILE_SIZE - height_frame_;
			x_pos_ = a.x;
			y_speed_ = -y_speed_;
		}

		if (Map_.game_map_.tile[brick.y][brick.x] != 6)
		{
			Map_.game_map_.tile[brick.y][brick.x] = 0;
			Mix_PlayChannel(-1, brick_break, 0);
		}
		else
		{
			Mix_PlayChannel(-1, collide, 0);
		}
	}
	y_pos_ += y_speed_;
	x_pos_ += x_speed_;
}

bool BallObject::checkLoss()
{
	if (y_pos_ > SCREEN_HEGHT)
		return true;
	else
		return false;
}

bool BallObject::checkWin(GameMap& Map_)
{
	bool a = true;
	for(int i=0;i<MAX_MAP_Y/TILE_SIZE;++i)
		for (int j = 0; j< MAX_MAP_X / TILE_SIZE; ++j)
		{
			if (Map_.game_map_.tile[i][j] != 0 && Map_.game_map_.tile[i][j] != 6)
			{
				a = false; break;
			}
		}
	return a;
}
