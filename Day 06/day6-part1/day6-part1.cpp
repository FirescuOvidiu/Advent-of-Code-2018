#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>


class Coordinates
{
public:
	Coordinates(int _x, int _y) : x(_x), y(_y) {}

public:
	int x;
	int y;
};


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	
	std::vector<Coordinates> coord;
	int nCoord = 0, row = 0, column = 0;
	int x = 0, y = 0;
	char c{};

	while (in >> y >> c >> x)
	{
		coord.push_back(Coordinates(x, y));
		if (coord[nCoord].x > row)
		{
			row = coord[nCoord].x + 1;
		}

		if (coord[nCoord].y > column)
		{
			column = coord[nCoord].y + 1;
		}
		nCoord++;
	}

	std::vector<int> frequency(nCoord, 0);
	int min = 0, distManhattan = 0, position = 0;

	for (int l = 0; l < row; l++)
	{
		for (int c = 0; c < column; c++)
		{
			min = abs(coord[0].x - l) + abs(coord[0].y - c);
			position = 0;

			for (int it = 1; it < nCoord; it++)
			{
				distManhattan = abs(coord[it].x - l) + abs(coord[it].y - c);
				if (min == distManhattan)
				{
					position = -1;
				}

				if (min > distManhattan)
				{
					min = distManhattan;
					position = it;
				}
			}

			if (position != -1)
			{
				if ((l == 0) || (l == row - 1) || (c == 0) || (c == column - 1))
				{
					frequency[position] = -1;
				}

				if (frequency[position] != -1)
				{
					frequency[position]++;
				}
			}
		}
	}

	int largestArea = 0;

	for (int it = 0; it < nCoord; it++)
	{
		if (frequency[it] > largestArea)
		{
			largestArea = frequency[it];
		}
	}

	out << largestArea;
	in.close();
	out.close();
}
