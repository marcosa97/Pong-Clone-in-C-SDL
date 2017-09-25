#include "texture.h"
#include "graphics.h"

Texture::Texture() {
	//Initialize
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture() {
	_free(); //FREEEEEEEEEEEEEEEE
}

//Loads an image into an SDL_Texture
bool Texture::loadFromFile(Graphics &graphics, char* fileName) {
	bool success = true;
	//Get rid of preexisting texture if there is one
	_free();

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(fileName);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", fileName, IMG_GetError());
		success = false;
	}
	else
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), loadedSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", fileName, SDL_GetError());
			success = false;
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	return success;
}

//Loads text into an SDL_Texture
// @&graphics: graphics object (because I need the renderer)
// @text: The text to render
// @font: the loaded TTF_Font to use for our text
// @textColor: SDL_Color to use for text
bool Texture::loadTextFromString(Graphics &graphics, const char* text, TTF_Font* font, SDL_Color textColor) {
	bool success = true;

	//Get rid of pre-existing texture
	_free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
	if (textSurface == NULL) {
		printf("Unable to render text surface!SDL_ttf Error : %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), textSurface);
		if (texture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	return success;
}

void Texture::_free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

// @int x, y - (x,y) area to render to on screen
void Texture::render(Graphics &graphics, int x, int y) {
	//Set rendering space and render to screen
	SDL_Rect areaToRender = { x, y, width, height };
	graphics.renderTexture(texture, &areaToRender);
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}

SDL_Texture* Texture::getSDLTexture() {
	return texture;
}
