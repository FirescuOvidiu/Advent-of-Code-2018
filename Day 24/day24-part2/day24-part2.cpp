#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>


class army
{
public:
	army(std::string attackType = {}, std::vector<std::string> immunities = {}, std::vector<std::string> weaknesses = {}) :
		units(0), hitPoints(0), attackDamage(0), attackType(attackType), initiative(0), immunities(immunities),
		weaknesses(weaknesses), choosen(false), dmgGiven(0), posChoosenToAttack(-1), effectivePower(0), enemyType("") {}


	void resetArmy()
	{
		choosen = false;
		dmgGiven = 0;
		posChoosenToAttack = -1;
		effectivePower = (long long) attackDamage * units;
	}
public:
	int units;
	int hitPoints;
	int	attackDamage;
	long long effectivePower;
	std::string attackType;
	int initiative;
	std::vector<std::string> immunities;
	std::vector<std::string> weaknesses;
	int posChoosenToAttack;
	std::string enemyType;
	long long dmgGiven;
	bool choosen;
};


bool sortingRule2(const army& a1, const army& a2)
{
	return  a1.initiative > a2.initiative;
};


void readInput(std::fstream& in, std::vector<army>& immuneSystem, std::vector<army>& infection)
{
	army currArmy;
	std::string aux;
	std::string type;
	std::string typeArmy;

	while (in >> aux)
	{
		if (aux == "Immune")
		{
			typeArmy = "Immune";
			in >> aux >> currArmy.units;
		}
		else
		{
			if (aux == "Infection:")
			{
				typeArmy = "Infection";
				in >> currArmy.units;
			}
			else
			{
				currArmy.units = std::stoi(aux);
			}
		}

		in >> aux >> aux >> aux >> currArmy.hitPoints >> aux >> aux >> aux;
		if (aux[0] == '(')
		{
			aux.erase(aux.begin());
			type = aux;
			in >> aux >> aux;
			while (aux != "with")
			{
				if (aux[aux.size() - 1] == ';')
				{
					aux.erase(aux.size() - 1);
					if (type == "weak")
					{
						type = "immune";
						currArmy.weaknesses.push_back(aux);
					}
					else
					{
						type = "weak";
						currArmy.immunities.push_back(aux);
					}
					in >> aux >> aux;
				}
				else
				{
					aux.erase(aux.size() - 1);
					if (type == "weak")		currArmy.weaknesses.push_back(aux);
					else					currArmy.immunities.push_back(aux);
				}
				in >> aux;
			}
		}
		in >> aux >> aux >> aux >> aux >> currArmy.attackDamage >> currArmy.attackType;
		in >> aux >> aux >> aux >> currArmy.initiative;
		currArmy.effectivePower = (long long) currArmy.attackDamage * currArmy.units;

		if (typeArmy == "Immune")
		{
			currArmy.enemyType = "Infection";
			immuneSystem.push_back(currArmy);
		}
		else
		{
			currArmy.enemyType = "Immune";
			infection.push_back(currArmy);
		}
		currArmy.weaknesses.clear();
		currArmy.immunities.clear();
	}
}


bool sortingRule(const army& a1, const army& a2)
{
	if (a1.effectivePower > a2.effectivePower)
	{
		return true;
	}
	else
	{
		if (a1.effectivePower == a2.effectivePower)
		{
			if (a1.initiative > a2.initiative)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		return false;
	}
}


void targetSelectionPhase(std::vector<army>& firstArmy, std::vector<army>& secondArmy, std::vector<army>& attackers)
{
	int effectivePower = 0;

	for (int itFirstArmy = 0; itFirstArmy < firstArmy.size(); itFirstArmy++)
	{
		for (int itSecondArmy = 0; itSecondArmy < secondArmy.size(); itSecondArmy++)
		{
			if (secondArmy[itSecondArmy].choosen)
			{
				continue;
			}

			effectivePower = firstArmy[itFirstArmy].effectivePower;
			for (int itImununities = 0; itImununities < secondArmy[itSecondArmy].immunities.size(); itImununities++)
			{
				if (firstArmy[itFirstArmy].attackType == secondArmy[itSecondArmy].immunities[itImununities])
				{
					effectivePower = 0;
					break;
				}
			}

			for (int itWeak = 0; itWeak < secondArmy[itSecondArmy].weaknesses.size(); itWeak++)
			{
				if (firstArmy[itFirstArmy].attackType == secondArmy[itSecondArmy].weaknesses[itWeak])
				{
					effectivePower *= 2;
					break;
				}
			}

			if (effectivePower == 0)
			{
				continue;
			}

			if (effectivePower > firstArmy[itFirstArmy].dmgGiven)
			{
				if (firstArmy[itFirstArmy].posChoosenToAttack != -1)
				{
					secondArmy[firstArmy[itFirstArmy].posChoosenToAttack].choosen = false;
				}
				firstArmy[itFirstArmy].dmgGiven = effectivePower;
				firstArmy[itFirstArmy].posChoosenToAttack = itSecondArmy;
				secondArmy[itSecondArmy].choosen = true;
			}
			else
			{
				if (effectivePower == firstArmy[itFirstArmy].dmgGiven)
				{
					if (secondArmy[itSecondArmy].effectivePower > secondArmy[firstArmy[itFirstArmy].posChoosenToAttack].effectivePower)
					{
						secondArmy[firstArmy[itFirstArmy].posChoosenToAttack].choosen = false;
						firstArmy[itFirstArmy].dmgGiven = effectivePower;
						firstArmy[itFirstArmy].posChoosenToAttack = itSecondArmy;
						secondArmy[itSecondArmy].choosen = true;
					}
					else
					{
						if (secondArmy[itSecondArmy].effectivePower == secondArmy[firstArmy[itFirstArmy].posChoosenToAttack].effectivePower)
						{
							if (secondArmy[itSecondArmy].initiative > secondArmy[firstArmy[itFirstArmy].posChoosenToAttack].initiative)
							{
								secondArmy[firstArmy[itFirstArmy].posChoosenToAttack].choosen = false;
								firstArmy[itFirstArmy].dmgGiven = effectivePower;
								firstArmy[itFirstArmy].posChoosenToAttack = itSecondArmy;
								secondArmy[itSecondArmy].choosen = true;
							}
						}
					}
				}
			}
		}

		if (firstArmy[itFirstArmy].posChoosenToAttack != -1)
		{
			attackers.push_back(firstArmy[itFirstArmy]);
		}
	}
}


void attackingPhase(std::vector<army>& firstArmy, std::vector<army>& secondArmy, std::vector<army>& attackers, int it)
{
	secondArmy[attackers[it].posChoosenToAttack].units -= attackers[it].dmgGiven / secondArmy[attackers[it].posChoosenToAttack].hitPoints;
	for (int itAtt = it + 1; itAtt < attackers.size(); itAtt++)
	{
		if (secondArmy[attackers[it].posChoosenToAttack].initiative == attackers[itAtt].initiative)
		{
			if (secondArmy[attackers[it].posChoosenToAttack].units <= 0)
			{
				attackers[itAtt].dmgGiven = 0;
			}
			else
			{
				if (attackers[itAtt].effectivePower == attackers[itAtt].dmgGiven)
				{
					attackers[itAtt].dmgGiven = (long long) secondArmy[attackers[it].posChoosenToAttack].units * attackers[itAtt].attackDamage;
				}
				else
				{
					attackers[itAtt].dmgGiven = (long long) secondArmy[attackers[it].posChoosenToAttack].units * attackers[itAtt].attackDamage * 2;
				}
			}
			break;
		}
	}
}


void eraseDestroyedUnits(std::vector<army>& army)
{
	auto it = army.begin();
	while (it != army.end())
	{
		if ((*it).units <= 0)
		{
			it = army.erase(it);
		}
		else
		{
			(*it).resetArmy();
			it++;
		}
	}
}


void calculateTotalUnits(const std::vector<army>& army, int& totalUnits)
{
	for (auto it = army.begin(); it != army.end(); it++)
	{
		totalUnits += (*it).units;
	}
}


bool part1(std::vector<army>& immuneSystem, std::vector<army>& infection)
{
	std::vector<army> attackers;
	int effectivePower = 0;
	std::vector<army> auxImmuneSystem;
	std::vector<army> auxInfection;
	while (!immuneSystem.empty() && !infection.empty())
	{
		std::sort(immuneSystem.begin(), immuneSystem.end(), sortingRule);
		std::sort(infection.begin(), infection.end(), sortingRule);

		auxImmuneSystem = immuneSystem;
		auxInfection = infection;
		targetSelectionPhase(immuneSystem, infection, attackers);
		targetSelectionPhase(infection, immuneSystem, attackers);
		std::sort(attackers.begin(), attackers.end(), sortingRule2);

		for (int it = 0; it < attackers.size(); it++)
		{
			if (attackers[it].dmgGiven == 0)
			{
				continue;
			}

			if (attackers[it].enemyType == "Infection")
			{
				attackingPhase(immuneSystem, infection, attackers, it);
			}
			else
			{
				attackingPhase(infection, immuneSystem, attackers, it);
			}
		}

		if ((auxImmuneSystem.size() == immuneSystem.size()) && (auxInfection.size() == infection.size()))
		{
			bool noChanges = true;

			for (int it = 0; it < immuneSystem.size(); it++)
			{
				if (immuneSystem[it].units != auxImmuneSystem[it].units)
				{
					noChanges = false;
					break;
				}
			}
			for (int it = 0; it < infection.size(); it++)
			{
				if (infection[it].units != auxInfection[it].units)
				{
					noChanges = false;
					break;
				}
			}

			if (noChanges)
			{
				return false;
			}
		}

		eraseDestroyedUnits(immuneSystem);
		eraseDestroyedUnits(infection);
		attackers.clear();
	}

	if (!immuneSystem.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}


int binarySearch(std::vector<army> immuneSystem, std::vector<army> infection)
{
	std::vector<army> auxImmuneSystem(immuneSystem);
	std::vector<army> auxInfection(infection);
	int l = 1, r = 2147483647;
	int mid = l + (r - l) / 2;

	while (l < r)
	{
		immuneSystem = auxImmuneSystem;
		infection = auxInfection;
		for (auto it = immuneSystem.begin(); it != immuneSystem.end(); it++)
		{
			(*it).attackDamage += mid;
			(*it).effectivePower = (long long) (*it).attackDamage * (*it).units;
		}

		if (part1(immuneSystem, infection))
		{
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
		mid = l + (r - l) / 2;
	}

	return r;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<army> immuneSystem;
	std::vector<army> infection;
	std::vector<army> attackers;

	readInput(in, immuneSystem, infection);

	int boost = binarySearch(immuneSystem, infection);

	for (auto it = immuneSystem.begin(); it != immuneSystem.end(); it++)
	{
		(*it).attackDamage += boost + 1;
		(*it).effectivePower = (long long)(*it).attackDamage * (*it).units;
	}
	part1(immuneSystem, infection);

	int totalUnits = 0;
	if (!immuneSystem.empty())
	{
		calculateTotalUnits(immuneSystem, totalUnits);
	}
	else
	{
		calculateTotalUnits(infection, totalUnits);
	}

	out << totalUnits;

	in.close();
	out.close();
}