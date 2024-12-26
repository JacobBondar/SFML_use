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

private:
	sf::RectangleShape m_board;

};