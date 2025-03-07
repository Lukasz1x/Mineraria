#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include "Writing.h"

using namespace std;

class GameSettings
{
private:
	int window_width;
	int window_height;
	string window_title;

public:
	GameSettings(int window_width, int window_height, string window_title);
	~GameSettings() = default;

	//funkcje do ustawie�
	int getWindowWidth();
	int getWindowHeight();
	string getWindowTitle();
	void setWorld(string world_name, string world_seed);

	//zmienne do generatora
	string world_name;
	string world_seed_unhashed;
	int world_seed = 0;

	//sekcje krytyczne w�tk�w
	bool draw = true;


	//zmienne do gry
	bool game_paused = false;
	bool dead = false;
	int regeneration_delay = 10; //w sekundach

	//taktyczne wska�niki na obiekty
	Writing* gui_respawn, *gui_main_menu;
};

