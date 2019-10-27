#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<std::vector<int>> matrix(1000, std::vector<int>(1000, 0));
	int id = 0, line = 0, column = 0, nLines = 0, nColumns = 0;
	char c{};

	// Other option for reading the input - sscanf
	while (in >> c >> id >> c >> column >> c >> line >> c >> nColumns >> c >> nLines)
	{
		for (int l = line; l < nLines + line; l++)
		{
			for (int c = column; c < nColumns + column; c++)
			{
				matrix[l][c]++;
			}
		}
	}

	in.clear();
	in.seekg(0, std::ios::beg);

	while (in >> c >> id >> c >> column >> c >> line >> c >> nColumns >> c >> nLines)
	{
		bool check = true;

		for (int l = line; l < nLines + line; l++)
		{
			for (int c = column; c < nColumns + column; c++)
			{
				if (matrix[l][c] > 1)
				{
					check = false;
					break;
				}
			}
		}

		if (check)
		{
			out << id;
			break;
		}
	}

	in.close();
	out.close();
}