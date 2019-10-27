#include <iostream>
#include <fstream>
#include <vector>

class node
{
public:
	node() : metadataSum(0), numChildNodes(0), childNodes(0), numMetadata(0), father(nullptr) {}
public:
	std::vector<node*> childs;
	int metadataSum;
	int numChildNodes;
	int childNodes;
	int numMetadata;
	struct node* father;
};


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	int metadata = 0, sum = 0;
	node* root = new node;
	node* currFather = root;
	in >> root->childNodes >> root->numMetadata;
	root->numChildNodes = root->childNodes;

	while (!in.eof())
	{
		node* newNode = new node;
		in >> newNode->childNodes >> newNode->numMetadata;
		newNode->numChildNodes = newNode->childNodes;
		newNode->father = currFather;

		currFather->childs.push_back(newNode);

		while (newNode->childNodes == 0)
		{
			if (newNode->numChildNodes == 0)
			{
				for (int it = 0; it < newNode->numMetadata; it++)
				{
					in >> metadata;
					sum = sum + metadata;
				}
			}
			else
			{
				for (int it = 0; it < newNode->numMetadata; it++)
				{
					in >> metadata;
					metadata--;
					if ((metadata > -1) && (metadata < newNode->numChildNodes))
					{
						sum = sum + newNode->childs[metadata]->metadataSum;
					}
				}

			}
			newNode->metadataSum = sum;
			sum = 0;
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

	out << root->metadataSum;
	in.close();
	out.close();
}
