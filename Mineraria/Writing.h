#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Writing : public Drawable
{
private:
	Text text;
	void draw(RenderTarget& target, RenderStates state) const override;
public:
	Writing(std::string writing_text, sf::Font& text_font, int x, int y, int size = 20);
	~Writing() = default;

	void setOutline(Color color, int thickness);
	void setOutline(Color color);
	void setCharacterSize(int size);
	void setColor(Color color);
	void setString(std::string s);
	int getCharacterSize();
	int getOutlineThickness();
	FloatRect getGlobalBounds();
	std::string getString();
};

