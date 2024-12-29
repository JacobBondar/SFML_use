#include "Controller.h"
#include "Controller.h"

Controller::Controller(){}

void Controller::run()
{
	auto event = sf::Event{};
	int cellClicked = -1;
	int robotPosition = -1, doorPosition = -1;

	while (m_paint.isWindowOpen())
	{
		if (m_paint.isEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				m_paint.closeWindow();
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				m_paint.mouseClicked(event, cellClicked, robotPosition, doorPosition);

				break;
			}
			}
		}
	}
}

void Controller::draw()
{
	m_paint.drawBoard();
}