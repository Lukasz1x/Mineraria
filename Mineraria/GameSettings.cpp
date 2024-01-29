#include "GameSettings.h"

GameSettings::GameSettings(int window_width, int window_height, string window_title)
{
	this->window_title = window_title;
	this->window_height = window_height;
	this->window_width = window_width;
}

int GameSettings::getWindowWidth()
{
	return window_width;
}

int GameSettings::getWindowHeight()
{
	return window_height;
}

string GameSettings::getWindowTitle()
{
	return window_title;
}

void GameSettings::setWorld(string world_name, string world_seed)
{
	this->world_name = world_name;
	world_seed_unhashed = world_seed;
	std::hash<std::string> hasher;
	if (world_seed == "")
	{
		for (int i = 0; i < 10; i++)
		{
			world_seed += std::to_string(rand() % 128);
		}
	}
	this->world_seed = hasher(world_seed);
}