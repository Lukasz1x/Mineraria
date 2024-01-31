#include "BlockTexture.h"

BlockTexture::BlockTexture(int ID, string file)
{
	this->ID = ID;
	texture.loadFromFile("assets/textures/block/"+file);

}

Texture& BlockTexture::getTexture()
{
	return texture;
}

int BlockTexture::getID()
{
	return ID;
}