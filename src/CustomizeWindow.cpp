#include "CustomizeWindow.h"

CustomizeWindow::CustomizeWindow()
	: m_window(sf::VideoMode::getDesktopMode(), "Window")
{
	std::ifstream checkBoard("board.txt");

	if (!checkBoard)
	{
		std::cout << "Enter col and row wanted for the board\n";

		float row, col;
		std::cin >> col >> row;
		m_col = col;
		m_row = row;
	}

	std::ofstream board("resources/board.txt");
	
	setTiles();
	setButtons();
	drawBoard();
}

void CustomizeWindow::drawButtons()
{
	for (int index = 0; index < m_buttons.size(); index++)
	{
		m_buttons[index].draw(m_window);
	}
}

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

void CustomizeWindow::setTiles()
{
	sf::Vector2f point = { 50, 150 };
	std::vector <Tile> rows;

	for (int row = 0; row < m_row; row++)
	{
		rows.clear();
		for (int col = 0; col < m_col; col++)
		{
			Tile newTile;
			newTile.setTilePosition(point);
			rows.push_back(newTile);
			point.x += 110;
		}
		m_board.push_back(rows);
		point.y += 110;
		point.x = 50;
	}
}

void CustomizeWindow::setButtons()
{
	std::ifstream file;
	file.open("Toolbar.txt");
	if (!file)
	{
		std::cerr << "Can't open the Toolbar file\n";
		exit(EXIT_FAILURE);
	}

	char type;
	std::string typeName;
	sf::Vector2f pos = { 10, 10 };
	while (file >> type)
	{
		typeName = type;
		createButton(typeName, pos);
	}
	file.close();

	createButton("Erase Object", pos);
	createButton("Clear Board", pos);
	createButton("Save Board", pos);
}

void CustomizeWindow::createButton(std::string typeName, sf::Vector2f &pos)
{
	switch (typeName[0])
	{
	case '/':
	{
		Button newButton("robot.jpeg", pos);
		m_buttons.push_back(newButton);
		break;
	}

	case '!':
	{
		Button newButton("guard.jpeg", pos);
		m_buttons.push_back(newButton);
		break;
	}

	case '@':
	{
		Button newButton("stone.jpeg", pos);
		m_buttons.push_back(newButton);
		break;
	}

	case '#':
	{
		Button newButton("wall.jpeg", pos);
		m_buttons.push_back(newButton);
		break;
	}

	case 'D':
	{
		Button newButton("door.jpeg", pos);
		m_buttons.push_back(newButton);
		break;
	}

	case 'E':
	{
		Button newButton("eraser.jpeg", pos);
		m_buttons.push_back(newButton);
		break;
	}
	case 'C':
	{
		Button newButton("clear.jpeg", pos);
		m_buttons.push_back(newButton);
		break;
	}

	case 'S':
	{
		Button newButton("boardSave.jpeg", pos);
		m_buttons.push_back(newButton);
		break;
	}

	default:
		break;
	}
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
				if (m_board[i][j].getType() == 'r' || m_board[i][j].getType() == 'd')
				{
					std::cout << "here\n";
					m_board[i][j].setType('0');
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
	if (m_buttons[buttonClicked].getType() != 'e')
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
			if (m_board[row][col].getType() != '0')
			{
				m_board[row][col].resetPicture();
				m_board[row][col].setType('0');
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
				if (m_board[row][col].getType() != '0')
				{
					m_board[row][col].resetPicture();
					m_board[row][col].setType('0');
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
	switch (m_buttons[buttonClicked].getType())
	{
		case 'b':
		{
			saveBoard();
			break;
		}

		case 'c':
		{
			clearBoard();
			break;
		}

		default:
		{
			return false;
		}
	}
	drawBoard();
	return true;
}

void CustomizeWindow::saveBoard() // do yay
{
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


/*void CustomizeWindow::setLines()
{
	sf::Vector2f size = m_board.getSize();
	sf::Vector2f pointStart = findTopLeft();

	sf::Vector2f temp = pointStart;
	sf::Vector2f pointEnd;

	std::vector <sf::Vertex> lines; //odd - start, even - end. 0-1, 2-3, 4-5

	for (float hori = 0; hori <= m_board.getTable().x / 100; hori++, temp.x += 100)
	{
		lines.push_back(temp);
		pointEnd = temp;
		pointEnd.y += size.y;

		lines.push_back(pointEnd);
	}
	
	temp = pointStart;
	for (float vert = 0; vert <= m_board.getTable().y / 100; vert++, temp.y += 100)
	{
		lines.push_back(temp);
		pointEnd = temp;
		pointEnd.x += size.x;

		lines.push_back(pointEnd);
	}

	for (int cell = 0; cell < lines.size(); cell += 2)
	{
		sf::Vertex line2[] = 
		{
			lines[cell], // Start point
			lines[cell + 1] // End point
		};
		m_window.draw(line2, 2, sf::Lines);
	}
}

sf::Vector2f CustomizeWindow::findTopLeft()
{
	sf::Vector2f pointStart = m_board.getPosition();
	sf::Vector2f length = m_board.getSize();
	pointStart.x -= length.x / 2;
	pointStart.y -= length.y / 2;

	return pointStart;
}
*/