#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow& window, GameSettings& game_settings)
	: window(window), game_settings(game_settings), current_state(GameState::in_main_menu) {
}

void GameManager::change_state(int state)
{
	switch (state)
	{
	case 1:	current_state = in_main_menu;		break;
	case 2:	current_state = in_singleplayer;	break;
	case 3:	current_state = in_multiplayer;		break;
	case 4:	current_state = in_achivements;		break;
	case 5:	current_state = in_settings;		break;
	case 6: current_state = in_game;			break;

	default:
		break;
	}
}

void GameManager::run()
{
	string world_name;
	while (window.isOpen())
	{
		switch (current_state)
		{
		case GameState::in_main_menu:
		{
			MainMenu state(window, game_settings);
			change_state(state.run());

			break;
		}
		case GameState::in_singleplayer:
		{
			Singleplayer state(window, game_settings);
			change_state(state.run(world_name));
			break;
		}
		case GameState::in_multiplayer:
		{
			Multiplayer state(window, game_settings);
			change_state(state.run(world_name));
			break;
		}
		case GameState::in_achivements:
		{
			Achivements state(window, game_settings);
			change_state(state.run());
			break;
		}
		case GameState::in_settings:
		{
			Settings state(window, game_settings);
			change_state(state.run());
			break;
		}
		case GameState::in_game:
		{
			Game state(window, game_settings);
			change_state(state.run());
			break;
		}
		default:
			break;
		}
	}
}