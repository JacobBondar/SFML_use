#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button(std::string text, sf::Vector2f position);
	sf::Sprite getPicture();
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	char getType();

private:
	std::string m_type;
	sf::Sprite m_picture;
	sf::Texture m_texturePicture;
};