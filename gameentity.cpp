#include "gameentity.hpp"

Vec3D<int> GameEntity::GetPos()
{
	return m_pos;
}

int GameEntity::MoveRelative(int xRel, int yRel) {
	m_pos.x += xRel;
	m_pos.y += yRel;
	return 1;
}

int GameEntity::Teleport(int x, int y) {
	m_pos.x = x;
	m_pos.y = y;
	return 1;
}