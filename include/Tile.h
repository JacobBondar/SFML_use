#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Tile
{
public:
	Tile();
	sf::RectangleShape getTile();
	void setType(char c);
	char getType();
	void setTilePosition(sf::Vector2f point);
	void setPicturePosition(sf::Vector2f point);
	void setOriginTile();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	bool doesContain(sf::Vector2f pointClicked);
	sf::Sprite getPicture();
	void setPicture(sf::Sprite picture);
	void resetPicture();

	void draw(sf::RenderWindow &window) const;

private:
	sf::RectangleShape m_tile;
	char m_type;
	sf::Sprite m_picture;

};