#ifndef INTRO_H
#define INTRO_H

#include "texture.h"
#include "gameState.h"

//This class handles the first image displayed in the game, the introduction screen

class Intro : public GameState {
private:
	Texture introImage;
public:
	Intro(Graphics& graphics);   //loads intro resources
	~Intro();  //frees intro resources

			   //Main loop functions
	void handleEvents(SDL_Event &e);
	void logic();
	void render(Graphics &graphics);
};

#endif //INTRO_H
