#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class Cart
{
public:
	Cart(char _cartDirection = ' ', int _x = 0, int _y = 0, char _replaced = ' ') : cartDirection(_cartDirection), x(_x), y(_y), intersectionTurn('L'), replaced(_replaced) {}
	static bool sortingRule(const Cart& a, const Cart& b)
	{
		return a.x < b.x ? true : (a.x == b.x ? a.y < b.y : false);
	}

public:
	char cartDirection;
	int x, y;
	char intersectionTurn;
	char replaced;
};


void determinateCartDirection(Cart& currCart)
{
	switch (currCart.replaced)
	{
	case '+':
		if (currCart.intersectionTurn == 'S')
		{
			currCart.intersectionTurn = 'R';
		}
		else
		{
			if (currCart.intersectionTurn == 'L')
			{
				currCart.intersectionTurn = 'S';

				if (currCart.cartDirection == 'v') currCart.cartDirection = '>';
				else if (currCart.cartDirection == '>') currCart.cartDirection = '^';
				else if (currCart.cartDirection == '^') currCart.cartDirection = '<';
				else if (currCart.cartDirection == '<') currCart.cartDirection = 'v';
			}

			if (currCart.intersectionTurn == 'R')
			{
				currCart.intersectionTurn = 'L';

				if (currCart.cartDirection == 'v') currCart.cartDirection = '<';
				else if (currCart.cartDirection == '>') currCart.cartDirection = 'v';
				else if (currCart.cartDirection == '^') currCart.cartDirection = '>';
				else if (currCart.cartDirection == '<') currCart.cartDirection = '^';
			}
		}
		break;

	case'\\':
		if (currCart.cartDirection == '>') currCart.cartDirection = 'v';
		else if (currCart.cartDirection == '^') currCart.cartDirection = '<';
		else if (currCart.cartDirection == '<') currCart.cartDirection = '^';
		else if (currCart.cartDirection == 'v') currCart.cartDirection = '>';
		break;

	case '/':
		if (currCart.cartDirection == '>') currCart.cartDirection = '^';
		else if (currCart.cartDirection == '^') currCart.cartDirection = '>';
		else if (currCart.cartDirection == '<') currCart.cartDirection = 'v';
		else if (currCart.cartDirection == 'v') currCart.cartDirection = '<';
		break;

	}
}


void moveCart(Cart& currCart, std::vector<std::string>& lines)
{
	lines[currCart.x][currCart.y] = currCart.replaced;

	switch (currCart.cartDirection)
	{
	case'>':
		currCart.y++;
		break;
	case'<':
		currCart.y--;
		break;
	case'v':
		currCart.x++;
		break;
	case'^':
		currCart.x--;
		break;
	}

	currCart.replaced = lines[currCart.x][currCart.y];
	lines[currCart.x][currCart.y] = currCart.cartDirection;
}

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<Cart> carts;
	std::vector<std::string> lines;
	std::string line;
	int x = 0;

	while (std::getline(in, line))
	{
		lines.push_back(line);

		for (int y = 0; y < line.length(); y++)
		{
			if ((line[y] == '>') || (line[y] == '<'))
			{
				carts.push_back(Cart(line[y], x, y, '-'));
			}

			if ((line[y] == 'v') || (line[y] == '^'))
			{
				carts.push_back(Cart(line[y], x, y, '|'));
			}
		}
		x++;
	}

	int it = 0, nCarts = carts.size();

	while (carts.size() != 1)
	{
		//for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
		//{
		//	std::cout << *it << "\n";
		//}
		//std::cout << "\n\n";

		it = 0;
		nCarts = carts.size();

		while(it<nCarts)
		{
			moveCart(carts[it], lines);

			if ((carts[it].replaced == '>') || (carts[it].replaced == '<') ||
				(carts[it].replaced == '^') || (carts[it].replaced == 'v'))
			{
				int second = 0;

				for (second = 0; second < nCarts; second++)
				{
					if ((carts[second].x == carts[it].x) && (carts[second].y == carts[it].y) && (carts[second].replaced != carts[it].replaced))
					{
						break;
					}
				}

				lines[carts[second].x][carts[second].y] = carts[second].replaced;

				if (second < it)
				{
					std::swap(second, it);
				}

				carts.erase(carts.begin() + second);
				carts.erase(carts.begin() + it);
				nCarts = carts.size();
			}
			else
			{
				determinateCartDirection(carts[it]);
				it++;
			}
		}

		std::sort(carts.begin(), carts.end(), Cart::sortingRule);
	}

	//for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
	//{
	//	std::cout << *it << "\n";
	//}
	//std::cout << "\n\n";

	out << carts[0].y << "," << carts[0].x;
	in.close();
	out.close();
}
