#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Tile
{
public:
	Tile();
	sf::RectangleShape getTile();
	void setTilePosition(sf::Vector2f point);
	void setOriginTile();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	bool doesContain(sf::Vector2f pointClicked);

private:
	sf::RectangleShape m_tile;

};