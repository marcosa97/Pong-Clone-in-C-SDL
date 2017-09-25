//This class wraps the SDL_Texture so it can handle loading textures
#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Graphics;

class Texture {
private:
	//actual harware texture
	SDL_Texture* texture;

	//image dimensions
	int width;
	int height;

public:
	Texture();
	~Texture();
	
	//This SDL_Texture can hold an image or text
	bool loadFromFile(Graphics &graphics, char* fileName); //Used to load images
	bool loadTextFromString(Graphics &graphics, const char* text, TTF_Font* font, SDL_Color textColor); //Used to load text

	void _free(); //deallocates texture
	void render(Graphics &graphics, int x, int y); //renders texture at a given (x,y) point

	int getWidth();
	int getHeight();
	SDL_Texture* getSDLTexture();

};

#endif //TEXTURE_H
