#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>


class Instruction
{
public:
	Instruction(std::string _opcode, int _firstIn, int _secondIn, int _output) : opcode(_opcode), firstIn(_firstIn), secondIn(_secondIn), output(_output) {}

public:
	std::string opcode;
	int firstIn, secondIn;
	int output;
};


void readInput(std::fstream& in, std::vector<Instruction>& instructions, int& ip)
{
	std::string opcode{};
	int firstIn = 0, secondIn = 0;
	int output = 0;

	in >> opcode >> ip;
	while (in >> opcode >> firstIn >> secondIn >> output)
	{
		instructions.push_back(Instruction(opcode, firstIn, secondIn, output));
	}
}


void executeInstructions(const Instruction& instruction, std::vector<int>& output)
{
	if (instruction.opcode == "addr")
	{
		output[instruction.output] = output[instruction.firstIn] + output[instruction.secondIn];
		return;
	}
	if (instruction.opcode == "addi")
	{
		output[instruction.output] = output[instruction.firstIn] + instruction.secondIn;
		return;
	}
	if (instruction.opcode == "mulr")
	{
		output[instruction.output] = output[instruction.firstIn] * output[instruction.secondIn];
		return;
	}
	if (instruction.opcode == "muli")
	{
		output[instruction.output] = output[instruction.firstIn] * instruction.secondIn;
		return;
	}
	if (instruction.opcode == "banr")
	{
		output[instruction.output] = output[instruction.firstIn] & output[instruction.secondIn];
		return;
	}
	if (instruction.opcode == "bani")
	{
		output[instruction.output] = output[instruction.firstIn] & instruction.secondIn;
		return;
	}
	if (instruction.opcode == "borr")
	{
		output[instruction.output] = output[instruction.firstIn] | output[instruction.secondIn];
		return;
	}
	if (instruction.opcode == "bori")
	{
		output[instruction.output] = output[instruction.firstIn] | instruction.secondIn;
		return;
	}
	if (instruction.opcode == "setr")
	{
		output[instruction.output] = output[instruction.firstIn];
		return;
	}
	if (instruction.opcode == "seti")
	{
		output[instruction.output] = instruction.firstIn;
		return;
	}
	if (instruction.opcode == "gtir")
	{
		output[instruction.output] = instruction.firstIn > output[instruction.secondIn];
		return;
	}
	if (instruction.opcode == "gtri")
	{
		output[instruction.output] = output[instruction.firstIn] > instruction.secondIn;
		return;
	}
	if (instruction.opcode == "gtrr")
	{
		output[instruction.output] = output[instruction.firstIn] > output[instruction.secondIn];
		return;
	}
	if (instruction.opcode == "eqir")
	{
		output[instruction.output] = instruction.firstIn == output[instruction.secondIn];
		return;
	}
	if (instruction.opcode == "eqri")
	{
		output[instruction.output] = output[instruction.firstIn] == instruction.secondIn;
		return;
	}
	if (instruction.opcode == "eqrr")
	{
		output[instruction.output] = output[instruction.firstIn] == output[instruction.secondIn];
		return;
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<Instruction> instructions;
	std::vector<int> registers(6);
	int ip = 0;

	readInput(in, instructions, ip);

	int numInstructions = instructions.size();
	int initialIP = ip;
	int it = 0;
	ip = 0;
	registers[0] = 1;

	// I assumed that after 1000 iterations on any input we need to find out the sum of all the divisors of the largest register
	while (it < 1000)
	{
		std::cout << "\nip=" << ip << "\t";
		registers[initialIP] = ip;
		for (int i = 0; i < 6; i++)
		{
			std::cout << registers[i] << " ";
		}
		std::cout << "\t" << instructions[ip].opcode << " " << instructions[ip].firstIn << " " << instructions[ip].secondIn << " " << instructions[ip].output << "\t";
		executeInstructions(instructions[ip], registers);
		for (int i = 0; i < 6; i++)
		{
			std::cout << registers[i] << " ";
		}
		ip = registers[initialIP] + 1;
		it++;
	}

	int register0 = 0, registerX = 0;

	for (int it = 0; it < 6; it++)
	{
		if (registers[it] > registerX)
		{
			registerX = registers[it];
		}
	}

	for (int div = 1; div < sqrt(registerX); div++)
	{
		if (registerX % div == 0)
		{
			register0 += div;
			if (registerX / div != div)
			{
				register0 += registerX / div;
			}
		}
	}

	out << register0;

	in.close();
	out.close();
}