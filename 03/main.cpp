#include "parser.h"

#include <vector>
#include <iostream>

void funcS(const std::string& str)
{
	std::cout <<"parsing string  : " << str << std::endl;
	std::cout << std::endl;
}
void funcStr(const std::string& str)
{
	std::cout <<"New string token is parsed  : "<< str << std::endl;
}
void funcNum(const uint64_t& num) {
	std::cout << "New numeral token is parsed  : " << num << std::endl;
}
void funcE(std::vector<std::string>& st, std::vector<uint64_t>& nt)
{
	std::cout << std::endl;
	for (size_t i = 0; i < nt.size(); ++i)
	{
		std::cout <<"Numeral token #" <<i << "  : "<< nt[i];
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (size_t i = 0; i < st.size(); ++i)
	{
		std::cout << "String token #" << i << "  : " << st[i];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
int main()
{
	parser *pr = new parser(funcS, funcNum, funcStr, funcE);
	pr->parseString("hello 123 h02 0001 12312z adsasdadsa hiiiiiiiiiiiiiiiiiiiiiiiiii hi 99999999999");
	delete pr;
	return 0;
}


