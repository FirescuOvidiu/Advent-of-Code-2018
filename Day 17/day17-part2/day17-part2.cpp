#include <iostream>
#include <fstream>
#include <vector>


void readInput(std::fstream& in, std::vector<std::vector<char>>& map, int& maxX, int& maxY, int& minX)
{
	char var1, var2, aux;
	int x, y1, y2;

	while (in >> var1 >> aux >> x >> aux >> var2 >> aux >> y1 >> aux >> aux >> y2)
	{
		if (var1 == 'x')
		{
			if (y1 < minX) minX = y1;
			if (y2 > maxX) maxX = y2;
			if (x > maxY) maxY = x;

			for (int it = y1; it <= y2; it++)
			{
				map[it][x] = '#';
			}
		}
		else
		{
			if (x < minX) minX = x;
			if (x > maxX) maxX = x;
			if (y2 > maxY) maxY = y2;

			for (int it = y1; it <= y2; it++)
			{
				map[x][it] = '#';
			}
		}
	}
	map[0][500] = '+';
}


void solveProblem(std::pair<int, int> currWaterPos, std::vector<std::vector<char>>& map, int maxX, int maxY)
{
	if (currWaterPos.first >= maxX)
	{
		return;
	}

	switch (map[currWaterPos.first + 1][currWaterPos.second])
	{
	case '.':
		map[currWaterPos.first + 1][currWaterPos.second] = '|';
		solveProblem(std::pair<int, int>(currWaterPos.first + 1, currWaterPos.second), map, maxX, maxY);
	case '#':
	case '~':
		while (true)
		{
			int y1 = currWaterPos.second;
			int y2 = currWaterPos.second;

			while ((y1 >= 0) && (map[currWaterPos.first + 1][y1] != '.') && (map[currWaterPos.first][y1 - 1] != '#') && (map[currWaterPos.first + 1][y1] != '|'))
			{
				y1--;
			}

			while ((y2 <= maxY + 1) && (map[currWaterPos.first + 1][y2] != '.') && (map[currWaterPos.first][y2 + 1] != '#') && (map[currWaterPos.first + 1][y2] != '|'))
			{
				y2++;
			}

			if ((map[currWaterPos.first + 1][y2] != '.') && (map[currWaterPos.first + 1][y1] != '.'))
			{
				for (int c = y1; c <= y2; c++)
				{
					if (map[currWaterPos.first + 1][c] == '|')
					{
						return;
					}
				}

				for (int c = y1; c <= y2; c++)
				{
					map[currWaterPos.first][c] = '~';
				}

				return;
			}

			if (y1 != currWaterPos.second)
			{
				for (int c = y1; c < currWaterPos.second; c++)
				{
					map[currWaterPos.first][c] = '|';
				}

				if (map[currWaterPos.first + 1][y1] == '.')
				{
					solveProblem(std::pair<int, int>(currWaterPos.first, y1), map, maxX, maxY);
				}
			}

			if (y2 != currWaterPos.second)
			{
				for (int c = currWaterPos.second + 1; c <= y2; c++)
				{
					map[currWaterPos.first][c] = '|';
				}

				if (map[currWaterPos.first + 1][y2] == '.')
				{
					solveProblem(std::pair<int, int>(currWaterPos.first, y2), map, maxX, maxY);
				}
			}
		}
	}
}

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<std::vector<char>> map(2000, std::vector<char>(2000, '.'));
	int maxX = 0, maxY = 0;
	int minX = 2000;

	readInput(in, map, maxX, maxY, minX);
	solveProblem(std::pair<int, int>(0, 500), map, maxX, maxY);

	int num = 0;

	for (int l = minX; l <= 1999; l++)
	{
		for (int c = 0; c <= 1999; c++)
		{
			if (map[l][c] == '~')
			{
				num++;
			}
		}
	}

	out << num;

	in.close();
	out.close();
}