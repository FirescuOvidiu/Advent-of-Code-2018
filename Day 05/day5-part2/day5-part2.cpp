#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::string units;
	char c{};

	while (in >> c)
	{
		if (empty(units))
		{
			units += c;
		}
		else
		{
			if ((units.back() == c - ('a' - 'A')) || (units.back() == c + ('a' - 'A')))
			{
				units.erase(units.end() - 1);
			}
			else
			{
				units += c;
			}
		}
	}

	std::string polymer(units);
	int length = polymer.length();
	int index = 0;

	for (int l = 0; l < 26; l++)
	{
		index = 0;
		polymer = units;

		while (index < polymer.length())
		{
			if ((polymer[index] == 'A' + l) || (polymer[index] == 'a' + l))
			{
				polymer.erase(polymer.begin() + index);

				while ((index > 0) && ((polymer[index] == polymer[index - 1] - ('a' - 'A')) ||
					(polymer[index] == polymer[index - 1] + ('a' - 'A'))))
				{
					polymer.erase(polymer.begin() + index - 1, polymer.begin() + index + 1);
					index--;
				}
			}
			else
			{
				index++;
			}
		}

		if (length > polymer.length())
		{
			length = polymer.length();
		}
	}

	out << length;

	in.close();
	out.close();
}