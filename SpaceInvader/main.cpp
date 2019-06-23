#include <cstdio>

#include "Game.h"

int main(int argc, char* argv[]) {
	Game game;
	if (!game.Init()) {
		printf("Failed to initialize game!\n");
		return 1;
	}

	game.Run();
	
	return 0;
}