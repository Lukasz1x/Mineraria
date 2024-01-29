#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>
#include <filesystem>
#include "GameSettings.h"
#include "Writing.h"
#include "World.h"


class Singleplayer
{
private:
	RenderWindow& window;
	GameSettings* game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
	Font font;
	vector<pair<string, string>> worlds_data;
	vector<tuple<RectangleShape, Text, Text>>worlds;
	int x0, y0;
public:


	Singleplayer(RenderWindow& window, GameSettings* game_settings);
	~Singleplayer() = default;

	int run(std::string& world_name);
};

