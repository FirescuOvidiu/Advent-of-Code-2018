#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>


class constellation
{
public:
	constellation(int x = 0, int y = 0, int z = 0, int w = 0) : x(x), y(y), z(z), w(w), number(0) {}

	static int manhattanDistance(const constellation& c1, const constellation& c2)
	{
		return abs(c1.x - c2.x) + abs(c1.y - c2.y) + abs(c1.z - c2.z) + abs(c1.w - c2.w);
	}

public:
	int x, y, z, w;
	int number;
	static int indexNumber;
};

int constellation::indexNumber = 1;


void readInput(std::fstream& in, std::vector<constellation>& constellations)
{
	constellation currConst;
	char aux{};

	while (in >> currConst.x >> aux >> currConst.y >> aux >> currConst.z >> aux >> currConst.w)
	{
		constellations.push_back(currConst);
	}
}


void mergeTwoConstellations(std::vector<constellation>& constellations, int c1Number, int c2Number)
{
	for (auto currPoint = constellations.begin(); currPoint != constellations.end(); currPoint++)
	{
		if ((*currPoint).number == c2Number)
		{
			(*currPoint).number = c1Number;
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<constellation> constellations;

	readInput(in, constellations);

	int nrConstallations = 0;

	for (auto currPoint = constellations.begin(); currPoint != constellations.end(); currPoint++)
	{
		for (auto otherPoints = constellations.begin(); otherPoints != constellations.end(); otherPoints++)
		{
			if (((*currPoint).number == (*otherPoints).number) && ((*currPoint).number != 0))
			{
				continue;
			}

			if (constellation::manhattanDistance(*currPoint, *otherPoints) <= 3)
			{
				if (((*currPoint).number == 0) && ((*otherPoints).number == 0))
				{
					(*currPoint).number = constellation::indexNumber;
					(*otherPoints).number = constellation::indexNumber;
					constellation::indexNumber++;
					nrConstallations++;
				}
				else
				{
					if (((*currPoint).number != 0) && ((*otherPoints).number != 0))
					{
						mergeTwoConstellations(constellations, (*currPoint).number, (*otherPoints).number);
						nrConstallations--;
					}
					else
					{
						(*otherPoints).number = (*currPoint).number;
					}
				}
			}
		}
	}

	out << nrConstallations;

	in.close();
	out.close();
}