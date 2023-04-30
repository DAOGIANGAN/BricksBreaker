#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_
#include "Common.h"
#include "BaseObject.h"

#define BRICKS_SPEED 8

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandelinputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clip();
	void CheckToMap();
	void DoPlayer();
protected:
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	int width_frame_;
	int height_frame_;
	SDL_Rect frame_clip_[5];
	Input input_type_;

};
#endif // !MAIN_OBJECT_H_