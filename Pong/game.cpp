#include "game.h"

Game::Game() {
	currentState = NULL;
	currentStateID = STATE_NULL;
	nextState = STATE_NULL;

	//"graphics" is initialized when declared, so no need to do anything here

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//Initialize FPS timer
	//timer.start();

}

Game::~Game() {
	//Quit SDL Subsystems
	TTF_Quit();
}

void Game::freeGame() {
	graphics._free();
	delete currentState;
}

//***NOTE: Does not check if SDL_ttf succceeded or not ***
bool Game::initSucceeded() {
	if (graphics.initSucceeded())
		return true;
	else
		return false;
}

//Main game loop
void Game::gameLoop() {
	currentStateID = STATE_INTRO;
	nextState = STATE_NULL;
	currentState = new Intro(graphics);

	//Event handler
	SDL_Event e;

	timer.start();

	float fps;

	//While application is running
	while (currentStateID != STATE_EXIT)
	{
		//Do state event handling
		currentState->handleEvents(e);

		fps = timer.calculateAvgFPS();

		//Do state logic
		currentState->logic();

		//Change state if needed
		nextState = currentState->getNextStateID();
		if (nextState != STATE_NULL)
			changeState();

		//Do state rendering
		currentState->render(graphics);

		//Update screen
		draw();

		//FPS Counter
		//timer.calculateAvgFPS();
		//timer.incrementCountedFrames();
		//printf("%f\n", fps);

	}

	graphics._free();
}

//This function changes the state of the game if the variable "nextState"
//  is set to something other than STATE_NULL
//-> Add as many states as you need for the game
void Game::changeState() {
	//If next state needs to be changed
	if (nextState != STATE_NULL) {
		//Delete current state
		if (nextState != STATE_EXIT) {
			delete currentState;
		}

		switch (nextState) {
		    case STATE_TITLE:
			    currentState = new Title(graphics);
			    break;
		    case STATE_PLAY:
			    currentState = new Play(graphics);
			    break;
		    case STATE_GAME_OVER:
			    currentState = new GameOver(graphics);
			    break;
		}
		//change current ID
		currentStateID = nextState;

		//NULL the next state ID
		nextState = STATE_NULL;
	}
}

//Updates the screen
void Game::draw() {
	//Clear screen
	//SDL_SetRenderDrawColor(graphics.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(graphics.getRenderer());

	//Render background texture to screen
	currentState->render(graphics);

	//Update screen ->This is what displays what was drawn/rendered
	SDL_RenderPresent(graphics.getRenderer());
}


