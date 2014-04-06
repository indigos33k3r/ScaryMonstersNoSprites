#ifndef TEXTMAP_H
#define TEXTMAP_H

#include <vector>
#include "vec3d.hpp"

class TextMap {
public:
	TextMap(int width, int height, char fill);
	void Clear();
	void Display();
	std::vector<char> GetCharMapVector();
	//int SetMap(std::vector<char> inputMap);
	void Set(int x, int y, char value);
	char Get(int x, int y); 
	int Width() { return m_width; }
	int Height() { return m_height; }
	Vec3D<int> Dimensions() const { Vec3D<int> dims(m_width, m_height, 0); return dims; }

	//need to write some operator overloading funcs to set maps to eachother

private:
	std::vector<char> m_charMap;
	int m_width;
	int m_height;
};

#endif