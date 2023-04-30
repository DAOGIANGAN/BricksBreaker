#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_
#include "Common.h"
#include "Header.h"
class TextObject
{
public:
	TextObject();
	~TextObject();
	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* gRenderer);
	void free();
    void SetRect(int x, int y);
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void render(SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	bool checkwithmouse(int x,int y);
	
private:
	SDL_Rect rect;
	SDL_Texture* mTexture;

};


#endif // !TEXT_OBJECT_H_
