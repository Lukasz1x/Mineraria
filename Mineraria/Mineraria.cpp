//  v.0.1.3

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameManager.h"
#include "GameSettings.h"


int main() 
{
    shared_ptr<GameSettings> game_settings = std::make_shared<GameSettings>(1280, 720, "Mineraria");
    shared_ptr<sf::RenderWindow> window = make_shared<sf::RenderWindow>(sf::VideoMode(game_settings->getWindowWidth(), game_settings->getWindowHeight()), game_settings->getWindowTitle());

    GameManager game_manager(window, game_settings);

    game_manager.run();

    return 0;
}
