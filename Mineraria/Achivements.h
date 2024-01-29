#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "GameManager.h"
#include "Writing.h"

class Achivements
{
private:
	RenderWindow& window;
	GameSettings* game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
public:


	Achivements(RenderWindow& window, GameSettings* game_settings);
	~Achivements() = default;

	int run();
};

