#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class GameSettings
{
private :
	int window_width;
	int window_height;
	string window_title;

public:
	GameSettings(int window_width, int window_height, string window_title);
	~GameSettings() = default;

	int getWindowWidth();
	int getWindowHeight();
	string getWindowTitle();
};

