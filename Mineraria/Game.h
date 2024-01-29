#pragma once

#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "World.h"
#include "Player.h"
#include "Writing.h"
#include "Gui.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace sf;

class Game
{
private:
	RenderWindow& window;
	GameSettings* game_settings;
	RectangleShape background;
	Texture background_texture;
	Player *player;
	World* world;
	View* main_view_ptr;
	void load();
	void load_unload(World& world);
	void update(World& world);
	void controls(World& world);
	void gui_controls();
	short zoom = 2;
	bool go_to_main_menu = false;
public:
	Game(RenderWindow& window, GameSettings* game_settings);
	~Game() = default;

	int run();
};

