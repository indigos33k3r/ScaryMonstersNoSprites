#ifndef CHARACTERENTITY_H
#define CHARACTERENTITY_H

#include "vec3d.hpp"
#include "gameentity.hpp"

class CharacterEntity : public GameEntity {
public:
	CharacterEntity(int type, Vec3D<int> pos):GameEntity(type, pos, GetCharacterRepresentation(type)) {
		m_isPlayer = false;
	}

	bool IsPosessed() const { return m_isPlayer; }
	void Possess() { m_isPlayer = true; } //give control to human player
	void Relinquish() { m_isPlayer = false; } //lose control of human player

private:
	bool m_isPlayer;

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
