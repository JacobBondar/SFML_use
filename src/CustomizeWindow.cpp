#include "CustomizeWindow.h"

//-----------------------------------------------------------------------------

CustomizeWindow::CustomizeWindow()
	: m_window(sf::VideoMode::getDesktopMode(), WINDOWNAME), m_row(0), m_col(0)
{
	m_boardFile.open(BOARDNAME, std::ios::out | std::ios::in);
	if (m_boardFile) // file exists
	{
		updateValues();
	}
	
	else
	{
		std::cout <<"Enter 1 <= col <= 33 and 1 <= row <= 15 wanted for the board\n";
		while (std::cin >> m_col >> m_row)
		{
			
			if ((m_col <= 33 && m_row <= 15) && (m_col >= 1 && m_row >= 1))
			{
				break;
			}
			std::cout << "Enter valid parameters for col and row\n"
				<< "Enter 1 <= col <= 33 and 1 <= row <= 15 wanted for the board\n";
		}

		m_boardFile.open(BOARDNAME, 
						 std::ios::out | std::ios::in | std::ios::trunc);
		if (!m_boardFile)
		{
			std::cerr << "Can't open the board\n";
			exit(EXIT_FAILURE);
		}
	}

	setButtons();
	setTiles();
	setFromFile();

	drawBoard();
}

//-----------------------------------------------------------------------------

void CustomizeWindow::updateValues()
{
	std::string line;
	while (std::getline(m_boardFile, line))
	{
		m_row++;

		if (m_col < line.length())
		{
			m_col = line.length();
		}
	}
}

//-----------------------------------------------------------------------------

std::string CustomizeWindow::findTypeCharToName(char type)
{
	switch (type)
	{
		case ROBOTTYPE:
		{
			return ROBOTNAME;
		}

		case GUARDTYPE:
		{
			return GUARDNAME;
		}

		case STONETYPE:
		{
			return STONENAME;
		}

		case WALLTYPE:
		{
			return WALLNAME;
		}

		case DOORTYPE:
		{
			return DOORNAME;
		}
	}
	return SPACENAME;
}

//-----------------------------------------------------------------------------

void CustomizeWindow::printAfterSave()
{
	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			m_board[row][col].setAfterSave();
			m_board[row][col].draw(m_window);
			m_board[row][col].setToDefault();
		}
	}
	drawButtons();
	m_window.display();
	std::this_thread::sleep_for(2000ms);
}

//-----------------------------------------------------------------------------

void CustomizeWindow::drawButtons()
{
	for (int index = 0; index < m_buttons.size(); index++)
	{
		m_buttons[index].draw(m_window);
	}
}

//-----------------------------------------------------------------------------

void CustomizeWindow::drawTiles()
{
	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			m_board[row][col].draw(m_window);
		}
	}
}

//-----------------------------------------------------------------------------

void CustomizeWindow::setTiles()
{
	sf::Vector2f point = STARTPOINTTILE;
	std::vector <Tile> rows;

	for (int row = 0; row < m_row; row++)
	{
		rows.clear();
		for (int col = 0; col < m_col; col++)
		{
			Tile newTile;
			newTile.setTilePosition(point);
			rows.push_back(newTile);
			point.x += 55;
		}
		m_board.push_back(rows);
		point.y += 55;
		point.x = 50;
	}
}

//-----------------------------------------------------------------------------

void CustomizeWindow::setFromFile()
{
	int row = 0, col = 0;
	char type;
	std::string typeName;
	m_boardFile.clear();
	m_boardFile.seekp(0, std::ios::beg);

	while (m_boardFile.get(type))
	{
		if (type == '\n')
		{
			row++;
			col = 0;
			continue;
		}

		typeName = findTypeCharToName(type);
		m_board[row][col].setType(typeName);
		for (int button = 0; button < m_buttons.size(); button++)
		{
			if (typeName == m_buttons[button].getType())
			{
				m_board[row][col].setPicture(m_buttons[button].getPicture());
				m_board[row][col].setPicturePosition(m_board[row][col].getTilePosition());
				break;
			}
		}
		col++;
	}
}

//-----------------------------------------------------------------------------

void CustomizeWindow::setButtons()
{
	std::ifstream file;
	file.open(TOOLBAR);
	if (!file)
	{
		std::cerr << "Can't open the Toolbar file\n";
		exit(EXIT_FAILURE);
	}

	char type;
	std::string typeName;
	sf::Vector2f pos = STARTPOINTBUTTONS;
	while (file >> type)
	{
		typeName = findCharacter(type);

		createButton(typeName, pos);
	}
	file.close();

	createButton(ERASERNAME, pos);
	createButton(CLEARNAME, pos);
	createButton(SAVENAME, pos);
}

std::string CustomizeWindow::findCharacter(char type)
{
	switch (type)
	{
		case ROBOTTYPE:
		{
			return ROBOTNAME;
		}

		case GUARDTYPE:
		{
			return GUARDNAME;
		}

		case STONETYPE:
		{
			return STONENAME;
		}

		case WALLTYPE:
		{
			return WALLNAME;
		}

		case DOORTYPE:
		{
			return DOORNAME;
		}
	}
	return SPACENAME;
}

void CustomizeWindow::createButton(std::string typeName, sf::Vector2f &pos)
{
	Button newButton(typeName, pos);
	m_buttons.push_back(newButton);

	pos.x += 150;
}

bool CustomizeWindow::clickedOnButton(sf::Vector2f pointClicked, int &cellClicked)
{
	for (int button = 0; button < m_buttons.size(); button++)
	{
		if (m_buttons[button].getGlobalBounds().contains(pointClicked))
		{
			cellClicked = button;
			return true;
		}
	}
	return false;
}

void CustomizeWindow::validCharacters(sf::Vector2f pointClicked, int buttonClicked)
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			if (m_board[i][j].doesContain(pointClicked))
			{
				continue;
			}

			if (m_board[i][j].getType() == m_buttons[buttonClicked].getType())
			{
				if (m_board[i][j].getType() == ROBOTNAME || m_board[i][j].getType() == DOORNAME)
				{
					m_board[i][j].setType(SPACENAME);
					m_board[i][j].resetPicture();
				}
			}
		}
	}
}

void CustomizeWindow::drawBoard()
{
	m_window.clear(); // To ensure the window is default
	
	drawTiles();
	drawButtons();

	m_window.display();
}

bool CustomizeWindow::isWindowOpen()
{
	return m_window.isOpen();
}

bool CustomizeWindow::isEvent(sf::Event& event)
{
	return m_window.waitEvent(event);
}

void CustomizeWindow::closeWindow()
{
	m_window.close();
}

void CustomizeWindow::mouseClicked(const sf::Event &event, int & buttonClicked)
{
	auto pointClicked = m_window.mapPixelToCoords(
		{ event.mouseButton.x, event.mouseButton.y });

	clickedOnButton(pointClicked, buttonClicked);

	if(buttonClicked >= 0)
	{
		if (CheckImmediateResponse(buttonClicked)) {}

		else
		{
			sf::Vector2i wantedTile;
			bool onTile = clickedOnTile(pointClicked, buttonClicked, wantedTile);

			if (onTile)
			{
				if (pressedOnErase(pointClicked, buttonClicked, wantedTile)) {}

				else if (buttonClicked < m_buttons.size()) // for reassurance
				{
					placePicture(pointClicked, buttonClicked, wantedTile);
					validCharacters(pointClicked, buttonClicked);
				}
				drawBoard();
			}
		}
	}
}

bool CustomizeWindow::pressedOnErase(sf::Vector2f pointClicked, int buttonClicked, sf::Vector2i wantedTile)
{
	if (m_buttons[buttonClicked].getType() != ERASERNAME)
	{
		return false;
	}

	eraseObject(pointClicked);
	return true;
}

void CustomizeWindow::clearBoard()
{
	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			if (m_board[row][col].getType() != SPACENAME)
			{
				m_board[row][col].resetPicture();
				m_board[row][col].setType(SPACENAME);
			}
		}
	}
}

void CustomizeWindow::eraseObject(sf::Vector2f pointClicked)
{
	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			if (m_board[row][col].doesContain(pointClicked))
			{
				if (m_board[row][col].getType() != SPACENAME)
				{
					m_board[row][col].resetPicture();
					m_board[row][col].setType(SPACENAME);
				}
			}
		}
	}
}

void CustomizeWindow::placePicture(sf::Vector2f& pointClicked, int buttonClicked, sf::Vector2i wantedTile)
{
	sf::Sprite picture = m_buttons[buttonClicked].getPicture();

	pointClicked = m_board[wantedTile.y][wantedTile.x].getPosition();
	m_board[wantedTile.y][wantedTile.x].setType(m_buttons[buttonClicked].getType());
	m_board[wantedTile.y][wantedTile.x].setPicture(picture);
	m_board[wantedTile.y][wantedTile.x].setPicturePosition(pointClicked);
}

bool CustomizeWindow::CheckImmediateResponse(int buttonClicked)
{
	std::string gotText = m_buttons[buttonClicked].getType();

	if (gotText == SAVENAME)
	{
		saveBoard();
	}

	else if (gotText == CLEARNAME)
	{
		clearBoard();
	}

	else
	{
		return false;
	}
	drawBoard();
	return true;
}

void CustomizeWindow::saveBoard()
{
	m_boardFile.clear();
	m_boardFile.seekp(0, std::ios::beg);

	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			char type = findTypeNameToChar(m_board[row][col].getType());
			m_boardFile << type;
		}
		m_boardFile << '\n';
	}
	m_boardFile.flush();

	printAfterSave();
}

char CustomizeWindow::findTypeNameToChar(std::string typeName)
{
	if (typeName == ROBOTNAME)
	{
		return ROBOTTYPE;
	}

	else if (typeName == GUARDNAME)
	{
		return GUARDTYPE;
	}

	else if (typeName == STONENAME)
	{
		return STONETYPE;
	}

	else if (typeName == WALLNAME)
	{
		return WALLTYPE;
	}

	else if (typeName == DOORNAME)
	{
		return DOORTYPE;
	}

	return SPACETYPE;
}

bool CustomizeWindow::clickedOnTile(sf::Vector2f &pointClicked, int buttonClicked, sf::Vector2i &wantedTile)
{
	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			if (m_board[row][col].doesContain(pointClicked))
			{
				wantedTile.x = col;
				wantedTile.y = row;
				return true;
			}
		}
	}
	return false;
}

void CustomizeWindow::closeFile()
{
	m_boardFile.close();
}