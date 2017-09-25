#include "graphics.h"
#include "texture.h"

Graphics::Graphics() {
	initSuccess = true;

	if (!init()) {
		printf("Failed to initialize!\n");
		initSuccess = false;
	}
}

Graphics::~Graphics() {
	_free();
}

bool Graphics::init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create VSYNCED renderer for window
			renderer = SDL_CreateRenderer(window, -1, 
				           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//|| SDL_RENDERER_PRESENTVSYNC

			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	//Turn on VSYNC
	//SDL_GL_SetSwapInterval(1);

	return success;
}

bool Graphics::initSucceeded() {
	if (initSuccess)
		return true;
	else
		return false;
}

void Graphics::_free() {
	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	//printf("free called\n");
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Graphics::getRenderer() const {
	return renderer;
}

// Called from texture.render() - renders a whole texture to a part of the screen
//  Note: may have to update later so we can choose to render a part of the texture
//        instead of rendering the whole texture
//     -> to do this, add SDL_Rect* source parameter
void Graphics::renderTexture(SDL_Texture* texture, SDL_Rect* destination) {
	SDL_RenderCopy(renderer, texture, NULL, destination);
}
