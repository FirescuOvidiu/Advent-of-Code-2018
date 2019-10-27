#include <iostream>
#include <fstream>

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	
	int number = 0, sum = 0;

	while (in >> number)
	{
		sum += number;
	}

	out << sum;

	in.close();
	out.close();
}
