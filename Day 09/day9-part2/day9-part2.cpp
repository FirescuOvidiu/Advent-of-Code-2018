#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class circularList
{
public:
	circularList() : data(0), next(this), prev(this) {}
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


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	circularList* root = new circularList;
	std::string aux;
	int players = 0;
	int marbles = 0;
	in >> players >> aux >> aux >> aux >> aux >> aux >> marbles;

	std::vector<unsigned int> score(players + 1, 0);

	unsigned int max = 0;
	int currPlayer = 1;

	for (int currMarble = 1; currMarble <= marbles; currMarble++)
	{
		if (currMarble % 23 != 0)
		{
			root->addNode(currMarble);
			root = root->next->next;
		}
		else
		{
			for (int it = 1; it < 7; it++)
			{
				root = root->prev;
			}

			score[currPlayer] += currMarble;
			score[currPlayer] += root->prev->prev->data;
			root->prev->prev->deleteNode();

			if (score[currPlayer] > max)
			{
				max = score[currPlayer];
			}
		}
		currPlayer = currPlayer % players + 1;
	}

	out << max;
	in.close();
	out.close();
}
