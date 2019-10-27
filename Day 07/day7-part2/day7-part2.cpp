#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <set>
#include <vector>


const int nWorkers = 5;


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

	std::map<char, Graph> graphNodes;
	std::set<std::pair<char,int>> nodes;
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
			nodes.insert(std::pair<char, int>((*it).first, ((*it).first) - 'A' + 60));
		}
	}

	std::vector<std::pair<char, int>> workers(nWorkers, std::make_pair('\0', -1));
	int workersWorking = 0;
	int counter = 0;

	while ((!nodes.empty()) || (workersWorking))
	{
		for (int it = 0; it < nWorkers; it++)
		{
			auto itNodes = nodes.begin();

			if (!nodes.empty())
			{
				if (workers[it].second == -1)
				{
					workers[it] = *itNodes;
					nodes.erase(itNodes);
					workersWorking++;
				}
			}
			else
			{
				break;
			}
		}

		for (int it = 0; it < nWorkers; it++)
		{
			if (workers[it].second != -1)
			{
				if (workers[it].second == 0)
				{
					for (auto itGraph = graphNodes[workers[it].first].neighbors.begin(); itGraph != graphNodes[workers[it].first].neighbors.end(); itGraph++)
					{
						if (graphNodes[*itGraph].gradeInt != -1)
						{
							graphNodes[*itGraph].gradeInt--;
							if (graphNodes[*itGraph].gradeInt == 0)
							{
								nodes.insert(std::pair<char, int>((*itGraph), (*itGraph) - 'A' + 60));
								graphNodes[*itGraph].gradeInt = -1;
							}
						}
					}
					workers[it].second = -1;
					workersWorking--;
				}
				else
				{
					workers[it].second--;
				}
			}
		}

		counter++;
	}

	out << counter;
	in.close();
	out.close();
}