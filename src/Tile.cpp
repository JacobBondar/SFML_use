#include "Tile.h"

Tile::Tile() : m_tile({ 100, 100 })
{
	m_tile.setFillColor(sf::Color::Black);
	m_tile.setOutlineColor(sf::Color::White);
	m_tile.setOutlineThickness(1);
}

sf::RectangleShape Tile::getTile()
{
	return m_tile;
}

void Tile::setTilePosition(sf::Vector2f point)
{
	m_tile.setPosition(point);
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