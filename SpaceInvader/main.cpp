//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//
//#ifdef _DEBUG
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//// allocations to be of _CLIENT_BLOCK type
//#else
//#define DBG_NEW new
//#endif

#include <cstdio>

#include "Game.h"

int main(int argc, char* argv[]) {
	Game game;
	if (!game.Init()) {
		printf("Failed to initialize game!\n");
		return 1;
	}

	game.Run();

	//_CrtDumpMemoryLeaks();
	
	return 0;
}