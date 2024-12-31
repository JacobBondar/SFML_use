#pragma once
#include <SFML/Graphics.hpp>
#include <string>

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
const std::string SPACENAME = " ";

const char SPACETYPE = ' ';
const char ROBOTTYPE = '/';
const char GUARDTYPE = '!';
const char DOORTYPE = 'D';
const char WALLTYPE = '#';
const char STONETYPE = '@';

const int SIZEOFPICTURE = 50;
const int SPACEBUTTONS = 150;

const sf::Vector2f STARTPOINTTILE = { 50, 150 };
const sf::Vector2f STARTPOINTBUTTONS = { 10, 10 };