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
	char c;

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

	int sum = 0, distManhattan = 0, count = 0;

	for (int l = 0; l < row; l++)
	{
		for (int c = 0; c < column; c++)
		{
			for (int it = 0; it < nCoord; it++)
			{
				distManhattan = abs(coord[it].x - l) + abs(coord[it].y - c);
				sum = sum + distManhattan;
			}

			if (sum < 10000)
			{
				count++;
			}
		}
	}

	out << count;
	in.close();
	out.close();
}
