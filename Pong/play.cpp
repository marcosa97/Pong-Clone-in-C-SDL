#include "play.h"

//Checks if game is over or not
//Best of 7
bool Play::isGameOver() {
	if ((playerScore == 4) || (AIScore == 4))
		return true;
	else
		return false;
}

//Sets up paddles + ball
void Play::setUpPaddles() {
	//Set starting positions and dimensions for objects on the screen
	PlayerPaddle.h = 100;
	PlayerPaddle.w = 20;
    PlayerPaddle.x = 20;
	PlayerPaddle.y = SCREEN_HEIGHT/2 - (PlayerPaddle.h/2);

	AIPaddle.h = 100;
	AIPaddle.w = 20;
	AIPaddle.x = 600;
	AIPaddle.y = SCREEN_HEIGHT/2 - (AIPaddle.h/2);

	ball.x = BALL_X;
	ball.y = BALL_Y;
	ball.w = 20;
	ball.h = 20;

	//Set up velocities
	xVelocity = getRandomNumber(6, 4);
	yVelocity = getRandomNumber(6, -6);
}

int Play::getRandomNumber(int high, int low) {
	//Make sure numbers are not too large, so do mod 
	int num = rand() % high + low;

	if (num > high)
		return high;
	else
		return num;
}

void Play::resetBall() {
	ball.x = BALL_X;
	ball.y = BALL_Y;
}

//Loads an int that represents a score (playerScore) into a Texture object
void Play::loadPlayerScore(Graphics &graphics) {
	char buffer[5];

	_itoa_s(playerScore, buffer, 5, 10);

	if (!PlayerScoreTexture.loadTextFromString(graphics, buffer,
		timesNewRoman, textColor))
	{
		printf("Failed to render text texture!\n");
	}
}

//Loads an int that represents a score (AIScore) into a Texture object
void Play::loadAIScore(Graphics &graphics) {
	char buffer[5];

	_itoa_s(AIScore, buffer, 5, 10);

	if (!AIScoreTexture.loadTextFromString(graphics, buffer,
		timesNewRoman, textColor))
	{
		printf("Failed to render text texture!\n");
	}
}

//Checks if the point (x,y) is inside the SDL_Rect rect
bool Play::pointInRect(int x, int y, SDL_Rect rect) {
	//If the point is within the rectangle
	if (x > rect.x &&
		y > rect.y &&
		x < rect.x + rect.w &&
		y < rect.y + rect.h) {

		return true;
	}

	return false;
}

//Checks if rect1 is in rect2, i.e., they collided/touched
bool Play::checkCollision(SDL_Rect rect1, SDL_Rect rect2) {
	//Check if rect1 is in rect 2 by checking if 
	// any of the four corners of rect1 are inside rect2

	//  (x, y)  ------------ (x + w, y)
	//          |          |
	//          |          |
	//(x, y + h)------------ (x + w, y + h)

	if (pointInRect(rect1.x, rect1.y, rect2) ||
		pointInRect(rect1.x + rect1.w, rect1.y, rect2) ||
		pointInRect(rect1.x, rect1.y + rect1.h, rect2) ||
		pointInRect(rect1.x + rect1.w, rect1.y + rect1.h, rect2)) {

		return true;
	}

	return false;
}

void Play::handleAIMovement() {
	//Move AI paddle
	//If ball is on the AIPaddle's side
	if (ball.x > 240) {
	    if (AIPaddle.y + 0.5 * AIPaddle.h > ball.y + 0.5 * ball.h + 20) {
		    AIPaddle.y -= PADDLE_SPEED;
	    }
	    else if (AIPaddle.y + 0.5 * AIPaddle.h < ball.y + 0.5 * ball.h -20) {
		    AIPaddle.y += PADDLE_SPEED;
    	}
    }

	//Keep AI Paddle inside boundaries
	if (AIPaddle.y < 1)
		AIPaddle.y = 1;
	if (AIPaddle.y + AIPaddle.h > 479)
		AIPaddle.y = 479 - AIPaddle.h;
}

//Speeds up ball in x and y direction by 1 pixel per sec.
void Play::speedBallUp() {
	//Speed up xVelocity
	if (xVelocity < 0)
		xVelocity--;
	else
		xVelocity++;

	//Speed up yVelocity
	if (yVelocity < 0)
		yVelocity--;
	else
		yVelocity++;

	bounceCount = 0; //reset counter
}

//loads intro resources
Play::Play(Graphics& graphics) {

	setUpPaddles();
	playerScore = 0;
	AIScore = 0;
	bounceCount = 0;

	//Font to use
	timesNewRoman = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	if (timesNewRoman == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}

	textColor = { 255, 255, 255 }; //white
	loadPlayerScore(graphics);
	loadAIScore(graphics);

	//Timer is initialized when declared because of default constructor

	//set seed
	srand(time(NULL));

	//gameOver = false;
	nextStateID = STATE_NULL;
}

//frees resources
Play::~Play() {
	AIScoreTexture._free();
	PlayerScoreTexture._free();
	TTF_CloseFont(timesNewRoman);
	//delete timesNewRoman; --> DO NOT USE THIS!
	//    -> Causes seg fault
	//timesNewRoman is already deleted by TTF_CloseFont
}

//Handles mouse input while the user plays a game
void Play::handleEvents(SDL_Event &e) {

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

    //Get a pointer to the array of keystates 
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    //Move PlayerPaddle up or down
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		PlayerPaddle.y -= PADDLE_SPEED;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		PlayerPaddle.y += PADDLE_SPEED;
	}

	//Keep PlayerPaddle inside the window, i.e., set boundaries
	if (PlayerPaddle.y < 1)
		PlayerPaddle.y = 1;
	if (PlayerPaddle.y + PlayerPaddle.h > 479)
		PlayerPaddle.y = 479 - PlayerPaddle.h;
}

//Handles logic when the game is being played:
void Play::logic() {

	//Handle ball movement
	ball.x += xVelocity;
	ball.y += yVelocity;

	//Handle AIPaddle movement
	handleAIMovement();

	//Set ball boundaries/bouncing
	if (ball.y < 1)
		yVelocity = -yVelocity;
	if (ball.y + ball.h > SCREEN_HEIGHT - 1)
		yVelocity = -yVelocity;

	//Handle ball and paddles collisions
	if (checkCollision(ball, PlayerPaddle) || 
		checkCollision(ball, AIPaddle)) {

		//Speed up if the ball has bounced 4 times
		bounceCount++;
		if (bounceCount == 3) {
            speedBallUp();
		}

		xVelocity = -xVelocity;
	}

	//Check if anyone has scored
	if (ball.x < 1) {
		AIScore += 1;
		printf("AI Score: %d\n", AIScore);
		setUpPaddles(); //reset ball
		//SDL_Delay(1000);
	}
	if (ball.x + ball.w > SCREEN_WIDTH - 1) {
		playerScore += 1;
		printf("Player Score: %d\n", playerScore);
		setUpPaddles();
		//SDL_Delay(1000);
	}

	if (isGameOver()) {
		requestStateChange(STATE_GAME_OVER); //STATE_GAME_OVER 
	}

}

//Renders current state of the game after logic has been handled
void Play::render(Graphics &graphics) {

	//SDL_Delay(1);
	//Render background (black)
	SDL_SetRenderDrawColor(graphics.getRenderer(), 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(graphics.getRenderer(), NULL);

	//Render paddles and ball
	SDL_SetRenderDrawColor(graphics.getRenderer(), 0x00, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(graphics.getRenderer(), &PlayerPaddle);
	SDL_RenderFillRect(graphics.getRenderer(), &AIPaddle);
	SDL_RenderFillRect(graphics.getRenderer(), &ball);

	//Update scores
	//WARNING: Here, score textures are loaded every frame, so very inefficient
	loadAIScore(graphics);
	loadPlayerScore(graphics);

	//Display scores
	PlayerScoreTexture.render(graphics, SCREEN_CENTER_X - 100, 50);
	AIScoreTexture.render(graphics, SCREEN_CENTER_X + 100, 50);

}