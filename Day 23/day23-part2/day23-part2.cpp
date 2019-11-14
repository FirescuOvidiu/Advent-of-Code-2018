#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0, int z = 0, int r = 0) : x(x), y(y), z(z), r(r) {}

	static int calculateDist(const Coordinate& c1, const Coordinate& c2)
	{
		return abs(c1.x - c2.x) + abs(c1.y - c2.y) + abs(c1.z - c2.z);
	}

	bool operator==(const Coordinate& c)
	{
		return ((this->x == c.x) && (this->y == c.y) && (this->z == c.z));
	}
public:
	int x, y, z;
	int r;
};


class Box
{
public:
	Box(Coordinate min, Coordinate max, int nanobots = 0) : min(min), max(max), nanobots(nanobots) {}
public:
	Coordinate min, max;
	int nanobots;
};


void readInput(std::fstream& in, std::vector<Coordinate>& nanoBots, Coordinate& min, Coordinate& max)
{
	Coordinate aux;
	char aux2;

	while (in >> aux2 >> aux2 >> aux2 >> aux2 >> aux2 >> aux.x >> aux2 >> aux.y >> aux2 >> aux.z >> aux2 >> aux2 >> aux2 >> aux2 >> aux.r)
	{
		nanoBots.push_back(aux);
		if (aux.x > max.x) max.x = aux.x;  if (aux.y > max.y) max.y = aux.y;  if (aux.z > max.z) max.z = aux.z;
		if (aux.x < min.x) min.x = aux.x;  if (aux.y < min.y) min.y = aux.y;  if (aux.z < min.z) min.z = aux.z;
	}
}


std::vector<Box> Split(Coordinate min, Coordinate max)
{
	return std::vector<Box>
	{
		Box(min, Coordinate(min.x + (max.x - min.x) / 2, min.y + (max.y - min.y) / 2, min.z + (max.z - min.z) / 2)),
			Box(Coordinate(min.x + (max.x - min.x) / 2, min.y, min.z), Coordinate(max.x, min.y + (max.y - min.y) / 2, min.z + (max.z - min.z) / 2)),
			Box(Coordinate(min.x, min.y + (max.y - min.y) / 2, min.z), Coordinate(min.x + (max.x - min.x) / 2, max.y, min.z + (max.z - min.z) / 2)),
			Box(Coordinate(min.x + (max.x - min.x) / 2, min.y + (max.y - min.y) / 2, min.z), Coordinate(max.x, max.y, min.z + (max.z - min.z) / 2)),
			Box(Coordinate(min.x, min.y, min.z + (max.z - min.z) / 2), Coordinate(min.x + (max.x - min.x) / 2, min.y + (max.y - min.y) / 2, max.z)),
			Box(Coordinate(min.x + (max.x - min.x) / 2, min.y, min.z + (max.z - min.z) / 2), Coordinate(max.x, min.y + (max.y - min.y) / 2, max.z)),
			Box(Coordinate(min.x, min.y + (max.y - min.y) / 2, min.z + (max.z - min.z) / 2), Coordinate(min.x + (max.x - min.x) / 2, max.y, max.z)),
			Box(Coordinate(min.x + (max.x - min.x) / 2, min.y + (max.y - min.y) / 2, min.z + (max.z - min.z) / 2), max)
	};
}


bool checkNanobotInBox(const Box& currBox, const Coordinate& currNanobot)
{
	Coordinate nearestPoint;

	nearestPoint.x = currNanobot.x > currBox.max.x ? currBox.max.x : currNanobot.x < currBox.min.x ? currBox.min.x : currNanobot.x;
	nearestPoint.y = currNanobot.y > currBox.max.y ? currBox.max.y : currNanobot.y < currBox.min.y ? currBox.min.y : currNanobot.y;
	nearestPoint.z = currNanobot.z > currBox.max.z ? currBox.max.z : currNanobot.z < currBox.min.z ? currBox.min.z : currNanobot.z;

	if (Coordinate::calculateDist(nearestPoint, currNanobot) <= currNanobot.r)
	{
		return true;
	}

	return false;
}

void calculateNumberOfNanobotsInBox(const std::vector<Coordinate>& nanoBots, const Coordinate min, const Coordinate max, Coordinate& coordSearched)
{
	std::vector<Box> boxes = Split(min, max);
	int maxNanobots = 0;

	if ((max.x - min.x) + (max.y - min.y) + (max.z - min.z) < 50)
	{
		for (int i = min.x; i <= max.x; i++)
		{
			for (int j = min.y; j <= max.y; j++)
			{
				for (int k = min.z; k <= max.z; k++)
				{
					maxNanobots = 0;

					for (std::vector<Coordinate>::const_iterator currNanoBot = nanoBots.cbegin(); currNanoBot != nanoBots.cend(); currNanoBot++)
					{
						if (Coordinate::calculateDist(Coordinate(i,j,k), *currNanoBot) <= (*currNanoBot).r)
						{
							maxNanobots++;
						}
					}

					if (coordSearched.r < maxNanobots)
					{
						coordSearched.r = maxNanobots;
						coordSearched.x = i;
						coordSearched.y = j;
						coordSearched.z = k;

						std::cout << Coordinate::calculateDist(coordSearched, Coordinate(0, 0, 0)) << "\n";
					}
				}
			}
		}
		return;
	}


	for (std::vector<Box>::iterator currBox = boxes.begin(); currBox != boxes.end(); currBox++)
	{
		for (std::vector<Coordinate>::const_iterator currNanoBot = nanoBots.cbegin(); currNanoBot != nanoBots.cend(); currNanoBot++)
		{
			if (checkNanobotInBox(*currBox, *currNanoBot))
			{
				currBox->nanobots++;
			}
		}
	}

	maxNanobots = 0;

	for (std::vector<Box>::iterator currBox = boxes.begin(); currBox != boxes.end(); currBox++)
	{
		if (currBox->nanobots > maxNanobots)
		{
			maxNanobots = currBox->nanobots;
		}
	}

	if (maxNanobots > coordSearched.r)
	{
		for (std::vector<Box>::iterator currBox = boxes.begin(); currBox != boxes.end(); currBox++)
		{
			if (currBox->nanobots == maxNanobots)
			{
				calculateNumberOfNanobotsInBox(nanoBots, currBox->min, currBox->max, coordSearched);
			}
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<Coordinate> nanoBots;
	Coordinate max(-2147483647, -2147483647, -2147483647), min(2147483647, 2147483647, 2147483647);
	Coordinate coordSearched;
	readInput(in, nanoBots, min, max);

	calculateNumberOfNanobotsInBox(nanoBots, min, max, coordSearched);

	out << Coordinate::calculateDist(coordSearched, Coordinate(0, 0, 0));

	in.close();
	out.close();
}