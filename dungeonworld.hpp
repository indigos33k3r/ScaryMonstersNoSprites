#ifndef DUNGEONWORLD_H
#define DUNGEONWORLD_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "vec3d.hpp"
#include "gameentity.hpp"
#include "characterentity.hpp"
#include "textmap.hpp"

class DungeonWorld {
public:
	DungeonWorld(int width, int height) : m_terrainMap(width, height, '.'), m_renderMap(width, height, '.') { 
		std::cout << "Dungeon of (" << width << "," << height << ") created.\n";
		m_characterList.push_back(new CharacterEntity(0, Vec3D<int>(width/2,height/2,0)));
		//spawn monsters? Load level? etc...

		//assign player entity
		for (std::vector<CharacterEntity *>::iterator iter = m_characterList.begin(); 
			iter != m_characterList.end(); iter++)
		{
			if ((*iter)->GetID() == 0)
			{
				(*iter)->Possess();
				m_pPlayerCharacter = *iter;
				std::cout << "Possessed the player character.\n";
			}
		}

		srand(time(NULL));
	}

	Vec3D<int> Dimensions() const { return m_terrainMap.Dimensions(); }
	void Render();
	void Generate(float density);
	void Update();

	CharacterEntity *PossessedCharacter() const { return m_pPlayerCharacter; }

private:

	static bool DiceRoll(float probability); //maybe this should go in a utils class?

	CharacterEntity *m_pPlayerCharacter;

	std::vector<CharacterEntity *> m_characterList;
	TextMap m_terrainMap;
	TextMap m_renderMap;
};

#endif
