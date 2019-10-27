#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

const int serialNumber = 4172;

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<std::vector<int>> grid(301, std::vector<int>(301, -6));
	int totalPower = 0;

	// Calculating the power level for the first square (1,1) - (3,3) and the total power level
	for (int x = 1; x <= 3; x++)
	{
		for (int y = 1; y <= 3; y++)
		{
			grid[x][y] = (((x + 10) * y + serialNumber) * (x + 10));
			grid[x][y] = log10(grid[x][y]) + 1 > 2 ? grid[x][y] % 1000 / 100 - 5 : 0;
			totalPower += grid[x][y];
		}
	}

	int maxPower = totalPower;
	int auxPower = totalPower;
	int posX = 1, posY = 1;

	for (int x = 1; x <= 298; x++)
	{
		// We save the total power of the first square 
		auxPower = totalPower;
		for (int y = 2; y <= 298; y++)
		{
			// We subtract from the total power the elements from the first collumn of the square
			// At the moment we have 2 collums in a row in the total power and add the third one to make a square
			// So we calculate the power level for the new cells and than add them to the total power
			totalPower = totalPower - grid[x][y - 1] - grid[x + 1][y - 1] - grid[x + 2][y - 1];
			for (int itX = x; itX <= x + 2; itX++)
			{

				grid[itX][y + 2] = (((itX + 10) * (y + 2) + serialNumber) * (itX + 10));
				grid[itX][y + 2] = log10(grid[itX][y + 2]) + 1 > 2 ? grid[itX][y + 2] % 1000 / 100 - 5 : 0;
				totalPower += grid[itX][y + 2];
			}

			if (totalPower > maxPower)
			{
				maxPower = totalPower;
				posX = x;
				posY = y;
			}
		}

		totalPower = auxPower;

		if (x < 298)
		{
			totalPower = totalPower - grid[x][1] - grid[x][2] - grid[x][3];
			for (int itY = 1; itY <= 3; itY++)
			{
				grid[x + 3][itY] = (((x + 3 + 10) * itY + serialNumber) * (x + 3 + 10));
				grid[x + 3][itY] = log10(grid[x + 3][itY]) + 1 > 2 ? grid[x + 3][itY] % 1000 / 100 - 5 : 0;
				totalPower += grid[x + 3][itY];
			}
			auxPower = totalPower;

			if (totalPower > maxPower)
			{
				maxPower = totalPower;
				posX = x;
				posY = 1;
			}
		}
	}

	out << posX << "," << posY;
	in.close();
	out.close();
}