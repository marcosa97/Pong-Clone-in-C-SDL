//This class handles the title screen for the game
#ifndef TITLE_H
#define TITLE_H

#include "gameState.h"
#include "texture.h"

class Title : public GameState {
private:
	Texture titleScreen;
public:
	Title(Graphics &graphics);
	~Title();

	//Main loop functions
	void handleEvents(SDL_Event &e);
	void logic();
	void render(Graphics &graphics);
};

#endif //TITLE_H