#include "Board.h"

Board::Board(float col, float row) :
	m_board({ col, row }), m_col(col), m_row(row)
{
	m_board.setFillColor(sf::Color::Black);
	m_board.setOutlineColor(sf::Color::White);
	m_board.setOutlineThickness(1);
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

sf::Vector2f Board::getPosition()
{
	return m_board.getPosition();
	
}

sf::Vector2f Board::getTable()
{
	return { m_col, m_row };
}

sf::Vector2f Board::getSize()
{
	return m_board.getSize();
}