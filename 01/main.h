#pragma once
#include <iostream>
#include <string>
#include <algorithm>

void DeleteSpaces(std::string& str);
bool CheckString(std::string str);
int GetNextInteger(std::string str);
int ParseArithmeticEspression(std::string str);
void SimplifyMinuses(std::string& str);

// Simplify double negation and sum with negative
inline void SimplifyMinuses(std::string& str) {
	for (int i = str.find("--"); i != -1; i = str.find("--")) {
		str.replace(i, 2, "+");
	}
	for (int i = str.find("+-"); i != -1; i = str.find("+-")) {
		str.replace(i, 2, "-");
	}
	for (int i = str.find("++"); i != -1; i = str.find("++")) {
		str.replace(i, 2, "+");
	}
}

// Removes all whitespaces in string
inline void DeleteSpaces(std::string& str) {
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
}

// Checks string for missing signs, unintentionall
// space or wrong symbols
bool CheckString(std::string str) {
	std::string alphavite = "1234567890+-*/ ";
	bool isPrevADigit = false;
	size_t len = str.length();

	// check for spaces
	for (size_t i = 0; i < len; ++i) {
		if (isPrevADigit && (i + 1) < len && str[i] == ' ' && isdigit(str[i + 1]) ||
			alphavite.find(str[i]) == std::string::npos)
			return false;
		if (isdigit(str[i]))
			isPrevADigit = true;
		else
			isPrevADigit = false;
	}

	// check for wrong signs syntax
	isPrevADigit = false;
	DeleteSpaces(str);
	for (size_t i = 0; i < str.length(); i++) {
		if ((str[i] == '*' || str[i] == '/' || str[i] == '+') && !isPrevADigit)
			return false;
		if (isdigit(str[i]))
			isPrevADigit = true;
		else
			isPrevADigit = false;
	}
	if (!isdigit(str[str.length() - 1]))
		return false;

	return true;
}
// Gets first signed entering number in
// given string
int GetNextInteger(std::string str) {
	std::string temp = "";
	std::string t;
	size_t i = 0;
	/*if (str[i] == '-') {
			i++;
			temp += '-';
	}*/

	if (str[0] == '-')
		return (-1) * GetNextInteger(str.substr(1));
	for (; isdigit(str[i]); i++) {
		temp += str[i];
	}
	return std::stoi(temp);
}
// Evaluate given arithmetic expression
int ParseArithmeticEspression(std::string str) {
	std::string numA = "0";
	int temp;
	size_t len = str.length();
	for (size_t i = 0; i < len; i++) {
		switch (str[i]) {
		case '+':
			return std::stoi(numA) + ParseArithmeticEspression(str.substr(i + 1));
		case '-':
			temp = GetNextInteger(str.substr(i + 1));
			return std::stoi(numA) - temp +
				ParseArithmeticEspression(
					str.substr(i + std::to_string(temp).length() + 1));
		case '*':
			temp = GetNextInteger(str.substr(i + 1));
			numA = std::to_string(std::stoi(numA) * temp);
			i += std::to_string(temp).length();
			break;
		case '/':
			temp = GetNextInteger(str.substr(i + 1));
			if (temp == 0)
				throw(std::logic_error("ERROR : Division by zero "));
			else
				numA = std::to_string(std::stoi(numA) / temp);
			i += std::to_string(temp).length();
			break;
		default:
			numA += str[i];
		}
	}
	return std::stoi(numA);
}
