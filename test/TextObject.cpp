#include "TextObject.h"

TextObject::TextObject()
{
	mTexture = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.h = 0;
	rect.w = 0;

}

TextObject::~TextObject()
{
}

bool TextObject::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			rect.w = loadedSurface->w;
			rect.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

bool TextObject::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* gRenderer)
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			rect.w = textSurface->w;
			rect.h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}

void TextObject::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		rect.x = 0;
		rect.y = 0;
		rect.w = 0;
		rect.h = 0;

	}
}

void TextObject::SetRect(int x, int y)
{   
	rect.x = x;
	rect.y = y;
}

void TextObject::render(SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (clip != NULL)
	{
		rect.w = clip->w;
		rect.h = clip->h;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &rect, angle, center, flip);
}

bool TextObject::checkwithmouse(int x, int y)
{  
	bool a = false;
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
	{
		a = true;
	}
	return a;
}

