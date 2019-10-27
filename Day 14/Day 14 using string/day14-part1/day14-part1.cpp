#include <iostream>
#include <fstream>
#include <string>

void findRecipeScores(std::string& scores,int length)
{
	int firstElf = 0;
	int secondElf = 1;

	while (scores.length() < length)
	{
		scores += std::to_string((scores[firstElf] - '0') + (scores[secondElf] - '0'));
		firstElf = (firstElf + (scores[firstElf] - '0') + 1) % scores.length();
		secondElf = (secondElf + (scores[secondElf] - '0') + 1) % scores.length();
	}

	if (scores.length() != length)
	{
		scores.erase(scores.end() - 1);
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::string scores("37");
	int length = 0;
	in >> length;

	findRecipeScores(scores, length + 10);
	out << scores.substr(length, 10);

	in.close();
	out.close();
}