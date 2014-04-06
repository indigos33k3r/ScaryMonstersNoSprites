#include "dungeonworld.hpp"
#include <iostream>

/*DungeonWorld::DungeonWorld() {

}*/

bool DungeonWorld::DiceRoll(float probability) {
	int myRand = rand() % 100 + 1;
	if (myRand <= static_cast<int>(probability * 100)) {
		return true;
	} 

	return false;
}

void DungeonWorld::Generate(float density) {
	//generate some noise
	for (int y = 0; y < m_terrainMap.Height(); y++) {
		for (int x = 0; x < m_terrainMap.Width(); x++) {
			if (DiceRoll(density)) {
				m_terrainMap.Set(x, y, '#');
			}
		}
	}

	//now join the noise in to more coherent walls and rooms
	for (int y = 0; y < m_terrainMap.Height(); y++) {
		for (int x = 0; x < m_terrainMap.Width(); x++) {

			//generate horizontal walls
			if (m_terrainMap.Get(x - 1, y) == '#' || m_terrainMap.Get(x + 1, y) == '#' ) {
				if (DiceRoll(density * 2)) {
					m_terrainMap.Set(x, y, '#');
				}
			}

			//generate vertical walls
			if (m_terrainMap.Get(x, y - 1) == '#' || m_terrainMap.Get(x, y + 1) == '#' ) {
				if (DiceRoll(density * 2)) {
					m_terrainMap.Set(x, y, '#');
				}
			}
		}
	}

	//done!
}

void DungeonWorld::Render() {
	m_renderMap = m_terrainMap;
	for (int i = 0; i < m_characterList.size(); i++)
	{
		if (isprint(m_characterList[i]->Representation())) {
			m_renderMap.Set(m_characterList[i]->GetPos().x, 
			m_characterList[i]->GetPos().y, 
			m_characterList[i]->Representation());
		}
	}
	m_renderMap.Display();
}

void DungeonWorld::Update()
{
	
}