//This class handles the game state when the game is being played

#ifndef PLAY_H
#define PLAY_H

#include <stdlib.h> //for random number generator and itoa()
#include <ctime> //to seed random number 
#include <sstream>

#include "gameState.h"
#include "texture.h"
#include "graphics.h" //Needed for declareWinner(graphics)
#include "timer.h"

//Center position of ball
#define BALL_X 310
#define BALL_Y 230

#define SCREEN_CENTER_X 320
#define SCREEN_CENTER_Y 230

#define PADDLE_SPEED 5

//This is the font we will use for score keeping
#define FONT_PATH "assets/sample.ttf"
#define FONT_SIZE 50

class Play : public GameState {
private:
	//Images/Assets
	Texture AIScoreTexture;
	Texture PlayerScoreTexture;
	SDL_Rect PlayerPaddle;
	SDL_Rect AIPaddle;
	SDL_Rect ball;

	TTF_Font *timesNewRoman;
	SDL_Color textColor;

	Timer timer;
	//In memory text stream
	std::stringstream timeText;

	//Game status info
	int xVelocity; //velocities of ball
	int yVelocity;

	//Keeps track of how many times the ball has bounced off the paddles;
	//Resets once it counts to 4
	int bounceCount; 
	
	int playerScore;
	int AIScore;

	bool isGameOver();
    
	//Methods for setting up game
	void setUpPaddles();
	int getRandomNumber(int high, int low); 
	void resetBall();
	void loadPlayerScore(Graphics &graphics);
	void loadAIScore(Graphics &graphics);

	//Methods for collisions
	bool pointInRect(int x, int y, SDL_Rect rect);
	bool checkCollision(SDL_Rect rect1, SDL_Rect rect2);

	//Gameplay methods
	void handleAIMovement();
	//int bounceCount();
	void speedBallUp();

public:
	Play(Graphics &graphics);   //loads resources for gameplay
	~Play();  //frees resources

	//Main loop functions
	void handleEvents(SDL_Event &e);
	void logic();
	void render(Graphics &graphics);
};

#endif //PLAY_H