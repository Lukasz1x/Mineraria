#include "Game.h"

Game::Game(RenderWindow& window, GameSettings& game_settings) : window(window), game_settings(game_settings) {}

void Game::load()
{
	background_texture.loadFromFile("assets/background_sky.png");
	background.setSize(Vector2f(800, 480));
	background.setTexture(&background_texture);
	background.setOrigin(400, 240);
	background.setScale(5, 5);
}

void Game::load_unload(World& world)
{
	chrono::milliseconds interval(100);
	auto startTime = std::chrono::steady_clock::now();
	while(window.isOpen())
	{ 
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
		if (elapsedTime >= interval)
		{	
			View current_view = window.getView();
			int x = current_view.getCenter().x / 512;
			world.load(x);
			world.unload(x);
			cout << "Load" << endl;
			startTime = std::chrono::steady_clock::now();
		}

	}
}

void Game::update(World& world)
{
	chrono::milliseconds interval(25);
	auto startTime = std::chrono::steady_clock::now();
	while (window.isOpen())
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
		if (elapsedTime >= interval)
		{
			player.applyGravity();
			player.updatePosition();
			startTime = std::chrono::steady_clock::now();
		}
	}
}

int Game::run()
{
	View main_view(FloatRect(0, 0, game_settings.getWindowWidth()/2, game_settings.getWindowHeight()/2));
	load();
	window.setView(main_view);
	World world("New World", 123);
	//thread t(&Game::load_unload, this, ref(world));
	//t.detach();
	thread update_thread(&Game::update, this, ref(world));
	update_thread.detach();
	short zoom = 1;

	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				window.close();
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Subtract))
			{
				if (zoom > 0)
				{
					main_view.zoom(2.0f);
					zoom--;
				}		
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Add))
			{
				if (zoom < 4)
				{
					main_view.zoom(0.5f);
					zoom++;
				}
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Down))
			{
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Up))
			{
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Right))
			{
				player.move_right();
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Left))
			{
				player.move_left();
				
			}
		}
		main_view.setCenter(player.getCenter());
		window.setView(main_view);
		FloatRect view;
		view = FloatRect(main_view.getCenter().x - main_view.getSize().x / 2 - 20, main_view.getCenter().y - main_view.getSize().y / 2 - 20, main_view.getSize().x + 40, main_view.getSize().y + 40);
		//cout << view.left << " " << view.top << " " << view.width << " " << view.height << " " << current_view.getCenter().x << " " << current_view.getCenter().y << endl;
		background.setPosition(main_view.getCenter().x, main_view.getCenter().y);
		int x = main_view.getCenter().x / 512;
		world.load(x);
		world.unload(x);
		window.clear();
		window.draw(background);
		for (auto& chunk : world.getChunks())
		{
			//cout << chunk.blocks[0][0].block.getPosition().x << endl;
			if (((chunk.getChunkX() * 32 * 16) >= view.left - 512 - 20) && ((chunk.getChunkX() * 32 * 16) <= view.left + main_view.getSize().y + 512 + 64))
			{
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 320; j++)
					{
						if (view.contains(Vector2f((chunk.getChunkX() * 32 + i) * 16, 16 * j)))
						{
							//cout << i << " " << j << endl;
							window.draw(chunk.block(i, j));
						}
					}
				}
			}
		}
		window.draw(player);
		window.display();



	}
	return 1;
}