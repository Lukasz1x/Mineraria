//  v.0.1.3

#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "GameSettings.h"


int main() 
{
    GameSettings game_settings(1280, 720, "Mineraria");
    sf::RenderWindow window(sf::VideoMode(game_settings.getWindowWidth(), game_settings.getWindowHeight()), game_settings.getWindowTitle());

    GameManager game_manager(window, &game_settings);

    game_manager.run();

    return 0;
}
