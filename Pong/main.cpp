/*
// ===== For memory leak checks in Visual Studio 2017 ================
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
*/

#include <stdio.h>
#include "game.h"
#include "gameState.h"

int main(int argc, char* argv[])
{
	//Visual Studio Memory Leak Check
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;

	if (!game.initSucceeded()) {
		printf("Game failed to initialize!\n");
		SDL_Delay(3000);
		return 0;
	}

	//Start game application
	game.gameLoop();

	//Free resources 
	game.freeGame();

	//Memory leak check report
	//_CrtDumpMemoryLeaks();
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	return 0;
}