#include <iostream>
#include <fstream>
#include <vector>


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	int serialNumber = 0;
	std::vector<std::vector<int>> sum(301, std::vector<int>(301));
	int cellPower = 0;

	in >> serialNumber;

	for (int x = 1; x <= 300; x++)
	{
		for (int y = 1; y <= 300; y++)
		{
			cellPower = 0;
			cellPower = (((x + 10) * y + serialNumber) * (x + 10));
			cellPower = log10(cellPower) + 1 > 2 ? cellPower % 1000 / 100 - 5 : 0;
			sum[x][y] = cellPower + sum[x - 1][y] + sum[x][y - 1] - sum[x - 1][y - 1];
		}

	}

	int currentPower = 0;
	int maxPower = sum[3][3];
	int posX = 1, posY = 1;

	for (int x = 1; x <= 298; x++)
	{
		for (int y = 1; y < 298; y++)
		{
			currentPower = sum[x - 1][y - 1] + sum[x + 2][y + 2] - sum[x + 2][y - 1] - sum[x - 1][y + 2];

			if (currentPower > maxPower)
			{
				maxPower = currentPower;
				posX = x;
				posY = y;
			}
		}
	}

	out << posX << "," << posY;
	in.close();
	out.close();
}