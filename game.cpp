#include "game.hpp"
#include <iostream>
#include <string>
#include <streambuf>
#include <algorithm>

/*Game::Game()
{

}*/

int Game::Init() {
	std::cout << "Initializing Scary Game...\n";
	m_dungeon.Generate(0.12f);
}

int Game::Turn() {
	//this is the main game loop.
	m_dungeon.Render();
	std::cout << "Enter command: ";
	std::string cmdIn;
	std::getline(std::cin, cmdIn);
	
	//this can all be bundled in a "HandleCommands" function or the like
	std::transform(cmdIn.begin(), cmdIn.end(), cmdIn.begin(), ::tolower);

	if (cmdIn.compare("quit") == 0) //compare returns 0 if they ARE equal
		return 0;

	if (cmdIn.compare("move left") == 0 ||
			cmdIn.compare("a") == 0)
	{
		std::cout << "Moving player character left!\n";
		m_dungeon.PossessedCharacter()->MoveRelative(-1, 0);
	}

	if (cmdIn.compare("move right") == 0 ||
			cmdIn.compare("d") == 0)
	{
		std::cout << "Moving player character right!\n";
		m_dungeon.PossessedCharacter()->MoveRelative(1, 0);
	}

	if (cmdIn.compare("move up") == 0 ||
			cmdIn.compare("w") == 0)
	{
		std::cout << "Moving player character up!\n";
		m_dungeon.PossessedCharacter()->MoveRelative(0, -1);
	}

	if (cmdIn.compare("move down") == 0 ||
			cmdIn.compare("s") == 0)
	{
		std::cout << "Moving player character down!\n";
		m_dungeon.PossessedCharacter()->MoveRelative(0, 1);
	}

	m_dungeon.Update();

	return 1; //otherwise, return 1 and keep looping!
}

int Game::Quit() {
	
}

