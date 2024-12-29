#include "CustomizeWindow.h"

CustomizeWindow::CustomizeWindow()
	: m_window(sf::VideoMode::getDesktopMode(), "Window")
{
	std::cout << "Enter col and row wanted for the board\n";

	float row, col;
	std::cin >> col >> row;

	m_col = col;
	m_row = row;
	setTiles();
	setButtons();
	drawBoard();
}

void CustomizeWindow::drawPictures()
{
	for (int pic = 0; pic < m_pictures.size(); pic++)
	{
		m_window.draw(m_pictures[pic]);
	}
}

void CustomizeWindow::drawButtons()
{
	for (int Button = 0; Button < m_buttons.size(); Button++)
	{
		m_window.draw(m_buttons[Button].getPicture());
	}
}

void CustomizeWindow::drawTiles()
{
	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			m_window.draw(m_board[row][col].getTile());
		}
	}
}

void CustomizeWindow::setTiles()
{
	sf::Vector2f point = { 200, 200 };
	std::vector <Tile> rows;

	for (int row = 0; row < m_row; row++)
	{
		rows.clear();
		for (int col = 0; col < m_col; col++)
		{
			Tile newTile;
			newTile.setTilePosition(point);
			rows.push_back(newTile);
			point.x += 100;
		}
		m_board.push_back(rows);
		point.y += 100;
		point.x = 200;
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
		Button newButton("save.jpeg", pos);
		m_buttons.push_back(newButton);
		break;
	}

	default:
		break;
	}
	pos.x += 150;
}

bool CustomizeWindow::clickedOnButton(sf::Vector2f pointClicked, int &cellClicked, 
									  int& robotPosition, int& doorPosition)
{
	for (int button = 0; button < m_buttons.size(); button++)
	{
		if (m_buttons[button].getGlobalBounds().contains(pointClicked))
		{
			cellClicked = button;
			if ('r' == m_buttons[button].getType())
			{
				robotPosition = button;
			}

			if ('d' == m_buttons[button].getType())
			{
				doorPosition = button;
			}

			return true;
		}
	}
	return false;
}

void CustomizeWindow::placePicture(sf::Vector2f pointClicked, int cellClicked)
{
	sf::Sprite picture = m_buttons[cellClicked].getPicture();
	picture.setPosition(pointClicked);
	m_pictures.push_back(picture);
}

void CustomizeWindow::drawBoard()
{
	m_window.clear(); // To ensure the window is default

	drawTiles();
	drawPictures();
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

void CustomizeWindow::mouseClicked(const sf::Event event, int &cellClicked,
								   int & robotPosition, int& doorPosition)
{
	auto pointClicked = m_window.mapPixelToCoords(
		{ event.mouseButton.x, event.mouseButton.y });

	if (clickedOnButton(pointClicked, cellClicked, robotPosition, doorPosition)) {}

	else if (cellClicked >= 0)
	{
		if (clickedOnTile(pointClicked))
		{
			if (cellClicked == robotPosition)
			{
				robotPosition = -1;
			}

			else if (cellClicked == doorPosition)
			{
				doorPosition = -1;
			}

			placePicture(pointClicked, cellClicked);
			drawBoard();
		}
	}
}

bool CustomizeWindow::clickedOnTile(sf::Vector2f &pointClicked)
{
	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			if (m_board[row][col].doesContain(pointClicked))
			{
				for (int pic = 0; pic < m_pictures.size(); pic++)
				{
					if (m_pictures[pic].getGlobalBounds().contains(pointClicked))
					{
						m_pictures.erase(m_pictures.begin() + pic);
					}
				}
				pointClicked = m_board[row][col].getPosition();
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