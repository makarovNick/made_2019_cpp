#include <iostream>
#include <string>
#include <algorithm>

void DeleteSpaces(std::string& str);
bool CheckString(std::string str);
int ParseArithmeticEspression(std::string str);

int main() {
	std::string a = "24   +			12";
	DeleteSpaces(a);
	std::cout << a;
}
void inline DeleteSpaces(std::string& str) {
	str.erase(std::remove(str.begin(), str.end(), ' '),str.end());
}
// Checks for missing signs or unintentionall space "2*4  3+4"
// or wrong symbols
bool CheckString(std::string str) {
	std::string alphavite = "1234567890+-*/ ";
	bool isPrevADigit = false;
	size_t len = str.length();

	for (size_t i = 0; i < len; ++i) {
		if (isPrevADigit && (i + 1) < len && str[i] == ' ' && isdigit(str[i + 1]) ||
			alphavite.find(str[i]) == std::string::npos)
			return false;
		if (isdigit(str[i]))
			isPrevADigit = true;
		else
			isPrevADigit = false;
	}
	return true;
}
int GetNextInteger(std::string str) {
	std::string temp = "";
	size_t i = 0;
	if (str[i] == '-') {
		i++;
		temp += '-';
	}
	for (; isdigit(str[i]); i++) {
		temp += str[i];
	}
	return std::stoi(temp);
}
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
			numA = std::to_string(std::stoi(numA) / temp);
			i += std::to_string(temp).length();
			break;
		default:
			numA += str[i];
		}
	}
	return std::stoi(numA);
}
