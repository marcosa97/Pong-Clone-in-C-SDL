/*
* Core of the game
*/

#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "gameState.h"
#include "intro.h"
#include "title.h"
#include "play.h"
#include "gameOver.h"
#include "timer.h"

class Game {
private:
	//bool success;
	Timer timer;
	Graphics graphics;

	//These handle game states 
	GameState* currentState;
	int currentStateID;
	int nextState;

public:
	Game();
	~Game();
	void freeGame();
	bool initSucceeded();

	//Game loop methods
	void gameLoop();
	void changeState();
	void draw();
};

#endif //GAME_H
