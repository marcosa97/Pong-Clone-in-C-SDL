#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <sstream>

#include "gameState.h"
#include "texture.h"
#include "timer.h"

#define GAME_OVER_FONT_PATH "assets/sample.ttf"
#define GAME_OVER_FONT_SIZE 40

class GameOver : public GameState {
private:
	Texture gameOverMessage;
	//TTF_Font *timesNewRoman;
	//SDL_Color textColor;

	//std::stringstream timeText;
	//char *timeText;
public:
	GameOver(Graphics &graphics);
	~GameOver();

	//Main loop functions
	void handleEvents(SDL_Event &e);
	void logic();
	void render(Graphics &graphics);
};

#endif //GAME_OVER_H