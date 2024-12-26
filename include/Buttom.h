#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Buttom
{
public:
	Buttom(std::string text, sf::Vector2f position);
	sf::RectangleShape getButtom() const;
	void setPicture();
	sf::Sprite getPicture();

private:
	sf::RectangleShape m_buttom;
	std::string m_type;
	sf::Sprite picture;
};