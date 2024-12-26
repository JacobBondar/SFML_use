#include "Board.h"

Board::Board(float col, float row) :
	m_board({col, row})
{
	m_board.setFillColor(sf::Color::Black);
	m_board.setOutlineColor(sf::Color::White);
	m_board.setOutlineThickness(5);
	
}

sf::RectangleShape Board::getBoard()
{
	return m_board;
}

void Board::setBoard(sf::Vector2f point)
{
	m_board.setPosition(point);
}

void Board::setOriginBoard()
{
	m_board.setOrigin(m_board.getSize() / 2.f);
}
