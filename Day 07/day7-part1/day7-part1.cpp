#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <set>


class Graph
{
public:
	Graph(int _gradeExt = 0, int _gradeInt = 0) : gradeExt(_gradeExt), gradeInt(_gradeInt) {}
public:
	int gradeExt;
	int gradeInt;
	std::list<char> neighbors;
};


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::map<char,Graph> graphNodes;
	std::set<char> nodes;
	std::string line;

	while (std::getline(in, line))
	{
		graphNodes[line[5]].gradeExt++;
		graphNodes[line[5]].neighbors.push_back(line[36]);
		graphNodes[line[36]].gradeInt++;
	}

	for (auto it = graphNodes.begin(); it != graphNodes.end(); it++)
	{
		if ((*it).second.gradeInt == 0)
		{
			nodes.insert((*it).first);
		}
	}

	char node = -1;

	while (!nodes.empty())
	{
		node = *(nodes.begin());
		nodes.erase(node);
		out << node;

		for (auto it = graphNodes[node].neighbors.begin(); it != graphNodes[node].neighbors.end(); it++)
		{
			if (graphNodes[*it].gradeInt != -1)
			{
				graphNodes[*it].gradeInt--;
				if (graphNodes[*it].gradeInt == 0)
				{
					nodes.insert(*it);
					graphNodes[*it].gradeInt = -1;
				}
			}
		}
	}

	in.close();
	out.close();
}
