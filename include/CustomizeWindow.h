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
	void mouseClicked(const sf::Event &event, int& cellClicked);

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
	bool clickedOnButton(sf::Vector2f pointClicked, int& cellClicked);
	void validCharacters(sf::Vector2f pointClicked, int cellClicked);
	bool clickedOnTile(sf::Vector2f &pointClicked, int buttonClicked, sf::Vector2i &wantedTile);
	void drawButtons();
	void drawTiles();
	bool pressedOnErase(sf::Vector2f pointClicked, int buttonClicked, sf::Vector2i wantedTile);
	void clearBoard();
	void eraseObject(sf::Vector2f pointClicked);
	void placePicture(sf::Vector2f& pointClicked, int buttonClicked, sf::Vector2i wantedTile);
	bool CheckImmediateResponse(int buttonClicked);
	void saveBoard();
};