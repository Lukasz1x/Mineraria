#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class BlockTexture
{
	Texture texture;
	int ID;
public:
	BlockTexture(int ID, string file);
	~BlockTexture() = default;
	Texture& getTexture();
	int getID();

};

