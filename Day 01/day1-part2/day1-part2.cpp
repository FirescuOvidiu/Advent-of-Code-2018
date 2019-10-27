#include <iostream>
#include <fstream>
#include <unordered_map>

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	
	std::unordered_map<int, bool> freq;
	int number = 0, sum = 0;
	bool found = false;

	while (!found)
	{
		while (in >> number)
		{
			sum += number;

			if (freq[sum] == true)
			{
				found = true;
				out << sum;
				break;
			}

			freq[sum] = true;
		}

		in.clear();
		in.seekg(0, in.beg);
	}

	in.close();
	out.close();
}
