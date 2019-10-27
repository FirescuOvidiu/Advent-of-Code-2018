#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void readInput(std::vector<int>& input, std::fstream& in)
{
	std::string aux;
	char l;

	in >> aux >> l >> input[0] >> aux >> input[1] >> aux >> input[2] >> aux >> input[3] >> aux;
}


int countBehaves(const std::vector<int>& before, const std::vector<int>& instructions, const std::vector<int>& after)
{
	for (int it = 0; it < 4; it++)
	{
		if ((before[it] != after[it]) && (it != instructions[3]))
		{
			return 0;
		}
	}

	int count = 0;

	// addr and addi
	if (before[instructions[1]] + before[instructions[2]] == after[instructions[3]]) count++;
	if (before[instructions[1]] + instructions[2] == after[instructions[3]]) count++;

	// mulr and muli
	if (before[instructions[1]] * before[instructions[2]] == after[instructions[3]]) count++;
	if (before[instructions[1]] * instructions[2] == after[instructions[3]]) count++;

	// banr and bani
	if ((before[instructions[1]] & before[instructions[2]]) == after[instructions[3]]) count++;
	if ((before[instructions[1]] & instructions[2]) == after[instructions[3]]) count++;

	// borr and bori
	if ((before[instructions[1]] | before[instructions[2]]) == after[instructions[3]]) count++;
	if ((before[instructions[1]] | instructions[2]) == after[instructions[3]]) count++;

	// setr and seti
	if (before[instructions[1]] == after[instructions[3]]) count++;
	if (instructions[1] == after[instructions[3]]) count++;

	// gtir, gtri and gtrr
	if (instructions[1] > before[instructions[2]] == after[instructions[3]]) count++;
	if (before[instructions[1]] > instructions[2] == after[instructions[3]]) count++;
	if (before[instructions[1]] > before[instructions[2]] == after[instructions[3]]) count++;

	// eqir, eqri and eqrr
	if (instructions[1] == before[instructions[2]] == after[instructions[3]]) count++;
	if (before[instructions[1]] == instructions[2] == after[instructions[3]]) count++;
	if (before[instructions[1]] == before[instructions[2]] == after[instructions[3]]) count++;

	return count;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<int> before(4);
	std::vector<int> instructions(4);
	std::vector<int> after(4);
	int samples = 0;

	while (!in.eof())
	{
		readInput(before, in);
		in >> instructions[0] >> instructions[1] >> instructions[2] >> instructions[3];
		readInput(after, in);
		
		if (countBehaves(before, instructions, after) >= 3) samples++;
	}

	out << samples;

	in.close();
	out.close();
}