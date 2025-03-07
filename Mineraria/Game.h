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
#include "GameState.h"
#include <mutex>
#include <condition_variable>

using namespace sf;

class Game
{
private:
	std::mutex mtx;
	std::condition_variable cv;
	shared_ptr<RenderWindow> window;
	shared_ptr<GameSettings> game_settings;
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
	int chunk_center_x = 0;
	bool ready_to_load = false; // Sygnalizacja, czy w¹tek doczytuj¹cy mo¿e dzia³aæ
	bool ready_to_draw = true;  // Sygnalizacja, czy w¹tek rysuj¹cy mo¿e dzia³aæ

public:
	Game(shared_ptr<RenderWindow> window, shared_ptr<GameSettings>game_settings);
	~Game() = default;

	GameState run();
};

