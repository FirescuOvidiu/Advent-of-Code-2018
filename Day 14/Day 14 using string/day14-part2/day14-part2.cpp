#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void computeArray(const std::string& substring, std::vector<int>& arr)
{
	int i = 0;
	int j = 1;

	while (j < substring.length())
	{
		if (substring[i] == substring[j])
		{
			i++;
			arr[j] = i;
			j++;
		}
		else
		{
			if (i != 0)
			{
				i = arr[i - 1];
			}
			else
			{
				arr[j] = 0;
				j++;
			}
		}
	}
}


bool KMP(const std::string& recipeScores, int& index, const std::vector<int>& arr, int score)
{
	if (recipeScores[index] - '0' == score)
	{
		index++;
		if (index == recipeScores.length())
		{
			return true;
		}
	}
	else
	{
		while (index != 0)
		{
			index = arr[index - 1];

			if (recipeScores[index] - '0' == score)
			{
				index++;
				return false;
			}
		}
	}

	return false;
}


void findRecipeScores(std::string& scores, const std::string& recipesScores)
{
	int firstElf = 0;
	int secondElf = 1;
	int sum = 0;
	int index = 0;

	std::vector<int> arr(recipesScores.length());
	computeArray(recipesScores, arr);

	while (true)
	{
		// Calculating the sum, adding the sum to the end of the string and checking if a matching was found
		sum = (scores[firstElf] - '0') + (scores[secondElf] - '0');
		/*if (sum > 9)
		{
			scores += sum / 10 + '0';
		}
		scores += sum % 10 + '0';*/
		scores += std::to_string(sum);

		if (sum > 9)
		{
			if (KMP(recipesScores, index, arr, 1) == true)
			{
				// We added 2 digits to the string and a match was found after the first digit so we delete the remaining digit
				scores.erase(scores.end() - 1);
				break;
			}
		}

		if (KMP(recipesScores, index, arr, sum % 10) == true)
		{
			break;
		}

		// Calculating the new positions for the first elf and second elf
		firstElf = (firstElf + (scores[firstElf] - '0') + 1) % scores.length();
		secondElf = (secondElf + (scores[secondElf] - '0') + 1) % scores.length();
	}
}


#include <time.h>

int main()
{
	clock_t tStart = clock();
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::string scores("37");
	std::string recipesScores;
	in >> recipesScores;

	findRecipeScores(scores, recipesScores);

	out << scores.length() - recipesScores.length();

	in.close();
	out.close();
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}