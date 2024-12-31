#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button(std::string text, sf::Vector2f position);
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	std::string getType();
	void draw(sf::RenderWindow& window);
	sf::Sprite getPicture();

private:
	sf::Texture m_texturePicture;
	std::string m_type;
	sf::Vector2f m_position;
};