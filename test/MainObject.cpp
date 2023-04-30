#include "MainObject.h"

MainObject::MainObject()
{
	
	x_pos_= 400;
	y_pos_ = 500;
	x_val_= 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;

}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w ;
		height_frame_ = rect_.h;
	}
	return ret;
}

void MainObject::Show(SDL_Renderer* des)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	SDL_Rect* curren_clip = &frame_clip_[0];
	SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };
	SDL_RenderCopy(des, p_object_, curren_clip, &renderQuad);

}

void MainObject::HandelinputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{

		case SDLK_d:
		{
			input_type_.right_ = 1;
			input_type_.left_ = 0;
		}
		break;
		case SDLK_a:
		{
			input_type_.left_ = 1;
			input_type_.right_ = 0;
		}

		break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{


		case SDLK_d:
		{
			input_type_.right_ = 0;

		}
		break;
		case SDLK_a:
		{
			input_type_.left_ = 0;

		}

		break;
		default:
			break;
		}
	}

}

void MainObject::set_clip()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;
	}
}

void MainObject::DoPlayer()
{
	if (input_type_.left_ == 1)
	{
		x_pos_ -= BRICKS_SPEED;
	}
	if (input_type_.right_ == 1)
	{
		x_pos_ += BRICKS_SPEED;
	}
	CheckToMap();
}

void MainObject::CheckToMap()
{
	int x1 = 0;
	int x2 = 0;
	
	x1 = x_pos_ ;
	x2 = x_pos_ + width_frame_;
	if (x1 < 0)
	{
		x_pos_ = 0;
	}
	if (x2 > SCREEN_WIDTH)
	{
		x_pos_ = SCREEN_WIDTH - width_frame_;
	}
	
}