#include <stdexcept>
#include <string>
#include <algorithm>

// Simplify double negation and sum with negative
void SimplifyMinuses(std::string& str) {
	for (size_t i = str.find("--"); i != std::string::npos; i = str.find("--")) {
		str.replace(i, 2, "+");
	}
	for (size_t i = str.find("+-"); i != std::string::npos; i = str.find("+-")) {
		str.replace(i, 2, "-");
	}
	for (size_t i = str.find("++"); i != std::string::npos; i = str.find("++")) {
		str.replace(i, 2, "+");
	}
}

// Removes all whitespaces in string
void DeleteSpaces(std::string& str) {
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
int GetNextInteger(const std::string& str) {
	std::string temp = "";
	std::string t;
	size_t i = 0;

	if (str[0] == '-')
		return (-1) * GetNextInteger(str.substr(1));
	for (; isdigit(str[i]); i++) {
		temp += str[i];
	}
	return std::stoi(temp);
}
// Evaluate given arithmetic expression
int ParseArithmeticEspression(const std::string & str, std::string StartNum = "0") {

	int temp;
	size_t len = str.length();
	for (size_t i = 0; i < len; i++) {
		switch (str[i]) {
		case '+':
			return std::stoi(StartNum) + ParseArithmeticEspression(str.substr(i + 1));
		case '-':
			temp = -GetNextInteger(str.substr(i+1));
			return std::stoi(StartNum) + ParseArithmeticEspression(str.substr(i +std::to_string(temp).length()),
									       std::to_string(temp));
		case '*':
			temp = GetNextInteger(str.substr(i + 1));
			StartNum = std::to_string(std::stoi(StartNum) * temp);
			i += std::to_string(temp).length();
			break;
		case '/':
			temp = GetNextInteger(str.substr(i + 1));
			if (temp == 0)
				throw(std::logic_error("ERROR : Division by zero "));
			else
				StartNum = std::to_string(std::stoi(StartNum) / temp);
			i += std::to_string(temp).length();
			break;
		default:
			StartNum += str[i];
		}
	}
	return std::stoi(StartNum);
}

