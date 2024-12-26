#include "Buttom.h"

Buttom::Buttom(std::string text, sf::Vector2f position) :
	m_buttom(sf::Vector2f(10, 20)), m_type(text)
{
	m_buttom.setPosition(position);
	m_buttom.setFillColor(sf::Color::White);
}

sf::RectangleShape Buttom::getButtom() const
{
	return m_buttom;
}