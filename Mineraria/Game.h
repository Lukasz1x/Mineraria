#pragma once

#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "World.h"
#include <vector>

using namespace sf;

class Game
{
private:
	RenderWindow& window;
	GameSettings& game_settings;
public:
	Game(RenderWindow& window, GameSettings& game_settings);
	~Game() = default;

	int run();
};

