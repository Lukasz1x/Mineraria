#include "GameManager.h"

GameManager::GameManager(shared_ptr<RenderWindow> window, shared_ptr<GameSettings>game_settings)
	: window(window), game_settings(game_settings), current_state(GameState::in_main_menu) {
}

void GameManager::change_state(GameState state)
{
	//cout<<"Changing state to "<<state<<endl;
	current_state = state;
}

void GameManager::run()
{
	string world_name;
	while (window->isOpen())
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
		case GameState::in_achievements:
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
		case GameState::in_generator_menu:
		{
			GameGeneratorMenu state(window, game_settings);
			change_state(state.run());
			break;
		}
		default:
			break;
		}
	}
}