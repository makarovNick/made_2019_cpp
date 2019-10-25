#include "parser.h"

parser::parser(const startFunc & start, const numToken& onNumCallback, const strToken& onStrCallback, const endFunc& end) :
	onRun(start),
	onEnd(end),
	strTok(onStrCallback),
	numTok(onNumCallback)
{
}
parser::parser(const numToken& onNumCallback, const strToken& onStrCallback) :
	strTok(onStrCallback),
	numTok(onNumCallback)
{
}
parser::parser(const startFunc& start, const endFunc& end) :
	onRun(start),
	onEnd(end)
{
}
parser::parser(const numToken& onNumCallback) :
	numTok(onNumCallback)
{
}
parser::parser(const strToken& onStrCallback) :
	strTok(onStrCallback)
{
}
void parser::setStartFunction(const startFunc& start)
{
	onRun = start;
}
void parser::setEndFunction(const endFunc& end)
{
	onEnd = end;
}
void parser::setOnStrFunction(const strToken& str)
{
	strTok = str;
}
void parser::setOnNumFunction(const numToken& num)
{
	numTok = num;
}
void parser::parseString(const std::string& str)
{
	str_tokens.clear();
	num_tokens.clear();
	if (onRun != nullptr)
		onRun(str);
	std::string currentToken;
	bool isNum = true;
	for (auto& c : str)
	{
		// skips spaces, fill temp string
		// and then push to vector 
		if (!isspace(static_cast<unsigned char>(c)))
		{
			currentToken.push_back(c);
			if (!isdigit(c))
			{
				isNum = false;
			}
		}
		else
		{
			if (!currentToken.empty())
			{
				if (isNum)
				{
					uint64_t temp = std::stoull(currentToken);
					if (numTok != nullptr)
						numTok(temp);
					num_tokens.push_back(temp);
				}
				else
				{
					if (strTok != nullptr)
						strTok(currentToken);
					str_tokens.push_back(currentToken);
				}
				isNum = true;
				currentToken.clear();
			}
		}
	}
        //Checks for last token
	if (!currentToken.empty())
	{
		if (isNum)
		{
			if (numTok != nullptr)
				numTok(std::stoull(currentToken));
			num_tokens.push_back(std::stoull(currentToken));
		}
		else
		{
			if (strTok != nullptr)
				strTok(currentToken);
			str_tokens.push_back(currentToken);
		}
		isNum = true;
		currentToken.clear();
	}
	if (onEnd != nullptr)
		onEnd(str_tokens, num_tokens);
}

std::vector<uint64_t> parser::getNumTokens() const
{
	return num_tokens;
}

std::vector<std::string> parser::getStrTokens() const
{
	return str_tokens;
}


