#include "Writing.h"

Writing::Writing(std::string writing_text, sf::Font& text_font, int x, int y, int size)
{
	text.setString(writing_text);
	text.setFont(text_font);
	text.setPosition(Vector2f(x, y));
	text.setCharacterSize(size);
	text.setOrigin(floor(text.getLocalBounds().width / 2), floor(text.getLocalBounds().height / 2));
}

void Writing::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->text);
}

void Writing::setOutline(Color color, int thickness)
{
	text.setOutlineColor(color);
	text.setOutlineThickness(thickness);
}

void Writing::setOutline(Color color)
{
	text.setOutlineColor(color);
}

FloatRect Writing::getGlobalBounds()
{
	return text.getGlobalBounds();
}

void Writing::setCharacterSize(int size)
{
	text.setCharacterSize(size);
	text.setOrigin(floor(text.getLocalBounds().width / 2), floor(text.getLocalBounds().height / 2));
}

int Writing::getCharacterSize()
{
	return text.getCharacterSize();
}

int Writing::getOutlineThickness()
{
	return text.getOutlineThickness();
}
