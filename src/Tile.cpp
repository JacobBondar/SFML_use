#include "Tile.h"

Tile::Tile() : m_tile({ 100, 100 }), m_type('0')
{
	m_tile.setFillColor(sf::Color::Black);
	m_tile.setOutlineColor(sf::Color::White);
	m_tile.setOutlineThickness(1);
}

sf::RectangleShape Tile::getTile()
{
	return m_tile;
}

void Tile::setType(char c)
{
	m_type = c;
}

char Tile::getType()
{
	return m_type;
}

void Tile::setPicture(sf::Sprite picture)
{
	m_picture.setTexture(*(picture.getTexture()));
}

void Tile::resetPicture()
{
	m_picture.setTexture(sf::Texture());
}

void Tile::draw(sf::RenderWindow &window) const
{
	window.draw(m_tile);

	if (m_type != '0')
	{
		window.draw(m_picture);
	}
}

void Tile::setTilePosition(sf::Vector2f point)
{
	m_tile.setPosition(point);
}

void Tile::setPicturePosition(sf::Vector2f point)
{
	m_picture.setPosition(point);
}

void Tile::setOriginTile()
{
	m_tile.setOrigin(m_tile.getSize() / 2.f);
}

sf::Vector2f Tile::getPosition()
{
	return m_tile.getPosition();
	
}

sf::Vector2f Tile::getSize()
{
	return m_tile.getSize();
}

bool Tile::doesContain(sf::Vector2f pointClicked)
{
	return (m_tile.getGlobalBounds().contains(pointClicked));
}

sf::Sprite Tile::getPicture()
{
	sf::Sprite tempPic;
	tempPic.setTexture(*(m_picture.getTexture()));

	return tempPic;
}
