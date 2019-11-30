#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>		


typedef		std::multimap<int, int>	MULT;
typedef		std::map<int, int> MAP;


#pragma region Function Declaration

template<class T>
void Print_Vector(const std::vector<T>& v);
void Print_Map(const MAP& m);
void Print_MultMap(const MULT& m);



std::vector<int> Founder_Power(const std::string&);				//Looking power
std::vector<int> Founder_odds(const std::string&);				//Looking odds
int ConcForNegativeNumber(std::vector<int>& vector_pow);
int ConcForPositiveNumber(std::vector<int>& vector_pow, bool);
std::string derivative(const std::string& polynomial);
#pragma endregion



int main()
{
	int flag = 0;
	std::string str;
	std::cout << "Hello! This program calculates the derivative." << std::endl;
	std::cout << "Enter the function. For the operation of multiplication, use the sign *" << std::endl;
	std::cout << "For exponentiation operation ^" << std::endl;
	
	while (true) 
	{
		std::cout << "Enter the function: ";
		std::cin >> str;
		system("cls");
		std::cout << "Your funcrion: " << str <<std::endl;
		std::cout << "Derivative: " << derivative(str) << std::endl;
		system("pause>nul");
		std::cout << "Do u wonna continue?" << std::endl;
		std::cout << "1.Yes" << std::endl;
		std::cout << "2.No" << std::endl;
		std::cin >> flag;
		if (flag == 2)
			break;
			
		

	}

	return 0;
}



std::string DeleteFirstPlus(const std::string& s)
{
	std::string str;
	if (s[0] == '+')
	{
		for (int i = 1; i != s.length(); i++)
			str += s[i];

	}
	else
		str = s;

	return str;
}



std::string MapToString(const MAP& m)
{
	std::string str;

	for (auto it = m.rbegin(); it != m.rend(); it++)
	{
		if (it->second == 0)
			continue;

		if (it->first == 1 && it->second == 1)
			str += "+x";
		else if (it->first == 1 && it->second == 1 && it == m.rbegin())
			str += "x";
		else if (it->first == 0 && it->second == 1)
		{
			str += "+";
			str += std::to_string(it->second);
		}
		else if (it->first == 0 && it == m.rbegin())
			return std::to_string(it->second);
		else if (it->first == 0 && it->second > 0)
		{
			str += "+";
			str += std::to_string(it->second);
		}
		else if (it->first == 0 && it->second < 0)
			str += std::to_string(it->second);
		else if (it->first == 1 && it->second > 0)
		{
			str += "+";
			str += std::to_string(it->second);
			str += "*x";
		}
		else if (it->first == 1 && it->second < 0)
		{
			str += std::to_string(it->second);
			str += "*x";
		}
		else if (it->first > 1 && it->second > 0)
		{
			str += "+";
			str += std::to_string(it->second);
			str += "*x^";
			str += std::to_string(it->first);
		}
		else if (it->first > 1 && it->second < 0)
		{
			str += std::to_string(it->second);
			str += "*x^";
			str += std::to_string(it->first);
		}

	}

	str = DeleteFirstPlus(str);

	return str;
}


MAP SimilarCoef(MULT& mult)
{
	MAP res;
	for (auto it1 = mult.begin(); it1 != mult.end(); it1++)
		for (auto it2 = it1; it2 != mult.end(); it2++)
			if (it1 != it2)
				if (it1->first == it2->first)
					it1->second += it2->second;

	for (auto it = mult.begin(); it != mult.end(); it++)
		res.emplace(it->first, it->second);


	/*for (auto it = res.begin(); it != res.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;*/


	return res;
}


std::string Compilation_Derivative(MULT& Func)
{
	if (Func.empty())
		return "0";

	MULT mult;

	for (auto it = Func.begin(); it != Func.end(); it++)
		mult.emplace(it->first - 1, it->first * it->second);

	MAP map = SimilarCoef(mult);

	return MapToString(map);
}

std::string AddToMap(std::vector<int>& vector1, std::vector<int>& vector2)
{
	size_t size = vector1.size();
	std::multimap<int, int> Derivative;
	for (size_t i = 0; i < size; i++)
		Derivative.emplace(vector1[i], vector2[i]);

	vector1.clear();
	vector2.clear();


	return Compilation_Derivative(Derivative);



}


std::string derivative(const std::string& polynomial)
{


	std::vector<int> Power = Founder_Power(polynomial);
	std::vector<int> Odds = Founder_odds(polynomial);

	if (Power.size() != Odds.size())
		return "Error";

	

	return AddToMap(Power, Odds); //Hash


}






#pragma region Parser

std::vector<int> Founder_odds(const std::string& s)
{
	std::vector<int> odds;
	std::vector<int> odds_in_function;
	auto it = s.cbegin();
	for (; it != s.cend(); it++)
	{
		if (*it == 'x')	//Find virable
		{
			auto it1 = it;
			if (it1 == s.begin())
			{
				odds_in_function.push_back(1);
				continue;
			}
			else
				it1--;


			if (*it1 == '*')
				it1--;
			else if (*it1 == '-')
			{
				odds_in_function.push_back(-1);
				continue;
			}
			else if (*it1 == '+')
			{
				odds_in_function.push_back(1);
				continue;
			}




			while (true)
			{
				if (it1 == s.cbegin())
				{
					if (*it1 == '-')
					{
						odds.push_back(-1);
						break;
					}

					odds.push_back(*it1);
					break;
				}

				if (*it1 == '-')
				{
					odds.push_back(-1);
					break;

				}
				else if (*it1 == '+')
					break;

				odds.push_back(*it1);
				it1--;

			}
			odds_in_function.push_back(*(odds.cend() - 1) > 0 ? ConcForPositiveNumber(odds, true) : \
				ConcForNegativeNumber(odds));

		}

	}

	return odds_in_function;
}

std::vector<int> Founder_Power(const std::string& s)
{
	std::vector<int> Number_of_power;
	std::vector<int> Pow_of_function;

	auto it = s.cbegin();
	for (; it != s.cend(); it++)
	{
		if (*it == '^')
		{
			it++;
			do
			{
				if (it == s.cend() - 1)
				{
					Number_of_power.push_back(*it);
					break;
				}


				Number_of_power.push_back(*it);
				it++;

			} while (*it != '+' && *it != '-');

			Pow_of_function.push_back(ConcForPositiveNumber(Number_of_power, false));


		}
		else if (*it == 'x')
		{

			if (it == s.cend() - 1)
			{
				Pow_of_function.push_back(1);
				break;
			}
			if (*(it + 1) == '+' || *(it + 1) == '-')
				Pow_of_function.push_back(1);
		}

	}

	return Pow_of_function;
}

bool Asci_function(std::vector<int>& vector_ascii)
{
	for (int i = 0; i < (int)vector_ascii.size(); i++)
	{
		switch (vector_ascii[i])
		{
		case 48:vector_ascii[i] = 0;	break;
		case 49:vector_ascii[i] = 1;	break;
		case 50:vector_ascii[i] = 2;	break;
		case 51:vector_ascii[i] = 3;	break;
		case 52:vector_ascii[i] = 4;	break;
		case 53:vector_ascii[i] = 5;	break;
		case 54:vector_ascii[i] = 6;	break;
		case 55:vector_ascii[i] = 7;	break;
		case 56:vector_ascii[i] = 8;	break;
		case 57:vector_ascii[i] = 9;	break;
		case -1:vector_ascii[i] = -1;   break;
		case 1:vector_ascii[i] = 1;   break;

			case int('+') : vector_ascii.erase(std::begin(vector_ascii) + i, \
				std::begin(vector_ascii) + i + 1); break;
			default:
				std::cout << "This is not a number! " << \
					vector_ascii[i] << std::endl;
				return false;
				break;
		}
	}
	return true;
}

int Concantination(std::vector<int>& vector)
{
	int con = 0;
	int coef = 1;

	auto it = vector.rbegin();
	for (; it != vector.rend(); it++)
	{
		con += *it * coef;
		coef *= 10;
	}
	vector.clear();
	return con;
}

int ConcForNegativeNumber(std::vector<int>& vector_pow)
{
	if (!Asci_function(vector_pow))
		return 0;

	if (*(vector_pow.end() - 1) < 0 && vector_pow.size() > 1)
	{

		vector_pow.pop_back();
		std::reverse(std::begin(vector_pow), std::end(vector_pow));
		return Concantination(vector_pow) * -1;

	}
	vector_pow.clear();
	return -1;
}

int ConcForPositiveNumber(std::vector<int>& vector_pow, bool flag = false)
{
	if (!Asci_function(vector_pow))
		return 0;

	if (flag)
		std::reverse(std::begin(vector_pow), std::end(vector_pow));

	return Concantination(vector_pow);

}

#pragma endregion











#pragma region Print


template<class T>
void Print_Vector(const std::vector<T>& v)
{
	std::cout << std::endl;
	std::cout << "Print vector" << std::endl;

	auto it = v.cbegin();
	if (v.cbegin() == v.cend())
	{
		std::cout << "No items " << std::endl;
		return;
	}
	for (; it != v.cend(); it++)
		std::cout << *it << " ";

	std::cout << std::endl;
}



void Print_Map(const MAP& m)
{
	std::cout << std::endl;
	std::cout << "Print multimap" << std::endl;

	int i = 0;
	for (const auto& iter : m)
	{
		i++;
		std::cout << "Term " << i << ")" << " Power: " << iter.first\
			<< " Coefficient: " << iter.second << std::endl;
	}
	std::cout << std::endl;
}


void Print_MultMap(const MULT& m)
{
	std::cout << std::endl;
	std::cout << "Print multimap" << std::endl;

	int i = 0;
	for (const auto& iter : m)
	{
		i++;
		std::cout << "Term " << i << ")" << " Power: " << iter.first\
			<< " Coefficient: " << iter.second << std::endl;
	}
	std::cout << std::endl;
}




#pragma endregion