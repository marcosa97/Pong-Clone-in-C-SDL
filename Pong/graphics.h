#ifndef GRAPHICS_H
#define GRAPHICS_H

//This class handles setting up the window and the rendering of textures
//Created using Lazy Foo's 2nd and 3rd SDL tutorials 
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//forward declaration
class Texture;

class Graphics {
private:
	bool initSuccess; //indicates whether initialization was successful or not
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Graphics();
	~Graphics();//Frees media and shuts down SDL
	bool init(); //initializes SDL
	bool initSucceeded();
	void _free(); //frees resources 
	
	SDL_Renderer* getRenderer() const;

	/* void renderTexture()
	* Draws a texture to a certain part of the screen
	*  @texture - what we are drawing from
	*  @sourceRectangle - the part from source that we want to draw
	*  @destinationRectangle - where we are drawing to
	*/
	void renderTexture(SDL_Texture* texture, SDL_Rect* destination); //calls SDL_RenderCopy

};

#endif //GRAHIPCS_H