#pragma once
#include <SFML/Graphics.hpp>
#include "CustomizeWindow.h"
#include "Button.h"
#include "Tile.h"

class Controller
{
public:
	Controller();
	void run();

private:
	CustomizeWindow m_paint;
};