#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::fstream firstIn("input.in", std::fstream::in);
	std::fstream secondIn("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::string firstBoxID;
	std::string secondBoxID;
	int indexSecondIn = 0;
	int numWrongLetters = 0;

	while (firstIn >> firstBoxID)
	{
		while (secondIn >> secondBoxID)
		{
			numWrongLetters = 0;

			for (int index = 0; index < (int)firstBoxID.length(); index++)
			{
				if (firstBoxID[index] != secondBoxID[index])
				{
					numWrongLetters++;
				}

				if (numWrongLetters > 1)
				{
					break;
				}
			}

			if (numWrongLetters == 1)
			{
				for (int index = 0; index < (int)firstBoxID.length(); index++)
				{
					if (firstBoxID[index] != secondBoxID[index])
					{
						firstBoxID.erase(firstBoxID.begin() + index);
						break;
					}
				}

				out << firstBoxID;
				firstIn.seekg(0, secondIn.end);
				break;
			}
		}

		indexSecondIn++;
		secondIn.clear();
		secondIn.seekg(secondIn.beg + indexSecondIn * firstBoxID.length());
	}
	
	firstIn.close();
	secondIn.close();
	out.close();
}
