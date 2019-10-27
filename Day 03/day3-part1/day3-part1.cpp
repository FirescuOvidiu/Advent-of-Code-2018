#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<std::vector<int>> matrix(1000, std::vector<int>(1000, 0));
	int id = 0, line = 0, column = 0, nLines = 0, nColumns = 0;
	int countSquareInches = 0;
	char c{};

	while (in >> c >> id >> c >> column >> c >> line >> c >> nColumns >> c >> nLines)
	{
		for (int l = line; l < nLines + line; l++)
		{
			for (int c = column; c < nColumns + column; c++)
			{
				if (matrix[l][c] != -1)
				{
					matrix[l][c]++;
				}

				if (matrix[l][c] == 2)
				{
					matrix[l][c] = -1;
					countSquareInches++;
				}
			}
		}
	}

	out << countSquareInches;

	in.close();
	out.close();
}