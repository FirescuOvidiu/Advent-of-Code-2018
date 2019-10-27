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

	std::set<std::string> lines;
	std::string line;

	while (std::getline(in, line))
	{
		lines.insert(line);
	}

	// guard has 61 instead of 60 because on position 60 we will keep the total minutes slept by a guard
	std::unordered_map<int, std::vector<int>> guards;
	std::vector<int> guard(61, 0);
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
				position->second[60] += wakesUpMinute - fallsAsleepMinute;                       // Total minutes slept
			}
			else
			{
				for (int index = fallsAsleepMinute; index < wakesUpMinute; index++)
				{
					guard[index]++;
				}

				guard[60] = wakesUpMinute - fallsAsleepMinute;						  //  Total minutes slept
				guards.insert(std::pair<int, std::vector<int>>(guardId, guard));
				for (int index = 0; index < 61; index++)
				{
					guard[index] = 0;
				}
			}
		}
	}

	int guardIdMostMinutesSlept = 0;
	int mostMinutesSlept = 0;

	for (auto it = guards.cbegin(); it != guards.cend(); it++)
	{
		if (it->second[60] > mostMinutesSlept)
		{
			guardIdMostMinutesSlept = it->first;
			mostMinutesSlept = it->second[60];
		}
	}

	int mostAsleepMinute = 0;

	for (int index = 1; index < 60; index++)
	{
		if (guards[guardIdMostMinutesSlept][index] > guards[guardIdMostMinutesSlept][mostAsleepMinute])
		{
			mostAsleepMinute = index;
		}
	}

	out << guardIdMostMinutesSlept * mostAsleepMinute;

	in.close();
	out.close();
}