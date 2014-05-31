#ifndef CHARACTERENTITY_H
#define CHARACTERENTITY_H

#include "vec3d.hpp"
#include "gameentity.hpp"
//#include "dungeonworld.hpp"

class DungeonWorld; //XXX forward declaration suffices for now, try not to introduce a circular dependency

class CharacterEntity : public GameEntity {
public:
	CharacterEntity(int type, Vec3D<int> pos):GameEntity(type, pos, GetCharacterRepresentation(type)) {
		m_isPlayer = false;
	}

	bool IsPosessed() const { return m_isPlayer; }
	void Possess() { m_isPlayer = true; } //give control to human player
	void RelinquishPossession() { m_isPlayer = false; } //lose control of human player

private:
	bool m_isPlayer;
	DungeonWorld *m_pDungeon; //player needs a ref to the world. NOT SET YET

	char GetCharacterRepresentation(int type)
	{
		switch (type) {
			case 0 :
				//plain old character
				return '@';
				break;
			case 1 :
				//monster!
				return 'M';
				break;
			default:
				return '?';
		}
	}
};

#endif 
