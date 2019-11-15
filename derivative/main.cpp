#include <iostream>
#include <vector>


template<class T>
void Print_Vector(const std::vector<T>& v);				//Print vector of any types
std::vector<int> Founder_Power(const std::string& s);				//Looking power
std::vector<int> Founder_odds(const std::string& s);				//Looking odds
int Concatenation(std::vector<int>& vector_pow);		//Concatenates vector elements into one number
void Asci_function(std::vector<int>& vector_ascii);		


void derivative(std::string polynomial)
{
	//std::vector<int> Power = Founder_Power(polynomial);
	std::vector<int> odds = Founder_odds(polynomial);



}




int main() 
{
	std::string str = {"-x^2-4*x-54*x-9999*x"};
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
		if (*it == 'x')
		{
			auto it1 = it;
			if(it1 == s.begin())
			{
				
				odds_in_function.push_back(1);
				continue;


			}
			else
				it1--;


			if (*it1 == '*')
				it1--;

			do
			{
				if (*it1 == '-')
				{
					odds.push_back(-1);
					break;
				}
				else if (*it1 == '+')
					break;

			
				

				odds.push_back(*it1);
				it1--;
			} while (it1 != s.cbegin());

			
			odds_in_function.push_back(Concatenation(odds));
			
		}
		
		
	}
	Print_Vector(odds_in_function);
	return odds;
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
				Number_of_power.push_back(*it);
				it++;
			} while (*it != '+' && *it != '-');

			Pow_of_function.push_back(Concatenation(Number_of_power));
		}

	}
	//Print_Vector(Pow_of_function);
	return Pow_of_function;
}



void Asci_function(std::vector<int>& vector_ascii) 
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

		default:
			std::cout << "This is not a number! " << vector_ascii[i] << \
				(char)vector_ascii[i] << std::endl;
			return ;
			break;
		}
	}

}


int Concatenation(std::vector<int>& vector_pow)
{

	
	Asci_function(vector_pow);

	int power = 0;
	int coef = 1;

	if (*(vector_pow.end() - 1) < 0 && vector_pow.size() > 1)
	{
		vector_pow.pop_back();
		power =	*(vector_pow.begin()) * -1;
		vector_pow.clear();
		return power;

	}

	auto it = vector_pow.rbegin();
	for (; it != vector_pow.rend(); it++)
	{
		power += *it * coef;
		coef *= 10;

	}

	vector_pow.clear();
	return power;
}


