#include "Button.h"

//-----------------------------------------------------------------------------

Button::Button(const std::string text, sf::Vector2f position) 
	: m_type(text), m_position(position)
{
	m_texturePicture.loadFromFile(text);
}

//-----------------------------------------------------------------------------

sf::Vector2f Button::getPosition() const
{
	return m_position;
}

//-----------------------------------------------------------------------------

sf::FloatRect Button::getGlobalBounds() const
{
	sf::Sprite picture(m_texturePicture);
	picture.setPosition(m_position);

	return picture.getGlobalBounds();
}

//-----------------------------------------------------------------------------

std::string Button::getType() const
{
	std::string tempString;
	tempString = m_type; // preforms deep copy

	return tempString;
}

//-----------------------------------------------------------------------------

void Button::draw(sf::RenderWindow &window) const
{
	sf::Sprite picture(m_texturePicture);
	picture.setPosition(m_position);

	window.draw(picture);
}

//-----------------------------------------------------------------------------

sf::Sprite Button::getPicture() const
{
	sf::Sprite tempPic(m_texturePicture);
	tempPic.setPosition(m_position);
	return tempPic;
}