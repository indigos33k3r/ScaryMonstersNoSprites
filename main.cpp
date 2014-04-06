#include "game.hpp"
#include <iostream>

int main() {
	Game scaryGame;
	scaryGame.Init();
	while (scaryGame.Turn());
	scaryGame.Quit();
	return 0;
}
