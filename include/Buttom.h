#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Buttom
{
public:
	Buttom(std::string text, sf::Vector2f position);
	sf::Sprite getPicture();
	sf::Texture getTexture();
	sf::Vector2f getPosition();

private:
	std::string m_type;
	sf::Sprite m_picture;
	sf::Texture m_texturePicture;
};