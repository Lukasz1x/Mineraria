#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "Writing.h"
#include "World.h"


class Singleplayer
{
private:
	RenderWindow& window;
	GameSettings& game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
public:


	Singleplayer(RenderWindow& window, GameSettings& game_settings);
	~Singleplayer() = default;

	int run(std::string& world_name);
};

