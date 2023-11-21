#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MainMenu.h"
#include "Singleplayer.h"
#include "Multiplayer.h"
#include "Achivements.h"
#include "Settings.h"
#include "GameSettings.h"

using namespace sf;

class GameManager
{
private:
	enum GameState {
		in_main_menu,
		in_singleplayer,
		in_multiplayer,
		in_achivements,
		in_settings,
		in_game,
	};
	GameState current_state;
	RenderWindow& window;
	GameSettings& game_settings;
	void change_state(int state);
public:
	GameManager(RenderWindow& window, GameSettings& game_settings);
	~GameManager() = default;
	void run();
};

