#include "Game.h"

Game::Game(RenderWindow& window, GameSettings& game_settings) : window(window), game_settings(game_settings) {}


int Game::run()
{
	View main_view(FloatRect(0, 0, 640, 360));
	window.setView(main_view);
	World world("New World", 123);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Subtract))
			{
				main_view.zoom(2.0f);
				window.setView(main_view);
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Add))
			{
				main_view.zoom(0.5f);
				window.setView(main_view);
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Down))
			{
				main_view.move(0.0f, 100.0f);
				window.setView(main_view);
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Up))
			{
				main_view.move(0.0f, -100.0f);
				window.setView(main_view);
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Right))
			{
				main_view.move(100.0f, 0.0f);
				window.setView(main_view);
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Left))
			{
				main_view.move(-100.0f, 0.0f);
				window.setView(main_view);
			}


			window.clear();
			for (auto& chunk : world.getChunks())
			{
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 320; j++)
					{
						window.draw(chunk.block(i, j));
					}
				}
			}
			window.display();
		}
	}
	return 1;
}