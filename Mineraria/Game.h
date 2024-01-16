#pragma once

#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "World.h"
#include "Player.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace sf;

class Game
{
private:
	RenderWindow& window;
	GameSettings& game_settings;
	RectangleShape background;
	Texture background_texture;
	Player player;
	void load();
	void load_unload(World& world);
	void update(World& world);
	void controls(World& world);
	short zoom = 2;
public:
	Game(RenderWindow& window, GameSettings& game_settings);
	~Game() = default;

	int run();
};

