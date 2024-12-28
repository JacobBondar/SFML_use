#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Buttom.h"
#include "fstream"
#include "Board.h"

class CustomizeWindow
{
public:
	CustomizeWindow(float col, float row);
	void run();

private:
	sf::RenderWindow m_window;
	std::vector <Buttom> m_buttoms;
	std::vector <sf::Sprite> m_pictures;
	Board m_board;

	void setBoard();
	void setButtoms();
	void drawBoard();
	void createButtom(std::string typeName, sf::Vector2f &pos);
	void setLines();
	sf::Vector2f findTopLeft();
	bool clickedOnButton(sf::Vector2f pointClicked, int& cellClicked);
	void placePicture(sf::Vector2f location, int cellClicked);
	void setPictures();
};