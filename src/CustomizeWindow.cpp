#include "CustomizeWindow.h"
using std::ifstream;

CustomizeWindow::CustomizeWindow(int col, int row)
	: m_window(sf::VideoMode(col + MIN_WIDTH, row + HEIGHT_TOOLBAR), "Window"),
	m_board(col, row)
{
	m_window.clear(); // To ensure the window is default
	
	setBoard();
	setButtoms();

	m_window.display();
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

void CustomizeWindow::setBoard()
{
	sf::Vector2u windowPos = m_window.getSize();
	sf::Vector2f fpoint = { (float)windowPos.x / 2, (float)windowPos.y / 2 };
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
		std::cerr << "Can't open the main file\n";
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


	auto guard = sf::Texture();
	guard.loadFromFile("guard.jpeg");

	auto sprite = sf::Sprite(guard);
	sprite.setPosition({0, 0});

	m_window.draw(sprite);
}

void CustomizeWindow::createButtom(std::string typeName, sf::Vector2f &pos)
{
	Buttom newButtom(typeName, pos);
	m_buttoms.push_back(newButtom);
	pos.x += 10;
}







void CustomizeWindow::drawBoard()
{
	for (int index = 0; index < m_buttoms.size(); index++)
	{
		m_window.draw(m_buttoms[index].getButtom());
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