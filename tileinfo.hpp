#ifndef TILEINFO_H
#define TILEINFO_H

#include <vector>
#include <iostream>

class TileInfo
{
public:
	TileInfo()
	{
		m_walkable.push_back('.');

		m_transparent.push_back('.');
		m_transparent.push_back('~');
	}

	bool IsTrasparent(char tile)
	{
		for (unsigned int i = 0; i < m_transparent.size(); i++)
		{
			if (tile == m_transparent[i])
				return 1;
		}
		return 0;
	}

	bool IsWalkable(char tile)
	{
		for (unsigned int i = 0; i < m_walkable.size(); i++)
		{
			if (tile == m_walkable[i])
				return 1;
		}
		return 0;
	}
private:
	std::vector<char> m_walkable;
	std::vector<char> m_transparent;
};

#endif