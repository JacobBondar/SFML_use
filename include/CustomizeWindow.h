#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Buttom.h"
#include "fstream"
#include "Board.h"
const int MIN_WIDTH = 500;
const int HEIGHT_TOOLBAR = 500;

class CustomizeWindow
{
public:
	CustomizeWindow(int col, int row);
	void run();

private:
	sf::RenderWindow m_window;
	std::vector <Buttom> m_buttoms;
	Board m_board;

	void setBoard();
	void setButtoms();
	void drawBoard();
	void createButtom(std::string typeName, sf::Vector2f &pos);
};