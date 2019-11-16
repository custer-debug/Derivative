#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
void Print_Vector(const std::vector<T>&);				//Print vector of any types
std::vector<int> Founder_Power(const std::string&);				//Looking power
std::vector<int> Founder_odds(const std::string&);				//Looking odds
bool Asci_function(std::vector<int>& vector_ascii);		
int ConcForNegativeNumber(std::vector<int>& vector_pow);
int ConcForPositiveNumber(std::vector<int>& vector_pow,bool);





void derivative(std::string& polynomial)
{
	std::vector<int> Power = Founder_Power(polynomial);
	std::vector<int> Odds = Founder_odds(polynomial);




}




int main() 
{
	std::string str = {"43253*x^4324+867*x^4324-432*x^2-4"};
	derivative(str);

	return 0;
}


template<class T>
void Print_Vector(const std::vector<T>& v)
{
	auto it = v.cbegin();
	for (; it != v.cend(); it++)
		std::cout << *it << " ";

	std::cout << std::endl;
}





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

			odds_in_function.push_back(*(odds.cend() - 1) > 0 ? ConcForPositiveNumber(odds,true) :\
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





