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
	if (&text != nullptr) {
		target.draw(text);
	}
	else {
		// Handle the case where the object is null
		std::cerr << "Error: Writing object is null." << std::endl;
	}
	//target.draw(this->text);
}

void Writing::setColor(Color color)
{
	text.setFillColor(color);
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

void Writing::setString(std::string s)
{
	text.setString(s);
	text.setOrigin(floor(text.getLocalBounds().width / 2), floor(text.getLocalBounds().height / 2));
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

std::string Writing::getString()
{
	return text.getString();
}
