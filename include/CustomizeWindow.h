#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Button.h"
#include "fstream"
#include "Tile.h"
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

//--------------------------- const section -----------------------------------

const std::string WINDOWNAME = "Window";
const std::string BOARDNAME = "board.txt";
const std::string TOOLBAR = "Toolbar.txt";

const std::string ROBOTNAME = "robot.jpg";
const std::string DOORNAME = "door.jpg";
const std::string GUARDNAME = "guard.jpg";
const std::string STONENAME = "stone.jpg";
const std::string WALLNAME = "wall.jpg";
const std::string CLEARNAME = "clear.jpg";
const std::string SAVENAME = "save.jpg";
const std::string ERASERNAME = "eraser.jpg";

const char SPACETYPE = ' ';
const char ROBOTTYPE = '/';
const char GUARDTYPE = '!';
const char DOORTYPE = 'D';
const char WALLTYPE = '#';
const char STONETYPE = '@';

const int SPACEBUTTONS = 150;
const int MAXCOL = 33;
const int MAXROW = 15;
const int MIN = 1;

const sf::Vector2f STARTPOINTTILE = { 50, 150 };
const sf::Vector2f STARTPOINTBUTTONS = { 10, 10 };

//--------------------------- class section -----------------------------------

class CustomizeWindow
{
public:
	CustomizeWindow();
	void run();
	void mouseClicked(const sf::Event &event, int& cellClicked);
	void drawBoard();

private:
	sf::RenderWindow m_window;
	std::vector <Button> m_buttons;
	std::vector < std::vector <Tile> > m_board;
	std::fstream m_boardFile;
	float m_col;
	float m_row;

	void setTiles();
	void setFromFile();
	void setButtons();
	
	void createButton(const std::string typeName, sf::Vector2f &pos);
	bool clickedOnButton(sf::Vector2f pointClicked, int& cellClicked) const;
	void validCharacters(sf::Vector2f pointClicked, int cellClicked);
	bool clickedOnTile(sf::Vector2f &pointClicked, int buttonClicked, 
					   sf::Vector2i &wantedTile) const;
	void drawButtons();
	void drawTiles();
	bool pressedOnErase(sf::Vector2f pointClicked, int buttonClicked, 
						sf::Vector2i wantedTile);
	void clearBoard();
	void eraseObject(sf::Vector2f pointClicked);
	void placePicture(sf::Vector2f& pointClicked, int buttonClicked,
					  sf::Vector2i wantedTile);
	bool CheckImmediateResponse(int &buttonClicked);
	void saveBoard();
	void updateValues();
	std::string findCharacter(char type) const;
	char findTypeNameToChar(const std::string typeName) const;
	std::string findTypeCharToName(char type) const;
	void printAfterSave();
	void checkTile(int row, int col);
	void recieveValues();
	void setNewWindow();
};