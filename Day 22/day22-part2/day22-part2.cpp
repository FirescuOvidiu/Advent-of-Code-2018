#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <tuple>


enum ToolType
{
	neither = 0,
	torch = 1,
	climbing = 2,
};



class Coordinates
{
public:
	Coordinates(int x = 0, int y = 0, ToolType tool = torch) : x(x), y(y), tool(tool) {}

	friend bool operator==(const Coordinates& c1, const Coordinates& c2)
	{
		return (c1.x == c2.x && c1.y == c2.y);
	}

public:
	int x, y;
	ToolType tool;
};


class Compare
{
public:
	bool operator() (const std::pair<Coordinates, int>& c1, const std::pair<Coordinates, int>& c2) const
	{
		return std::tie(c1.second, c1.first.x, c1.first.y, c1.first.tool) < std::tie(c2.second, c2.first.x, c2.first.y, c2.first.tool);
	}
};


void readInput(std::fstream& in, int& depth, int& lines, int& columns, Coordinates& end)
{
	std::string aux;
	char aux2;
	in >> aux >> depth >> aux >> columns >> aux2 >> lines;

	end.x = lines;
	end.y = columns;

	lines = lines * 3; columns = columns * 3;
	lines > columns ? columns = lines : lines = columns;
}


// Inserting in the set the new coordinates and updating the mapValues
void updateSet(bool currCase, std::vector<std::vector<std::vector<int>>>& mapValues, const Coordinates& nextPosition, ToolType tool,
	int currDistance, std::set< std::pair<Coordinates, int>, Compare>& positions, const Coordinates& currPosition)
{
	if (currCase == true)
	{
		if (mapValues[tool][nextPosition.x][nextPosition.y] >= currDistance + 1)
		{
			mapValues[tool][nextPosition.x][nextPosition.y] = currDistance + 1;
			positions.insert(std::pair<Coordinates, int>(Coordinates(nextPosition.x, nextPosition.y, currPosition.tool), mapValues[tool][nextPosition.x][nextPosition.y]));
		}
	}
	else
	{
		if (mapValues[tool][nextPosition.x][nextPosition.y] >= currDistance + 8)
		{
			mapValues[tool][nextPosition.x][nextPosition.y] = currDistance + 8;
			positions.insert(std::pair<Coordinates, int>(Coordinates(nextPosition.x, nextPosition.y, tool), mapValues[tool][nextPosition.x][nextPosition.y]));
		}
	}
}


void calculateDistances(std::vector<std::vector<std::vector<int>>>& mapValues, const std::vector<std::vector<char>>& map, const Coordinates& start, const Coordinates& end, int lines, int columns)
{
	const std::vector<int> dx{ -1, 0, 0, 1 };
	const std::vector<int> dy{ 0, -1, 1, 0 };

	std::set< std::pair<Coordinates, int>, Compare> positions;
	Coordinates currPosition(0, 0), nextPosition(0, 0);
	int currDistance = 0;

	positions.insert(std::pair<Coordinates, int>(start, 0));

	while (!positions.empty())
	{
		currPosition = (*positions.begin()).first;
		currDistance = (*positions.begin()).second;
		positions.erase(positions.begin());

		if (currDistance >= mapValues[currPosition.tool][end.x][end.y])
		{
			continue;
		}

		// Parse all adjacent location and add to the set the ones that have the currDistance + distance from currPosition to nextPosition < distance of nextPosition
		for (int it = 0; it < 4; it++)
		{
			nextPosition.x = currPosition.x + dx[it];
			nextPosition.y = currPosition.y + dy[it];

			// Check if the next position is the destination
			if (nextPosition == end)
			{
				if (currPosition.tool == torch)
				{
					if (mapValues[currPosition.tool][end.x][end.y] > currDistance + 1)
					{
						mapValues[currPosition.tool][end.x][end.y] = currDistance + 1;
					}
				}
				else
				{
					if (mapValues[currPosition.tool][end.x][end.y] > currDistance + 8)
					{
						mapValues[currPosition.tool][end.x][end.y] = currDistance + 8;
					}
				}
				continue;
			}

			if ((nextPosition.x >= 0) && (nextPosition.y >= 0) && (nextPosition.x < lines) && (nextPosition.y < columns))
			{
				switch (map[nextPosition.x][nextPosition.y])
				{
				// Next position is a rocky area
				case '.':
					// Checking if we have the right tool for next area and updating the set
					if ((currPosition.tool == climbing) || (currPosition.tool == torch))
					{
						updateSet(true, mapValues, nextPosition, currPosition.tool, currDistance, positions, currPosition);
					}
					else
					{
						if (map[currPosition.x][currPosition.y] == '=')
						{
							updateSet(false, mapValues, nextPosition, climbing, currDistance, positions, currPosition);
						}
						else
						{
							updateSet(false, mapValues, nextPosition, torch, currDistance, positions, currPosition);
						}
					}
					break;

				// Next position is a wet area
				case '=':
					// Checking if we have the right tool for next area nad updating the set
					if ((currPosition.tool == climbing) || (currPosition.tool == neither))
					{
						updateSet(true, mapValues, nextPosition, currPosition.tool, currDistance, positions, currPosition);
					}
					else
					{
						if (map[currPosition.x][currPosition.y] == '.')
						{
							updateSet(false, mapValues, nextPosition, climbing, currDistance, positions, currPosition);
						}
						else
						{
							updateSet(false, mapValues, nextPosition, neither, currDistance, positions, currPosition);
						}
					}
					break;

				// Next position is a narrow area
				case'|':
					// Checking if we have the right tool for next area nad updating the set
					if ((currPosition.tool == torch) || (currPosition.tool == neither))
					{
						updateSet(true, mapValues, nextPosition, currPosition.tool, currDistance, positions, currPosition);
					}
					else
					{
						if (map[currPosition.x][currPosition.y] == '=')
						{
							updateSet(false, mapValues, nextPosition, neither, currDistance, positions, currPosition);
						}
						else
						{
							updateSet(false, mapValues, nextPosition, torch, currDistance, positions, currPosition);
						}
					}
					break;
				}
			}
		}
	}
}


void createMap(std::vector<std::vector<std::vector<int>>>& mapValues, std::vector<std::vector<char>>& map,
	const int lines, const int columns, const int depth, const Coordinates& start, const Coordinates& end)
{
	for (int type = 0; type < 3; type++)
	{
		for (int l = 0; l < lines; l++)
		{
			for (int c = 0; c < columns; c++)
			{
				if (((l != start.x) && (c != start.y)) && (l != end.x || (c != end.y)))
				{
					mapValues[type][l][c] = (mapValues[type][l - 1][c] * mapValues[type][l][c - 1] + depth) % 20183;
				}
				else
				{
					if (c == 0)
					{
						mapValues[type][l][c] = (l * 48271 + depth) % 20183;
					}
					else
					{
						if (l == 0)
						{
							mapValues[type][l][c] = (c * 16807 + depth) % 20183;
						}
						else
						{
							mapValues[type][l][c] = depth % 20183;
						}
					}
				}

				switch (mapValues[type][l][c] % 3)
				{
				case 0:
					map[l][c] = '.';
					break;
				case 1:
					map[l][c] = '=';
					break;
				case 2:
					map[l][c] = '|';
					break;
				}
			}
		}
	}
	map[end.x][end.y] = '.';

	const int maxValue = 2047483647;
	for (int type = 0; type < 3; type++)
	{
		for (int l = 0; l < lines; l++)
		{
			for (int c = 0; c < columns; c++)
			{
				mapValues[type][l][c] = maxValue;
			}
		}
		mapValues[type][start.x][start.y] = 0;
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	Coordinates start(0, 0), end(0, 0);
	int lines = 0, columns = 0;
	int depth = 0;

	readInput(in, depth, lines, columns, end);

	std::vector<std::vector<std::vector<int>>> mapValues(3, std::vector<std::vector<int>>(lines, std::vector<int>(columns)));	std::vector<std::vector<char>> map(lines, std::vector<char>(columns));

	createMap(mapValues, map, lines, columns, depth, start, end);
	calculateDistances(mapValues, map, start, end, lines, columns);

	if (mapValues[torch][end.x][end.y] > mapValues[neither][end.x][end.y])
	{
		if (mapValues[torch][end.x][end.y] > mapValues[climbing][end.x][end.y])
		{
			out << mapValues[torch][end.x][end.y];
		}
		else
		{
			out << mapValues[climbing][end.x][end.y];
		}
	}
	else
	{
		if (mapValues[neither][end.x][end.y] < mapValues[climbing][end.x][end.y])
		{
			out << mapValues[neither][end.x][end.y];
		}
		else
		{
			out << mapValues[climbing][end.x][end.y];
		}
	}

	in.close();
	out.close();
}