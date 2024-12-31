#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button(const std::string text, sf::Vector2f position);
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	std::string getType() const;
	sf::Sprite getPicture() const;
	void draw(sf::RenderWindow& window) const;

private:
	sf::Texture m_texturePicture;
	std::string m_type;
	sf::Vector2f m_position;
};