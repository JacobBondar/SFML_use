#include "Button.h"

Button::Button(std::string text, sf::Vector2f position) : m_type(text)
{
	m_texturePicture.loadFromFile(text);

	m_picture = sf::Sprite(m_texturePicture);
	m_picture.setPosition(position);
}

sf::Sprite Button::getPicture()
{
	sf::Sprite picture(m_texturePicture); // Create a new sprite
	picture.setPosition(m_picture.getPosition()); // Preserve position
	return picture; // Return the new sprite
}

sf::Vector2f Button::getPosition()
{
	return m_picture.getPosition();
}

sf::FloatRect Button::getGlobalBounds()
{
	return m_picture.getGlobalBounds();
}

char Button::getType()
{
	return m_type[0]; // return first letter only
}
