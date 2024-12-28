#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

const float HEIGHT = 200;
const float WIDTH = 100;

class Board
{
public:
	Board(float col, float row);
	sf::RectangleShape getBoard();
	void setBoard(sf::Vector2f point);
	void setOriginBoard();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	sf::Vector2f getTable();

private:
	sf::RectangleShape m_board;
	float m_row;
	float m_col;
};