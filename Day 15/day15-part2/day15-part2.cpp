#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>


const int maxPath = 2147483647;


class Coordinates
{
public:
	Coordinates(int _x, int _y) : x(_x), y(_y) {}

	friend bool operator<(Coordinates c1, Coordinates c2)
	{
		return c1.x < c2.x ? true : c1.x == c2.x ? c1.y < c2.y : false;
	}

public:
	int x;
	int y;
};


class Monster : public Coordinates
{
public:
	Monster(int _x, int _y) : Coordinates(_x, _y), hitPoints(200), attackPower(3) {}

	static bool sortingRule(const Monster& m1, const Monster& m2)
	{
		return m1.x < m2.x ? true : m1.x == m2.x ? m1.y < m2.y : false;
	}

public:
	int hitPoints;
	int attackPower;
};


class path
{
public:
	path(int _length = maxPath, char _startDirection = 'S') : length(_length), startDirection(_startDirection) {}

public:
	int length;
	char startDirection;
};


void initializateMinPath(const Coordinates curr, std::vector<std::vector<path>>& minPath)
{
	minPath[curr.x][curr.y].length = 0;
	minPath[curr.x][curr.y].startDirection = 'S';

	minPath[curr.x - 1][curr.y].length = 1;
	minPath[curr.x - 1][curr.y].startDirection = 'U';

	minPath[curr.x][curr.y - 1].length = 1;
	minPath[curr.x][curr.y - 1].startDirection = 'L';

	minPath[curr.x][curr.y + 1].length = 1;
	minPath[curr.x][curr.y + 1].startDirection = 'R';

	minPath[curr.x + 1][curr.y].length = 1;
	minPath[curr.x + 1][curr.y].startDirection = 'D';
}


void calculatePositions(Coordinates curr, const std::vector<std::vector<char>>& map, std::vector<std::vector<path>>& minPath)
{
	const std::vector<int> dx{ -1, 0, 0, 1 };
	const std::vector<int> dy{ 0, -1, 1, 0 };
	std::queue<Coordinates> queue;

	initializateMinPath(curr, minPath);

	for (int it = 0; it < 4; it++)
	{
		if ((map[curr.x + dx[it]][curr.y + dy[it]] != '#') &&
			(map[curr.x][curr.y] != map[curr.x + dx[it]][curr.y + dy[it]]))
		{
			queue.push(Coordinates(curr.x + dx[it], curr.y + dy[it]));
		}
	}

	while (!queue.empty())
	{
		curr = queue.front();
		queue.pop();

		for (int it = 0; it < 4; it++)
		{
			if (minPath[curr.x + dx[it]][curr.y + dy[it]].length == maxPath)
			{
				minPath[curr.x + dx[it]][curr.y + dy[it]] = path(minPath[curr.x][curr.y].length + 1, minPath[curr.x][curr.y].startDirection);

				if (map[curr.x + dx[it]][curr.y + dy[it]] == '.')
				{
					queue.push(Coordinates(curr.x + dx[it], curr.y + dy[it]));
				}
			}
		}
	}
}


char findNextPosition(const std::vector<std::vector<path>>& minPath, const std::vector<Monster>& monster)
{
	int minLength = maxPath;
	char startDirection = 'S';

	for (std::vector<Monster>::const_iterator it = monster.begin(); it != monster.end(); it++)
	{
		if ((minPath[(*it).x][(*it).y].length < minLength) && (*it).hitPoints > 0)
		{
			minLength = minPath[(*it).x][(*it).y].length;
			startDirection = minPath[(*it).x][(*it).y].startDirection;
		}
	}

	return startDirection;
}


void moveNextPosition(std::vector<std::vector<char>>& map, Monster& m, const char nextPosition, const char monster)
{
	if (nextPosition != 'S')
	{
		map[m.x][m.y] = '.';

		if (nextPosition == 'U') m.x--;
		else if (nextPosition == 'L') m.y--;
		else if (nextPosition == 'R') m.y++;
		else if (nextPosition == 'D') m.x++;

		map[m.x][m.y] = monster;
	}
}



bool checkFinish(std::vector<Monster>& elves, std::vector<Monster>& goblins, std::vector<Monster>::iterator itGoblins)
{
	const std::vector<int> dx{ -1, 0, 0, 1 };
	const std::vector<int> dy{ 0, -1, 1, 0 };

	for (std::vector<Monster>::iterator it = elves.begin(); it != elves.end(); it++)
	{
		if ((*it).hitPoints > 0)
		{
			return false;
			break;
		}
	}

	return itGoblins != goblins.end();
}


bool checkMove(const std::vector<Monster>::iterator& curr, std::vector<std::vector<char>>& map, std::vector<Monster>& monsters, const char monsterType)
{
	if ((*curr).hitPoints <= 0)
	{
		return false;
	}

	const std::vector<int> dx{ -1, 0, 0, 1 };
	const std::vector<int> dy{ 0, -1, 1, 0 };

	std::vector<Monster>::iterator itMonsterMin = monsters.end();

	for (int it = 0; it < 4; it++)
	{
		if (map[(*curr).x + dx[it]][(*curr).y + dy[it]] == monsterType)
		{
			for (std::vector<Monster>::iterator itMonsters = monsters.begin(); itMonsters != monsters.end(); itMonsters++)
			{
				if (((*curr).x + dx[it] == (*itMonsters).x) && ((*curr).y + dy[it] == (*itMonsters).y))
				{
					if (itMonsterMin == monsters.end())
					{
						itMonsterMin = itMonsters;
					}
					else
					{
						if ((*itMonsterMin).hitPoints > (*itMonsters).hitPoints)
						{
							itMonsterMin = itMonsters;
						}
					}
				}
			}
		}
	}

	if (itMonsterMin == monsters.end())
	{
		return true;
	}
	else
	{
		(*itMonsterMin).hitPoints -= (*curr).attackPower;

		if ((*itMonsterMin).hitPoints <= 0)
		{
			map[(*itMonsterMin).x][(*itMonsterMin).y] = '.';
		}

		return false;
	}
}


void deleteMonsters(std::vector <Monster>& m)
{
	std::vector < Monster>::iterator itMonster = m.begin();

	while (itMonster != m.end())
	{
		if ((*itMonster).hitPoints <= 0)
		{
			itMonster = m.erase(itMonster);
		}
		else
		{
			itMonster++;
		}
	}
}

void readInput(std::vector<std::vector<char>>& map, std::vector<Monster>& elves, std::vector<Monster>& goblins, int& l, int& c, std::fstream& in)
{
	std::string line;

	while (std::getline(in, line))
	{
		std::vector<char> column(line.length());
		c = 0;

		for (std::string::iterator it = line.begin(); it != line.end(); it++)
		{
			switch (*it)
			{
			case 'E':
				elves.push_back(Monster(l, c));
				break;
			case 'G':
				goblins.push_back(Monster(l, c));
				break;
			}
			column[c++] = *it;
		}
		map.push_back(column);
		l++;
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<std::vector<char>> map;
	std::vector<Monster> elves;
	std::vector<Monster> goblins;
	int l = 0, c = 0;
	int rounds = 0;

	readInput(map, elves, goblins, l, c, in);

	std::vector<std::vector<char>> auxMap;
	std::vector<Monster> auxElves;
	std::vector<Monster> auxGoblins;

	do {
		for (std::vector<Monster>::iterator it = elves.begin(); it != elves.end(); it++)
		{
			(*it).attackPower += 1;
		}

		auxMap = map;
		auxElves = elves;
		auxGoblins = goblins;
		rounds = 0;

		while ((!auxElves.empty()) && (!auxGoblins.empty()))
		{
			std::vector<Monster>::iterator itElves = auxElves.begin();
			std::vector<Monster>::iterator itGoblins = auxGoblins.begin();

			while ((itElves != auxElves.end()) || (itGoblins != auxGoblins.end()))
			{
				std::vector<std::vector<path>> minPath(l, std::vector<path>(c));

				if ((itElves != auxElves.end()) && ((itGoblins == auxGoblins.end()) || (*itElves < *itGoblins)))
				{
					if (checkMove(itElves, auxMap, auxGoblins, 'G'))
					{
						calculatePositions(*itElves, auxMap, minPath);
						moveNextPosition(auxMap, *itElves, findNextPosition(minPath, auxGoblins), 'E');
						checkMove(itElves, auxMap, auxGoblins, 'G');
					}
					itElves++;
				}
				else
				{
					if (checkMove(itGoblins, auxMap, auxElves, 'E'))
					{
						calculatePositions(*itGoblins, auxMap, minPath);
						moveNextPosition(auxMap, *itGoblins, findNextPosition(minPath, auxElves), 'G');
						checkMove(itGoblins, auxMap, auxElves, 'E');
					}
					itGoblins++;
				}
				if ((checkFinish(auxElves, auxGoblins, itGoblins)) || (checkFinish(auxGoblins, auxElves, itElves)))
				{
					rounds--;
					break;
				}
			}

			deleteMonsters(auxElves);
			deleteMonsters(auxGoblins);

			std::sort(auxElves.begin(), auxElves.end(), Monster::sortingRule);
			std::sort(auxGoblins.begin(), auxGoblins.end(), Monster::sortingRule);

			rounds++;
		}
	} while (auxElves.size() != elves.size());

	int sum = 0;
	
	for (std::vector<Monster>::iterator it = auxElves.begin(); it != auxElves.end(); it++)
	{
		sum += (*it).hitPoints;
	}

	out << rounds * sum;

	in.close();
	out.close();
}