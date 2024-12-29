#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Button.h"
#include "fstream"
#include "Tile.h"

class CustomizeWindow
{
public:
	CustomizeWindow();
	void drawBoard();
	bool isWindowOpen();
	bool isEvent(sf::Event &event);
	void closeWindow();
	void mouseClicked(const sf::Event event, int& cellClicked,
					  int& robotExists, int& doorExists);

private:
	sf::RenderWindow m_window;
	std::vector <Button> m_buttons;
	std::vector <sf::Sprite> m_pictures;
	std::vector < std::vector <Tile> > m_board;
	float m_col;
	float m_row;
	
	void setTiles();
	void setButtons();
	
	void createButton(std::string typeName, sf::Vector2f &pos);
	bool clickedOnButton(sf::Vector2f pointClicked, int& cellClicked,
						 int& robotExists, int& doorExists);
	void placePicture(sf::Vector2f pointClicked, int cellClicked);
	bool clickedOnTile(sf::Vector2f &pointClicked);
	void drawPictures();
	void drawButtons();
	void drawTiles();
	
};