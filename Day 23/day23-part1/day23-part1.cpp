#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0, int z = 0, int r = 0) : x(x), y(y), z(z), r(r) {}

	static int calculateDist(const Coordinate& c1, const Coordinate& c2)
	{
		return abs(c1.x - c2.x) + abs(c1.y - c2.y) + abs(c1.z - c2.z);
	}

public:
	int x, y, z;
	int r;
};



void readInput(std::fstream& in,std::vector<Coordinate>& nanoBots, Coordinate& strongestNanobot)
{
	Coordinate aux;
	char aux2;
	while (in >> aux2 >> aux2 >> aux2 >> aux2 >> aux2 >> aux.x >> aux2 >> aux.y >> aux2 >> aux.z >> aux2 >> aux2 >> aux2 >> aux2 >> aux.r)
	{
		nanoBots.push_back(aux);
		if (aux.r > strongestNanobot.r)
		{
			strongestNanobot = aux;
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<Coordinate> nanoBots;
	Coordinate strongestNanobot;
	int totalNumber = 0;

	readInput(in, nanoBots, strongestNanobot);

	for (std::vector<Coordinate>::const_iterator it = nanoBots.cbegin(); it != nanoBots.cend(); it++)
	{
		if (Coordinate::calculateDist(*it, strongestNanobot) <= strongestNanobot.r)
		{
			totalNumber++;
		}
	}

	out << totalNumber;

	in.close();
	out.close();
}
