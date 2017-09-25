#include "title.h"

Title::Title(Graphics &graphics) {
	if (!titleScreen.loadFromFile(graphics, "assets/images/Pong Title.png"))
		printf("Failed to load Title Screen!\n");
	nextStateID = STATE_NULL;
}

Title::~Title() {
	titleScreen._free();
}

void Title::handleEvents(SDL_Event &e) {
	//While there's events to handle
	while (SDL_PollEvent(&e))
	{
		//If the user has Xed out the window
		if (e.type == SDL_QUIT)
		{
			//Quit the program
			requestStateChange(STATE_EXIT);
		}

		//SWITCH CASE CAN BE ADDED HERE TO IMPLEMENT GAME MENU

		//If the user pressed enter
		else if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_RETURN))
		{
			//Move to the next state
			requestStateChange(STATE_PLAY); //STATE_EXIT is a placeholder here
		}
	}
}

void Title::logic() {
	//nothing happens. We only display an image in the intro
}

void Title::render(Graphics &graphics) {
	//render title screen
	titleScreen.render(graphics, 0, 0);
}