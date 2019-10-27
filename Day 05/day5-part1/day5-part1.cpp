#include <iostream>
#include <fstream>

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

	out << units.length();

	in.close();
	out.close();
}