#include <iostream>
#include <fstream>
#include <vector>
#include <string>


void readInput(std::vector<std::vector<char>>& map, int& nLines, int& nColumns, std::fstream& in)
{
	std::string line;

	while (std::getline(in, line))
	{
		nColumns = 1;
		for (std::string::iterator it = line.begin(); it != line.end(); it++)
		{
			map[nLines][nColumns++] = *it;
		}
		nLines++;
	}

	map.resize(nLines + 1);
	for (auto it = map.begin(); it != map.end(); it++)
	{
		(*it).resize(nColumns + 1);
	}
}


void changes(std::vector<std::vector<char>>& map, int nLines, int nColumns, const std::vector<int>& dx, const std::vector<int>& dy)
{
	std::vector<std::vector<char>> aux(nLines + 1, std::vector<char>(nColumns + 1));
	int countTrees = 0;
	int countLumberyard = 0;

	for (int l = 1; l < nLines; l++)
	{
		for (int c = 1; c < nColumns; c++)
		{
			countTrees = 0;
			countLumberyard = 0;

			for (int i = 0; i < 8; i++)
			{
				if (map[l + dx[i]][c + dy[i]] == '|') countTrees++;
				if (map[l + dx[i]][c + dy[i]] == '#') countLumberyard++;
			}

			switch (map[l][c])
			{
			case '.':
				aux[l][c] = countTrees >= 3 ? '|' : '.';
				break;

			case '|':
				aux[l][c] = countLumberyard >= 3 ? '#' : '|';
				break;

			case '#':
				aux[l][c] = ((countTrees == 0) || (countLumberyard == 0)) ? '.' : '#';
				break;
			}
		}
	}
	map = aux;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<std::vector<char>> map(60, std::vector<char>(60));
	const std::vector<int>dx{ -1,-1,-1,0,0,1,1,1 };
	const std::vector<int>dy{ -1,0,1,-1,1,-1,0,1 };
	int nLines = 1, nColumns = 1;

	readInput(map, nLines, nColumns, in);

	for (int index = 1; index <= 10; index++)
	{
		changes(map, nLines, nColumns,dx,dy);
	}

	int countTrees = 0;
	int countLumberyard = 0;

	for (int l = 1; l < nLines; l++)
	{
		for (int c = 1; c < nColumns; c++)
		{
			if (map[l][c] == '|') countTrees++;
			if (map[l][c] == '#') countLumberyard++;
		}
	}

	out << countTrees * countLumberyard;

	in.close();
	out.close();
}