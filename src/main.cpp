#include <iostream>
#include "CustomizeWindow.h"

void getCoordinats(float& col, float& row);

int main()
{
	float col = 0, row = 0;
	getCoordinats(col, row);
	auto board = CustomizeWindow(col, row);

	board.run();

	exit(EXIT_SUCCESS);
}

void getCoordinats(float& col, float& row)
{
	/*if(board.exists)
	{
		return;
	}*/

	std::cout << "Enter col and row wanted for the board\n";
	
	while (std::cin >> col >> row)
	{
		if (row > 2 && col > 2)
		{
			break;
		}
		std::cout << "Enter col and row at least 2\n";
	}
}
