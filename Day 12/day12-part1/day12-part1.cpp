#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::string plants;
	std::vector<std::pair<std::string, std::string>> notes;
	std::string note;
	std::string output;

	in >> plants >> plants >> plants;
	plants.insert(0, "..............................");
	plants.insert(plants.length(), "..............................");

	while (in >> note >> output >> output)
	{
		notes.push_back(std::pair<std::string, std::string> (note, output));
	}


	int countGenerations = 0;
	std::string copyPlants;
	std::size_t pos = -1;
	int sum = 0;

	while (countGenerations < 21)
	{
		copyPlants.erase();
		sum = 0;
		for (int it = 0; it < plants.length(); it++)
		{
			copyPlants += '.';
			if (plants[it] == '#')
			{
				sum = sum + it - 30;
			}
		}

		std::cout << plants << "  " << sum << "\n";

		for (std::vector<std::pair<std::string, std::string>>::iterator it = notes.begin(); it != notes.end(); ++it)
		{
			pos = -1;
			while ((pos = plants.find((*it).first, pos + 1)) != std::string::npos)
			{
				copyPlants.replace(pos+2, 1, (*it).second);
			}
		}

		plants = copyPlants;
		countGenerations++;
	}

	out << sum;
	in.close();
	out.close();
}