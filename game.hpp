#ifndef GAME_H
#define GAME_H

#include "dungeonworld.hpp"
#include <vector>

class Game {
public:
	Game() : m_dungeon(60, 20) { }
	int Init();
	int Turn();
	int Quit();

private:
	DungeonWorld m_dungeon;
};

#endif
