#include "gameOver.h"

GameOver::GameOver(Graphics &graphics) {
	if (!gameOverMessage.loadFromFile(graphics, "assets/images/Pong Game over.png"))
		printf("Failed to load Title Screen!\n");
	nextStateID = STATE_NULL;

	/*
	//Font to use
	timesNewRoman = TTF_OpenFont(GAME_OVER_FONT_PATH, GAME_OVER_FONT_SIZE);
	if (timesNewRoman == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}

	textColor = { 0, 0, 0 };

	//gameOverMessage.loadTextFromString(graphics, "GAME OVER: PLAY AGAIN?", timesNewRoman, textColor);
	//timeText.str("");

	*/

}

GameOver::~GameOver() {
	gameOverMessage._free();
}

//Main loop functions
void GameOver::handleEvents(SDL_Event &e) {
	//Handle events on queue
	while (SDL_PollEvent(&e))
	{
		//If the user has Xed out the window
		if (e.type == SDL_QUIT)
		{
			//Quit the program
			requestStateChange(STATE_EXIT);
		}
	} //while

	//HANDLING EVENTS USING KEY STATES
	//Get a pointer to the array of keystates 
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	//Return to title screen if user presses BACKSPACE
	//Play again if ENTER is pressed
	if (currentKeyStates[SDL_SCANCODE_RETURN]) {
		requestStateChange(STATE_PLAY);
	}
	else if (currentKeyStates[SDL_SCANCODE_BACKSPACE]) {
		requestStateChange(STATE_TITLE);
	}
}

void GameOver::logic() {
}

void GameOver::render(Graphics &graphics) {
	/*
	//Set text to be rendered
	timeText.str("");
	timeText << "Average Frames Per Second " << avgFPS;

	//timeText = buffer.str().c_str();

	//Render text
	if (!timeTest.loadTextFromString(graphics, timeText.str().c_str(), timesNewRoman, textColor))
	{
		printf("Unable to render time texture!\n");
	}
	
	countedFrames++;
	*/

	gameOverMessage.render(graphics, 0, 0);
}