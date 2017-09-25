//This abstract class is used to derive the states of the game (intro, title screen, game over screen, etc)

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "SDL.h" 

class Graphics;

//NOTE: Add any additional game states here 
enum GameStates {
	STATE_NULL, //for when we don't want to change state
	STATE_INTRO,
	STATE_TITLE,
	STATE_PLAY,
	STATE_GAME_OVER,
	STATE_EXIT,
};

//Definition of an abstact class that I got online
//Abstract class:
//Abstract classes are used to represent general concepts (for example, Shape), which can be used as 
//  base classes for concrete classes (for example, Circle).
//  No objects of an abstract class can be created. Abstract types cannot be used as parameter types, 
//  as function return types, or as the type of an explicit conversion. Pointers and references to an 
//  abstract class can be declared.
//
//Game States include:
//   Intro
//   Title Screen
//   Play
//   Game Over

class GameState {
protected:
	//Make this protected because the derived classes need to access this variable

	int nextStateID; //contains STATE_NULL when we don't want to change states
public:
	//to be used in game.cpp to see whether we want to change state or not
	int getNextStateID() { return nextStateID; }
	//if state needs to change, this function is called and changes nextStateID to new state
	void requestStateChange(int newStateID) { nextStateID = newStateID; }

	//Main game loop functions 
	virtual void handleEvents(SDL_Event &e) = 0; //pure virtual
	virtual void logic() = 0;
	virtual void render(Graphics &graphics) = 0;
	virtual ~GameState() {};
};

#endif //GAME_STATE_H