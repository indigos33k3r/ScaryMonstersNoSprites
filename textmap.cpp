#include "textmap.hpp"
#include <iostream>
#include <cctype>

TextMap::TextMap(int width, int height, char fill) {
	m_charMap.resize(width * height);
	m_width = width;
	m_height = height;

	//we don't actually HAVE to do this, but it makes sense.
	for (int i = 0; i < m_charMap.size(); i++)
		m_charMap[i] = fill;
}

void TextMap::Clear() {
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void TextMap::Display() {
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			if (isprint(m_charMap[(y * m_width) + x]))
				std::cout << m_charMap[(y * m_width) + x];
			else
				std::cout << ' ';
		}
		std::cout << "\n";
	}
}

std::vector<char> TextMap::GetCharMapVector() {
	return m_charMap;
}

void TextMap::Set(int x, int y, char value) {
	int vecIndex = (y * m_width) + x;
	if (vecIndex < 0 || vecIndex > m_charMap.size())
		return;

	m_charMap[(y * m_width) + x] = value;
}

char TextMap::Get(int x, int y) {
	int vecIndex = (y * m_width) + x;
	if (vecIndex < 0 || vecIndex > m_charMap.size())
		return 0;

	return m_charMap[vecIndex];
}