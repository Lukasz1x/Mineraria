#include "GameSettings.h"

GameSettings::GameSettings(int window_width, int window_height, string window_title)
{
	this->window_title = window_title;
	this->window_height = window_height;
	this->window_width = window_width;
}

int GameSettings::getWindowWidth()
{
	return window_width;
}

int GameSettings::getWindowHeight()
{
	return window_height;
}

string GameSettings::getWindowTitle()
{
	return window_title;
}