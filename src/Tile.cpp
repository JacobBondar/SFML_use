#include "Tile.h"

//-----------------------------------------------------------------------------

Tile::Tile() : m_tile({ SIZEOFPICTURE, SIZEOFPICTURE }), m_type(SPACENAME)
{
	m_tile.setFillColor(sf::Color::Black);
	m_tile.setOutlineColor(sf::Color::White);
	m_tile.setOutlineThickness(1);
}

//-----------------------------------------------------------------------------

sf::RectangleShape Tile::getTile() const
{
	return m_tile;
}

//-----------------------------------------------------------------------------

void Tile::setType(const std::string type)
{
	m_type = type;
}

//-----------------------------------------------------------------------------

std::string Tile::getType() const
{
	return m_type;
}

//-----------------------------------------------------------------------------

void Tile::setPicture(const sf::Sprite picture)
{
	m_picture.setTexture(*(picture.getTexture()));
	m_picture.setScale(0.5f, 0.5f);
}

//-----------------------------------------------------------------------------

void Tile::resetPicture()
{
	m_picture.setTexture(sf::Texture());
}

//-----------------------------------------------------------------------------

void Tile::setAfterSave()
{
	m_tile.setOutlineColor(sf::Color::Green);
	m_tile.setOutlineThickness(2);
}

//-----------------------------------------------------------------------------

void Tile::setToDefault()
{
	m_tile.setOutlineColor(sf::Color::White);
	m_tile.setOutlineThickness(1);
}

//-----------------------------------------------------------------------------

void Tile::draw(sf::RenderWindow &window) const
{
	window.draw(m_tile);

	if (m_type != SPACENAME)
	{
		window.draw(m_picture);
	}
}

//-----------------------------------------------------------------------------

void Tile::setTilePosition(sf::Vector2f point)
{
	m_tile.setPosition(point);
}

//-----------------------------------------------------------------------------

sf::Vector2f Tile::getTilePosition() const
{
	return m_tile.getPosition();
}

//-----------------------------------------------------------------------------

void Tile::setPicturePosition(sf::Vector2f point)
{
	m_picture.setPosition(point);
}

//-----------------------------------------------------------------------------

void Tile::setOriginTile()
{
	m_tile.setOrigin(m_tile.getSize() / 2.f);
}

//-----------------------------------------------------------------------------

sf::Vector2f Tile::getPosition() const
{
	return m_tile.getPosition();
	
}

//-----------------------------------------------------------------------------

sf::Vector2f Tile::getSize() const
{
	return m_tile.getSize();
}

//-----------------------------------------------------------------------------

bool Tile::doesContain(sf::Vector2f pointClicked) const
{
	return (m_tile.getGlobalBounds().contains(pointClicked));
}

//-----------------------------------------------------------------------------

sf::Sprite Tile::getPicture() const
{
	sf::Sprite tempPic;
	tempPic.setTexture(*(m_picture.getTexture()));

	return tempPic;
}