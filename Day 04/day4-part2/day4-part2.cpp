#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <utility>

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::string line;
	std::set<std::string> lines;

	while (std::getline(in, line))
	{
		lines.insert(line);
	}

	std::unordered_map<int, std::vector<int>> guards;
	std::vector<int> guard(60, 0);
	std::string operation;
	int guardId = 0;
	int fallsAsleepMinute = 0;
	int wakesUpMinute = 0;

	for (auto it = lines.cbegin(); it != lines.cend(); it++)
	{
		operation = (*it).substr(19, 5);
		if (operation == "Guard")
		{
			guardId = std::stoi((*it).substr(26));
		}

		if (operation == "falls")
		{
			fallsAsleepMinute = std::stoi((*it++).substr(15, 2));
			wakesUpMinute = std::stoi((*it).substr(15, 2));

			auto position = guards.find(guardId);

			if (position != guards.end())
			{
				for (int index = fallsAsleepMinute; index < wakesUpMinute; index++)
				{
					position->second[index]++;
				}
			}
			else
			{
				for (int index = fallsAsleepMinute; index < wakesUpMinute; index++)
				{
					guard[index]++;
				}

				guards.insert(std::pair<int, std::vector<int>>(guardId, guard));
				guard.clear();
				guard.resize(60, 0);
			}
		}
	}

	int guardIdMostAsleep = 0;
	int minuteMostAsleep = 0;
	int countTimes = 0;

	int currMinuteMostAsleep = 0;

	for (auto it = guards.cbegin(); it != guards.cend(); it++)
	{
		currMinuteMostAsleep = 0;

		for (int index = 0; index < 60; index++)
		{
			if (it->second[currMinuteMostAsleep] < it->second[index])
			{
				currMinuteMostAsleep = index;
			}
		}

		if (it->second[currMinuteMostAsleep] > countTimes)
		{
			countTimes = it->second[currMinuteMostAsleep];
			minuteMostAsleep = currMinuteMostAsleep;
			guardIdMostAsleep = it->first;
		}
	}

	out << guardIdMostAsleep * minuteMostAsleep;

	in.close();
	out.close();
}