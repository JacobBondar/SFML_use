#include "CustomizeWindow.h"
using std::ifstream;

CustomizeWindow::CustomizeWindow(float col, float row)
	: m_window(sf::VideoMode::getDesktopMode(), "Window"),
	m_board(col * 100, row * 100)
{
	m_window.clear(); // To ensure the window is default

	setBoard();
	setButtoms();
	setLines();


	m_window.display();
}

void CustomizeWindow::setBoard()
{
	sf::Vector2u windowPos = m_window.getSize();
	sf::Vector2f fpoint = { (float)windowPos.x / 2, (float)windowPos.y / 2 + 10};
	m_board.setOriginBoard();
	m_board.setBoard(fpoint);
	m_window.draw(m_board.getBoard());
}

void CustomizeWindow::setButtoms()
{
	ifstream file;
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
		createButtom(typeName, pos);
	}
	file.close();

	createButtom("Erase Object", pos);
	createButtom("Clear Board", pos);
	createButtom("Save Board", pos);

	for (int buttom = 0; buttom < m_buttoms.size(); buttom++)
	{
		m_window.draw(m_buttoms[buttom].getPicture());
	}
}

void CustomizeWindow::createButtom(std::string typeName, sf::Vector2f &pos)
{
	switch (typeName[0])
	{
	case '/':
	{
		Buttom newButtom("robot.jpeg", pos);
		m_buttoms.push_back(newButtom);
		break;
	}

	case '!':
	{
		Buttom newButtom("guard.jpeg", pos);
		m_buttoms.push_back(newButtom);
		break;
	}

	case '@':
	{
		Buttom newButtom("stone.jpeg", pos);
		m_buttoms.push_back(newButtom);
		break;
	}

	case '#':
	{
		Buttom newButtom("wall.jpeg", pos);
		m_buttoms.push_back(newButtom);
		break;
	}

	case 'D':
	{
		Buttom newButtom("door.jpeg", pos);
		m_buttoms.push_back(newButtom);
		break;
	}

	case 'E':
	{
		Buttom newButtom("eraser.jpeg", pos);
		m_buttoms.push_back(newButtom);
		break;
	}
	case 'C':
	{
		Buttom newButtom("clear.jpeg", pos);
		m_buttoms.push_back(newButtom);
		break;
	}

	case 'S':
	{
		Buttom newButtom("save.jpeg", pos);
		m_buttoms.push_back(newButtom);
		break;
	}

	default:
		break;
	}
	pos.x += 150;
}

void CustomizeWindow::setLines()
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

void CustomizeWindow::run()
{
	auto event = sf::Event{};
	while (m_window.isOpen())
	{
		if (m_window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				break;
			}
		}
	}
}





void CustomizeWindow::drawBoard()
{
	for (int index = 0; index < m_buttoms.size(); index++)
	{
		m_window.draw(m_buttoms[index].getPicture());
	}
	 

	m_window.display();
}

/*
void CustomizeWindow::run()
{
	auto event = sf::Event{};
	while (m_window.isOpen())
	{
		if (m_window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				handleClick(event.mouseButton);
				break;
			}
		}
	}
}

void CustomizeWindow::handleClick(const sf::Event::MouseButtonEvent& event)
{
	m_window.clear();
	if (m_circle.getGlobalBounds().contains(
		m_window.mapPixelToCoords({ event.x, event.y })))
	{
		m_circle.setFillColor(sf::Color::Green);
	}

	else
	{
		m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
		m_circle.setPosition(m_window.mapPixelToCoords({ event.x, event.y }));
	}
	m_window.draw(m_circle);
	m_window.display();
}
*/