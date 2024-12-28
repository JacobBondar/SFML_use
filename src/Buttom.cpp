#include "Buttom.h"

Buttom::Buttom(std::string text, sf::Vector2f position) : m_type(text)
{
	m_texturePicture.loadFromFile(text);

	m_picture = sf::Sprite(m_texturePicture);
	m_picture.setPosition(position);
}

sf::Sprite Buttom::getPicture()
{
	sf::Sprite picture(m_texturePicture); // Create a new sprite
	picture.setPosition(m_picture.getPosition()); // Preserve position
	return picture; // Return the new sprite
}

sf::Texture Buttom::getTexture()
{
	return m_texturePicture;
}

sf::Vector2f Buttom::getPosition()
{
	return m_picture.getPosition();
}