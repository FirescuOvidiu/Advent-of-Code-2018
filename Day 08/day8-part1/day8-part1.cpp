#include <iostream>
#include <fstream>
#include <vector>

class node
{
public:
	node() : childNodes(0), numMetadata(0), father(nullptr) {}
public:
	std::vector<int> metadata;
	std::vector<node*> childs;
	int childNodes;
	int numMetadata;
	node* father;
};


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	int metadata = 0, sum = 0;
	node* root = new node;
	node* currFather = root;
	in >> root->childNodes >> root->numMetadata;
	
	while (!in.eof())
	{
		node* newNode = new node;
		in >> newNode->childNodes >> newNode->numMetadata;
		newNode->father = currFather;

		currFather->childs.push_back(newNode);

		while (newNode->childNodes == 0)
		{
			for (int it = 0; it < newNode->numMetadata; it++)
			{
				in >> metadata;
				newNode->metadata.push_back(metadata);
				sum = sum + metadata;
			}
			if (currFather != nullptr)
			{
				newNode = currFather;
				currFather->childNodes--;
				currFather = currFather->father;
			}
			else
			{
				break;
			}
		}
		currFather = newNode;
	}

	out << sum;
	in.close();
	out.close();
}
