#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.h"
#include "MainMenu.h"
#include "Singleplayer.h"
#include "Multiplayer.h"
#include "Achivements.h"
#include "Settings.h"
#include "GameSettings.h"
#include "GameGeneratorMenu.h"


using namespace sf;

class GameManager
{
private:
	GameState current_state;
	shared_ptr<RenderWindow> window;
	shared_ptr<GameSettings> game_settings;
	void change_state(GameState state);
public:
	GameManager(shared_ptr<RenderWindow> window, shared_ptr<GameSettings>game_settings);
	~GameManager() = default;
	void run();
};

