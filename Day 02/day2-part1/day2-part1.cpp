#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	
	std::vector<int> countLetters(26, 0);
	std::string boxID;
	int countTwo = 0, countThree = 0;
	bool checkCountTwo = false, checkCountThree = false;

	while (in >> boxID)
	{
		for (int index = 0; index < boxID.length(); index++)
		{
			countLetters[(int)(boxID[index]-'a')]++;
		}

		checkCountTwo = false;
		checkCountThree = false;

		for (int i = 0; i <= 25; i++)
		{
			if ((countLetters[i] == 2) && (!checkCountTwo))
			{
				countTwo++;
				checkCountTwo = true;
			}
			
			if ((countLetters[i] == 3) && (!checkCountThree))
			{
				countThree++;
				checkCountThree=true;
			}
			
			countLetters[i] = 0;
		}
	}

	out << countTwo * countThree;
	
	in.close();
	out.close();
}
