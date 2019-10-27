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


void writeOutput(circularList* parse, int length, std::fstream& out)
{
	if (length > 0)
	{
		writeOutput(parse->prev, length - 1, out);
		out << parse->data;
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	const int firstRecipeScore = 3;
	const int secondRecipeScore = 7;
	int inputLength = 0;
	in >> inputLength;
	inputLength += 10;

	circularList* last = new circularList(firstRecipeScore);
	last->addNode(secondRecipeScore);
	last = last->next;

	circularList* firstElf = last->prev;
	circularList* secondElf = last;
	int listLength = 2;
	int sum = 0;
	int min = 0, max = 0;

	while (listLength <= inputLength)
	{
		sum = firstElf->data + secondElf->data % 10;

		if (sum > 9)
		{
			last->addNode(1);
			last = last->next;
			listLength++;
		}
		last->addNode(sum % 10);
		last = last->next;
		listLength++;

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

	if (listLength != inputLength)
	{
		last = last->prev;
		last->next->deleteNode();
	}

	writeOutput(last, 10, out);
	in.close();
	out.close();
}
