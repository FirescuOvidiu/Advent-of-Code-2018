#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>


void executeInstructions(const std::vector<int>& instructions, std::vector<int>& output,const std::vector<int>& order)
{
	switch (order[instructions[0]])
	{
	// addr
	case 0: 
		output[instructions[3]] = output[instructions[1]] + output[instructions[2]];
		break;

	// addi
	case 1:
		output[instructions[3]] = output[instructions[1]] + instructions[2];
		break;

	// mulr
	case 2:
		output[instructions[3]] = output[instructions[1]] * output[instructions[2]];
		break;

	// muli
	case 3:
		output[instructions[3]] = output[instructions[1]] * instructions[2];
		break;

	// banr
	case 4:
		output[instructions[3]] = output[instructions[1]] & output[instructions[2]];
		break;

	// bani
	case 5:
		output[instructions[3]] = output[instructions[1]] & instructions[2];
		break;

	// borr
	case 6:
		output[instructions[3]] = output[instructions[1]] | output[instructions[2]];
		break;

	// bori
	case 7:
		output[instructions[3]] = output[instructions[1]] | instructions[2];
		break;

	// setr
	case 8:
		output[instructions[3]] = output[instructions[1]];
		break;

	// seti
	case 9:
		output[instructions[3]] = instructions[1];
		break;

	// gtir
	case 10:
		output[instructions[3]] = instructions[1] > output[instructions[2]];
		break;

	// gtri
	case 11:
		output[instructions[3]] = output[instructions[1]] > instructions[2];
		break;

	// gtrr
	case 12:
		output[instructions[3]] = output[instructions[1]] > output[instructions[2]];
		break;

	// eqir
	case 13:
		output[instructions[3]] = instructions[1] == output[instructions[2]];
		break;

	// eqri
	case 14:
		output[instructions[3]] = output[instructions[1]] == instructions[2];
		break;

	// eqrr
	case 15:
		output[instructions[3]] = output[instructions[1]] == output[instructions[2]];
		break;
	}
}


void calculateFrequency(const std::vector<int>& before, const std::vector<int>& instructions, const std::vector<int>& after, std::vector<std::vector<int>>& freq)
{
	for (int it = 0; it < 4; it++)
	{
		if ((before[it] != after[it]) && (it != instructions[3]))
		{
			return;
		}
	}

	if (before[instructions[1]] + before[instructions[2]] == after[instructions[3]]) freq[instructions[0]][0]++;
	if (before[instructions[1]] + instructions[2] == after[instructions[3]]) freq[instructions[0]][1]++;

	// mulr and muli
	if (before[instructions[1]] * before[instructions[2]] == after[instructions[3]]) freq[instructions[0]][2]++;
	if (before[instructions[1]] * instructions[2] == after[instructions[3]]) freq[instructions[0]][3]++;

	// banr and bani
	if ((before[instructions[1]] & before[instructions[2]]) == after[instructions[3]]) freq[instructions[0]][4]++;
	if ((before[instructions[1]] & instructions[2]) == after[instructions[3]]) freq[instructions[0]][5]++;

	// borr and bori
	if ((before[instructions[1]] | before[instructions[2]]) == after[instructions[3]]) freq[instructions[0]][6]++;
	if ((before[instructions[1]] | instructions[2]) == after[instructions[3]]) freq[instructions[0]][7]++;

	// setr and seti
	if (before[instructions[1]] == after[instructions[3]]) freq[instructions[0]][8]++;
	if (instructions[1] == after[instructions[3]]) freq[instructions[0]][9]++;

	// gtir, gtri and gtrr
	if (instructions[1] > before[instructions[2]] == after[instructions[3]]) freq[instructions[0]][10]++;
	if (before[instructions[1]] > instructions[2] == after[instructions[3]]) freq[instructions[0]][11]++;
	if (before[instructions[1]] > before[instructions[2]] == after[instructions[3]]) freq[instructions[0]][12]++;

	// eqir, eqri and eqrr
	if (instructions[1] == before[instructions[2]] == after[instructions[3]]) freq[instructions[0]][13]++;
	if (before[instructions[1]] == instructions[2] == after[instructions[3]]) freq[instructions[0]][14]++;
	if (before[instructions[1]] == before[instructions[2]] == after[instructions[3]]) freq[instructions[0]][15]++;
}


void readInput(std::vector<int>& input, std::fstream& in)
{
	std::string aux;
	char l;

	in >> aux >> l >> input[0] >> aux >> input[1] >> aux >> input[2] >> aux >> input[3] >> aux;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream in2("input2.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<int> before(4);
	std::vector<int> instructions(4);
	std::vector<int> after(4);
	std::vector<std::vector<int>> freq(16, std::vector<int>(16));

	while (!in.eof())
	{
		readInput(before, in);
		in >> instructions[0] >> instructions[1] >> instructions[2] >> instructions[3];
		readInput(after, in);

		calculateFrequency(before, instructions, after, freq);
	}

	std::vector<int> order(16, -1);
	std::vector<int> numElements(16, 0);
	int posMax = 0;
	int num = 0;

	for (int l = 0; l < 16; l++)
	{
		posMax = 0;
		num = 1;

		for (int c = 1; c < 16; c++)
		{
			if (freq[l][posMax] < freq[l][c])
			{
				freq[l][posMax] = 0;
				posMax = c;
				num = 1;
			}
			else
			{
				if (freq[l][posMax] == freq[l][c])
				{
					num++;
				}
				else
				{
					freq[l][c] = 0;
				}
			}
		}

		numElements[l] = num;
	}

	int pos = 0;

	while (pos != -1)
	{
		pos = -1;

		for (int it = 0; it < 16; it++)
		{
			if (numElements[it] == 1)
			{
				numElements[it] = 0;
				pos = it;
				break;
			}
		}

		if (pos != -1)
		{
			for (int it = 0; it < 16; it++)
			{
				if (freq[pos][it] != 0)
				{
					freq[pos][it] = 0;
					for (int i = 0; i < 16; i++)
					{
						if (freq[i][it] != 0)
						{
							numElements[i]--;
							freq[i][it] = 0;
						}
					}
					order[pos] = it;
					break;
				}
			}
		}
	}



	std::vector<int> output(4);

	while (in2 >> instructions[0] >> instructions[1] >> instructions[2] >> instructions[3])
	{
		executeInstructions(instructions, output, order);
	}

	out << output[0];

	in.close();
	out.close();
}