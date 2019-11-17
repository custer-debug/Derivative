#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <map>
#include <string>				


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

#pragma region Function Declaration

template<class T>
void Print_Vector(const std::vector<T>& v);

template<class U>
void Print_Map(const std::multimap<U, U>& m);

std::vector<int> Founder_Power(const std::string&);				//Looking power
std::vector<int> Founder_odds(const std::string&);				//Looking odds
int ConcForNegativeNumber(std::vector<int>& vector_pow);
int ConcForPositiveNumber(std::vector<int>& vector_pow,bool);
void Knot(const std::string& polynomial);
#pragma endregion



int main()
{
	std::string str = { "-x^2-x^3" };
	Knot(str);

	system("pause>nul");
	return 0;
}




void AddCoefficient(std::string& s, int num) 
{
	
	s += std::to_string(num);
	s += "*";
}

void AddPower(std::string& s, int num) 
{
	if (num == 1)
		return;
	s += "^";
	s += std::to_string(num);
}




void Compilation_Derivative(const std::multimap<int, int>& map)
{
	if (map.empty())
		return;
	
	int Coefficient = 0;
	int Power = 0;
	int C = 0;
	std::string str;
	auto iter = map.rbegin();
	for (;iter != map.rend(); iter++)
	{
		if (iter->first == 1)
			C += iter->second;
		else
		{
			Coefficient = iter->first * iter->second;
			Power = iter->first - 1;
			AddCoefficient(str,Coefficient);
			str += "x";
			AddPower(str,Power);
			str += "+";
		}
	}			//play me
		
	if (C != 0)
		str += std::to_string(C);
	else
		str.pop_back();
	
	std::cout << str << std::endl;

}



void AddToMap(std::vector<int>& vector1,std::vector<int>& vector2)
{
	size_t size = vector1.size();
	std::multimap<int, int> Derivative;
	for (size_t i = 0; i < size; i++)
		Derivative.emplace(vector1[i],vector2[i]);
	
	vector1.clear();
	vector2.clear();

	Compilation_Derivative(Derivative);
	//Print_Map(Derivative);

}






void Knot(const std::string& polynomial)
{	
	

	std::vector<int> Power = Founder_Power(polynomial);
	std::vector<int> Odds = Founder_odds(polynomial);

	if (Power.size() != Odds.size())
	{
		SetConsoleTextAttribute(console, FOREGROUND_RED);
		std::cout << "The number of degrees does not match the number of values" << std::endl;
		return ;
	}
	
//	std::cout << Power.size() << " ";

	AddToMap(Power, Odds); //Hash
	

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

			Pow_of_function.push_back(ConcForPositiveNumber(Number_of_power,false) );
		
		
		}else if(*it == 'x')
		{

			if (it == s.cend() - 1)
			{
				Pow_of_function.push_back(1);
				break;
			}
			if (*(it + 1) == '+' || *(it + 1) == '-' )
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

			case int('+') : vector_ascii.erase(std::begin(vector_ascii) + i,\
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

int ConcForPositiveNumber(std::vector<int>& vector_pow,bool flag = false)
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

template<class U>
void Print_Map(const std::multimap<U, U>& m)
{
	int i = 0;
	for (const auto& iter : m)
	{
		i++;
		std::cout << "Term " << i << ")" << " Power: " << iter.first\
			<< " Coefficient: " << iter.second << std::endl;
	}

}

#pragma endregion