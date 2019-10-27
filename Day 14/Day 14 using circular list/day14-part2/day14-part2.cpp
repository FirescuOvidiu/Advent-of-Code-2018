#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class circularList
{
public:
	circularList(int _data = 0) : data(_data), next(this), prev(this) {}
	circularList(int _data, circularList* _next, circularList* _prev) : data(_data), next(_next), prev(_prev) {}

	void addNode(int data)
	{
		circularList* newNode = new circularList(data, this->next, this);

		this->next->prev = newNode;
		this->next = newNode;
	}

	void deleteNode()
	{
		this->prev->next = this->next;
		this->next->prev = this->prev;

		delete this;
	}

public:
	int data;
	circularList* next;
	circularList* prev;
};


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


#include <time.h>

int main()
{
	clock_t tStart = clock();
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	const int firstRecipeScore = 3;
	const int secondRecipeScore = 7;
	std::string substring;
	in >> substring;

	// Auxiliar vector needed for the KMP algorithm
	std::vector<int> arr(substring.length());
	computeArray(substring, arr);

	// Creating the circular list
	circularList* last = new circularList(firstRecipeScore);
	last->addNode(secondRecipeScore);
	last = last->next;

	circularList* firstElf = last->prev;
	circularList* secondElf = last;
	int listLength = 2;
	int sum = 0;
	int min = 0, max = 0;

	int index = 0;

	int i = 0;

	while (true)
	{
		if (i == 100000000)
		{
			break;
		}
		i++;

		// Calculating the sum, adding the sum to the end of the list and checking if a matching was found
		sum = firstElf->data + secondElf->data % 10;

		if (sum > 9)
		{
			last->addNode(1);
			last = last->next;
			listLength++;

			if (KMP(substring, index, arr, 1) == true)
			{
				break;
			}
		}
		last->addNode(sum % 10);
		last = last->next;
		listLength++;

		if (KMP(substring, index, arr, sum % 10) == true)
		{
			break;
		}

		// Calculating the new positions for the first elf and second elf
		if (firstElf->data < secondElf->data)
		{
			min = firstElf->data;
			max = secondElf->data;

			for (int i = 0; i < max - min; i++)
			{
				secondElf = secondElf->next;
			}
		}
		else
		{
			min = secondElf->data;
			max = firstElf->data;

			for (int i = 0; i < max - min; i++)
			{
				firstElf = firstElf->next;
			}
		}

		for (int i = 0; i <= min; i++)
		{
			firstElf = firstElf->next;
			secondElf = secondElf->next;
		}
	}

	out << listLength - substring.length();
	in.close();
	out.close();
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}