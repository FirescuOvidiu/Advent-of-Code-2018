#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <math.h>
#include <windows.h>


class point
{
public:
	std::pair<int, int> position;
	std::pair<int, int> velocity;
};


void MoveTo(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<point> points;
	std::string line;

	while (std::getline(in, line))
	{
		point aux;
		sscanf(line.c_str(), "position=<%d, %d> velocity=<%d, %d>", &aux.position.first, &aux.position.second, &aux.velocity.first, &aux.velocity.second);
		points.push_back(aux);
	}

	bool check = true;
	int minX = 100000, minY = 100000;
	int seconds = 0;

	while (true)
	{
		check = true;

		for (std::vector<point>::iterator it = points.begin(); it != points.end(); ++it)
		{
			if (abs(((*(points.begin())).position.first - (*it).position.first) > 100) ||
				(abs((*(points.begin())).position.second - (*it).position.second) > 100))
			{
				check = false;
			}

			(*it).position.first += (*it).velocity.first;
			(*it).position.second += (*it).velocity.second;
		}
		seconds++;

		if (check)
		{
			minX = 100000;
			minY = 100000;

			for (std::vector<point>::iterator it = points.begin(); it != points.end(); ++it)
			{
				if (minX > (*it).position.first)
				{
					minX = (*it).position.first;
				}

				if (minY > (*it).position.second)
				{
					minY = (*it).position.second;
				}
			}

			for (std::vector<point>::iterator it = points.begin(); it != points.end(); ++it)
			{
				MoveTo((*it).position.first - minX, (*it).position.second - minY);
				std::cout << "#";
			}

			Sleep(2000);
			system("cls");
			MoveTo(0, 0);
			std::cout << seconds;
			Sleep(2000);
			system("cls");
		}
	}

	in.close();
	out.close();
}
