#include "Game.h"

Game::Game(RenderWindow& window, GameSettings* game_settings) : window(window), game_settings(game_settings)	{}

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
	chrono::milliseconds interval(250);
	auto startTime = std::chrono::steady_clock::now();
	while(window.isOpen() && !go_to_main_menu)
	{ 
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
		if (elapsedTime >= interval)
		{	
			View current_view = window.getView();
			int x = current_view.getCenter().x / 512;
			
			world.load(x);
			game_settings->wait_draw = true;
			if (!game_settings->draw)
			{
				world.unload(x);
			}
			game_settings->wait_draw = false;
			startTime = std::chrono::steady_clock::now();
		}

	}
}

void check_colisions(World& world, int& top, int& down, int& left, int& right, FloatRect position)
{
	top = (int)((position.top - 50) / 16) * 16;
	left = (int)((position.left - 50) / 16) * 16;
	right = (int)((position.left + position.width + 50) / 16) * 16;
	down = (int)((position.top + position.height + 50) / 16) * 16;
	int loop1 = right;
	int loop2 = down;
	for (int x = left; x <= loop1; x += 16)
	{
		for (int y = top; y <= loop2; y += 16)
		{
			if (world.getBlockID(x, y) != 0)
			{
				FloatRect check_y = position;
				check_y.top -= 50;
				check_y.height += 100;
				check_y.left += 0.5;
				check_y.width -= 1;
				if (check_y.intersects(FloatRect(x-0.5, y-0.5, 17, 17)))
				{
					if ((y >= position.top + (position.height/3)) && (y < down))
					{
						down = y;
					}
					if ((y <= position.top+(position.height / 3)) && (y > top))
					{
						top = y;
					}
				}
				FloatRect check_x = position;
				check_x.left -= 50;
				check_x.width += 100;
				check_x.top += 0.5;
				check_x.height -= 1;
				if (check_x.intersects(FloatRect(x, y, 16, 16)))
				{
					if ((x >= position.left + (position.width/3)) && (x < right))
					{
						right = x;
					}
					if ((x <= position.left + (position.width / 3)) && (x > left))
					{
						left = x;
					}
				}
			}
		}
	}
	left += 16;
	top += 16;
}

void Game::update(World& world)
{
	chrono::milliseconds interval(25);//ma by� 25
	auto startTime = std::chrono::steady_clock::now();
	int top, down, left, right;
	while (window.isOpen() && !go_to_main_menu)
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
		//check_colisions(world, top, down, left, right, player->getHitBox());
		if (elapsedTime >= interval)
		{
			
			check_colisions(world, top, down, left, right, player->getHitBox());
			player->updatePosition(top, down, left, right);
			player->update();
			startTime = std::chrono::steady_clock::now();
		}
	}
}

void Game::gui_controls()
{
	Writing* guiButtons[] = { game_settings->gui_main_menu, game_settings->gui_respawn };
	if (!game_settings->draw)
	{
		game_settings->wait_draw = true;

		//cout << guiButtons[0]->getGlobalBounds().left << " " << guiButtons[0]->getGlobalBounds().top << " " << guiButtons[0]->getGlobalBounds().height << " " << guiButtons[0]->getGlobalBounds().width << endl;
		for (int i = 0; i < 2; i++)
		{
			FloatRect textBounds = guiButtons[i]->getGlobalBounds();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				textBounds.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
			{
				if (i)
					player->respawn();
				else
					go_to_main_menu = true;
			}

			if (textBounds.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
			{
				guiButtons[i]->setOutline(Color(155, 155, 100));
				guiButtons[i]->setCharacterSize(1.1 * 0.08 * game_settings->getWindowHeight());
			}
			else
			{
				guiButtons[i]->setOutline(Color(0, 0, 0));
				guiButtons[i]->setCharacterSize(0.08 * game_settings->getWindowHeight());
			}
		}
		game_settings->wait_draw = false;
	}
}

void Game::controls(World& world)
{
	Vector2i selected = Vector2i(0, 0);
	sf::Clock breakBlockClock;
	bool isMousePressed = false;
	bool relase_substract = true;
	bool relase_add = true;

	while (window.isOpen() && !go_to_main_menu)
	{
		if (game_settings->dead)
		{
			if(!game_settings->draw)
				world.unselectBlock(selected.x, selected.y);
			gui_controls();
			continue;
		}

		Vector2i mouse = Mouse::getPosition(window);
		Vector2f worldMouse = window.mapPixelToCoords(mouse);
		int left = ((int)((worldMouse.x - 18) / 16)) * 16;
		int top = ((int)((worldMouse.y - 18) / 16)) * 16;

		for (int x = left; x <= left + 40; x += 16)
		{
			for (int y = top; y <= top + 40; y += 16)
			{			
				FloatRect block(x, y, 16, 16);
				if (block.contains(worldMouse))// && !game_settings->draw)
				{
					world.selectBlock(x, y);
					if (selected!=Vector2i(x,y))
					{
						world.unselectBlock(selected.x, selected.y);
						
						selected = Vector2i(x, y);
					}
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!isMousePressed)
			{
				breakBlockClock.restart();
				isMousePressed = true;
			}

			if (breakBlockClock.getElapsedTime().asSeconds() >= 1.0f) // 1.0f to czas w sekundach
			{
				world.breakBlock(selected.x, selected.y);
				breakBlockClock.restart();
			}
		}
		else
		{
			isMousePressed = false;
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if(player->getVelocity().y==0)
				player->setVelocity(Vector2f(0, -100));
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player->setVelocity(Vector2f(80, player->getVelocity().y));
		}
		else if (Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player->setVelocity(Vector2f(-80, player->getVelocity().y));
		}
		else
		{
			player->setVelocity(Vector2f(0, player->getVelocity().y));
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Subtract) && relase_substract)
		{
			if (zoom > 1)
			{
				main_view_ptr->zoom(2.0f);
				zoom--;
			}
			relase_substract = false;
		}
		else if (!Keyboard::isKeyPressed(sf::Keyboard::Subtract) && relase_add)
		{
			relase_substract = true;
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Add) && relase_add)
		{
			if (zoom < 5)
			{
				main_view_ptr->zoom(0.5f);
				zoom++;
			}
			relase_add = false;
		}
		else if (!Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			relase_add = true;
		}

	}
}

int Game::run()
{
	View main_view(FloatRect(0, 0, game_settings->getWindowWidth()/2, game_settings->getWindowHeight()/2));
	View gui(FloatRect(0, 0, game_settings->getWindowWidth(), game_settings->getWindowHeight()));
	FloatRect view;
	main_view_ptr = &main_view;

	load();
	window.setView(main_view);
	

	World world(game_settings->world_name, game_settings->world_seed, game_settings->world_seed_unhashed);

	player = new Player(game_settings);
	player->setSpawnPoint(world.getSpawnPoint());
	player->setPosition(world.getSpawnPoint());

	thread load_thread(&Game::load_unload, this, ref(world));
	load_thread.detach();
	thread update_thread(&Game::update, this, ref(world));
	update_thread.detach();
	thread controls_thread(&Game::controls, this, ref(world));
	controls_thread.detach();


	

	while (window.isOpen())
	{
		if (go_to_main_menu)
		{
			game_settings->world_name = "";
			game_settings->world_seed = 0;
			return 1;
		}
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				for (auto& chunk : world.getChunks())
				{
					world.save(chunk);
				}
				window.close();

			}
		}
		game_settings->draw = true;

		if (!game_settings->wait_draw)
		{
			main_view.setCenter(player->getCenter());
			window.setView(main_view);
			view = FloatRect(main_view.getCenter().x - main_view.getSize().x / 2 - 20, main_view.getCenter().y - main_view.getSize().y / 2 - 20, main_view.getSize().x + 40, main_view.getSize().y + 40);

			window.clear();
			background.setPosition(main_view.getCenter().x, main_view.getCenter().y);
			window.draw(background);
			for (auto& chunk : world.getChunks())
			{
				if (((chunk.getChunkX() * 32 * 16) >= view.left - 512 - 20) && ((chunk.getChunkX() * 32 * 16) <= view.left + main_view.getSize().y + 512 + 64))
				{
					for (int i = 0; i < 32; i++)
					{
						for (int j = 0; j < 320; j++)
						{
							if (view.contains(Vector2f((chunk.getChunkX() * 32 + i) * 16, 16 * j)))
							{
								window.draw(chunk.block(i, j));
							}
						}
					}
				}
			}
			window.draw(*player);
			window.setView(gui);
			window.draw(player->draw_gui());

			game_settings->draw = false;
			window.display();
		}
	}
	return 1;
}