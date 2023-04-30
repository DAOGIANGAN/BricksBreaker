#ifndef BaseObject_H_
#define BaseObject_H_
#include "Common.h"
class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void Free();
	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() const { return p_object_; }
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	
protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
	
};

#endif // !BaseObject_H_
