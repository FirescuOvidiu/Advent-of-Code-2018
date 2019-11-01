#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>


class Coordinate
{
public:
	Coordinate(int _x, int _y) :x(_x), y(_y) {}
public:
	int x, y;
};


void calculateDistances(Coordinate curr, const std::vector<std::vector<char>>& map, std::vector<std::vector<int>>& minPath)
{
	const std::vector<int> dx{ -2, 0, 0, 2 };
	const std::vector<int> dy{ 0, -2, 2, 0 };

	const std::vector<int> auxDx{ 1, 0, 0, -1 };
	const std::vector<int> auxDy{ 0, 1, -1, 0 };

	std::queue<Coordinate> queue;

	queue.push(curr);

	while (!queue.empty())
	{
		curr = queue.front();
		queue.pop();

		for (int it = 0; it < 4; it++)
		{
			if ((minPath[curr.x + dx[it]][curr.y + dy[it]] == 0) &&
				(map[curr.x + dx[it]][curr.y + dy[it]] == '.') &&
				(map[curr.x + dx[it] + auxDx[it]][curr.y + dy[it] + auxDy[it]] == '|' ||
					map[curr.x + dx[it] + auxDx[it]][curr.y + dy[it] + auxDy[it]] == '-'))
			{
				minPath[curr.x + dx[it]][curr.y + dy[it]] = minPath[curr.x][curr.y] + 1;
				queue.push(Coordinate(curr.x + dx[it], curr.y + dy[it]));
			}
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<char>> map(2000, std::vector<char>(2000, '#'));
	std::vector<std::vector<int>> minPath(2000, std::vector<int>(2000));
	std::stack<Coordinate> positions;
	Coordinate start(1000, 1000), currPosition(1000, 1000);
	std::string regExpr;

	in >> regExpr;
	positions.push(start);
	map[start.x][start.y] = 'X';

	for (const auto step : regExpr)
	{
		switch (step)
		{
		case 'N':
			currPosition.x -= 2;
			map[currPosition.x + 1][currPosition.y] = '-';
			map[currPosition.x][currPosition.y] = '.';
			break;
		case 'W':
			currPosition.y -= 2;
			map[currPosition.x][currPosition.y + 1] = '|';
			map[currPosition.x][currPosition.y] = '.';
			break;
		case 'E':
			currPosition.y += 2;
			map[currPosition.x][currPosition.y - 1] = '|';
			map[currPosition.x][currPosition.y] = '.';
			break;
		case 'S':
			currPosition.x += 2;
			map[currPosition.x - 1][currPosition.y] = '-';
			map[currPosition.x][currPosition.y] = '.';
			break;
		case '(':
			positions.push(currPosition);
			break;
		case ')':
			positions.pop();
			break;
		case '|':
			currPosition = positions.top();
			break;
		}
	}

	calculateDistances(start, map, minPath);

	int count = 0;

	for (int x = 0; x < 2000; x++)
	{
		for (int y = 0; y < 2000; y++)
		{
			if (minPath[x][y] >= 1000)
			{
				count++;
			}
			//out << map[x][y] << " ";
		}
		//out << "\n";
	}

	out << count;

	in.close();
	out.close();
}