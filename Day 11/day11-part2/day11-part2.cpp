#include <iostream>
#include <fstream>
#include <vector>
#include <string>


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
	int maxPower = sum[0][0];
	int posX = 1, posY = 1, totalSize = 1;

	for (int size = 1; size <= 300; size++)
	{
		for (int x = 1; x <= 301 - size; x++)
		{
			for (int y = 1; y <= 301 - size; y++)
			{
				currentPower = sum[x - 1][y - 1] + sum[x + size - 1][y + size - 1] - sum[x + size - 1][y - 1] - sum[x - 1][y + size - 1];

				if (currentPower > maxPower)
				{
					maxPower = currentPower;
					posX = x;
					posY = y;
					totalSize = size;
				}
			}
		}
	}

	out << posX << "," << posY << "," << totalSize;
	in.close();
	out.close();
}