#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ConstNames.h"

class Tile
{
public:
	Tile();
	sf::RectangleShape getTile() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	std::string getType() const;
	sf::Vector2f getTilePosition() const;
	sf::Sprite getPicture() const;

	void setType(const std::string type);
	void setTilePosition(sf::Vector2f point);
	void setPicturePosition(sf::Vector2f point);
	void setOriginTile();
	void setPicture(const sf::Sprite picture);
	void setAfterSave();
	void setToDefault();

	bool doesContain(sf::Vector2f pointClicked) const;
	void resetPicture();
	void draw(sf::RenderWindow &window) const;

private:
	sf::RectangleShape m_tile;
	std::string m_type;
	sf::Sprite m_picture;

};