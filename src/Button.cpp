#include "Button.h"

Button::Button(std::string text, sf::Vector2f position) : m_type(text), m_position(position)
{
	m_texturePicture.loadFromFile(text);
}

sf::Vector2f Button::getPosition()
{
	return m_position;
}

sf::FloatRect Button::getGlobalBounds() // maybe look for another way
{
	sf::Sprite picture(m_texturePicture); // Create a new sprite
	picture.setPosition(m_position);

	return picture.getGlobalBounds();
}

char Button::getType()
{
	return m_type[0]; // return first letter only
}

void Button::draw(sf::RenderWindow &window)
{
	sf::Sprite picture(m_texturePicture); // Create a new sprite
	picture.setPosition(m_position);

	window.draw(picture);
}

sf::Sprite Button::getPicture()
{
	sf::Sprite tempPic(m_texturePicture);
	tempPic.setPosition(m_position);
	return tempPic;
}