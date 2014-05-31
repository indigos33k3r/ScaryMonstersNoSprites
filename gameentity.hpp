#ifndef ENTITY_H
#define ENTITY_H

#include "vec3d.hpp"

class GameEntity {
public:
	GameEntity(int type, Vec3D<int> pos, char representation) : m_type(type), 
		m_id(NextValidID()), 
		m_pos(pos),
		m_representation(representation) {}

	GameEntity() : m_id(NextValidID()), 
		m_type(0), 
		m_pos(-1, -1, 0),
		m_representation(0) {}
	char Representation() { return m_representation; }
	int GetID() { return m_id; }
	Vec3D<int> GetPos();

	//TODO these functions should be virtual so inhereted classes can implement them their own way
	int MoveRelative(int xRel, int yRel);
	int Teleport(int x, int y);
private:
	int NextValidID() { static int nextID = 0; return nextID++; }

	char m_representation;
	int m_id;
	int m_type;
	Vec3D<int> m_pos;
};

#endif