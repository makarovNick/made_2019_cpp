#include "parser.h"

parser::parser(startFunc start, numToken onNumCallback, strToken onStrCallback, endFunc end) :
	onRun(start),
	onEnd(end),
	strTok(onStrCallback),
	numTok(onNumCallback)
{}
parser::parser(numToken onNumCallback, strToken onStrCallback) :
	onRun(nullptr),
	onEnd(nullptr),
	strTok(onStrCallback),
	numTok(onNumCallback)
{}
parser::parser(startFunc start, endFunc end) :
	onRun(start),
	onEnd(end),
	strTok(nullptr),
	numTok(nullptr)
{}
parser::parser(numToken onNumCallback) :
	onRun(nullptr),
	onEnd(nullptr),
	strTok(nullptr),
	numTok(onNumCallback)
{}
parser::parser(strToken onStrCallback) :
	onRun(nullptr),
	onEnd(nullptr),
	strTok(onStrCallback),
	numTok(nullptr)
{}
parser::parser() :
	onRun(nullptr),
	onEnd(nullptr),
	strTok(nullptr),
	numTok(nullptr)
{}

parser::~parser()
{
	num_tokens.clear();
	str_tokens.clear();
	startFunc onRun = nullptr;
	endFunc onEnd = nullptr;
	strToken strTok = nullptr;
	numToken numTok = nullptr;
}
void parser::setStartFunction(startFunc start)
{
	onRun = start;
}
void parser::setEndFunction(endFunc end)
{
	onEnd = end;
}
void parser::setOnStrFunction(strToken str)
{
	strTok = str;
}
void parser::setOnNumFunction(numToken num)
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
		}
	}
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


