#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "constNames.h"

class Tile
{
public:
	Tile();
	sf::RectangleShape getTile();
	void setType(std::string type);
	std::string getType();
	void setTilePosition(sf::Vector2f point);
	sf::Vector2f getTilePosition();
	void setPicturePosition(sf::Vector2f point);
	void setOriginTile();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	bool doesContain(sf::Vector2f pointClicked);
	sf::Sprite getPicture();
	void setPicture(sf::Sprite picture);
	void resetPicture();
	void setAfterSave();
	void setToDefault();
	void draw(sf::RenderWindow &window) const;

private:
	sf::RectangleShape m_tile;
	std::string m_type;
	sf::Sprite m_picture;

};