#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void readInput(std::fstream& in, int& depth, int& lines, int& columns)
{
	std::string aux;
	char aux2;
	in >> aux >> depth >> aux >> columns >> aux2 >> lines;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	int lines = 0, columns = 0;
	int depth = 0;
	int riskLevel = 0;

	readInput(in, depth, lines, columns);

	std::vector<std::vector<int>> map(lines + 1, std::vector<int>(columns + 1));

	for (int l = 0; l <= lines; l++)
	{
		for (int c = 0; c <= columns; c++)
		{
			if (((l != 0) && (c != 0)) && (l != lines || (c != columns)))
			{
				map[l][c] = (map[l - 1][c] * map[l][c - 1] + depth) % 20183;
			}
			else
			{
				if (c == 0)
				{
					map[l][c] = (l * 48271 + depth) % 20183;
				}
				else
				{
					if (l == 0)
					{
						map[l][c] = (c * 16807 + depth) % 20183;
					}
					else 
					{
						map[l][c] = depth % 20183;
					}
				}
			}
			riskLevel += map[l][c] % 3;
		}
	}

	out << riskLevel;

	in.close();
	out.close();
}