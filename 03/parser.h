#pragma once
#include <string>
#include <vector>

//class contains two vectors of tokens :
//str_tokens and num_tokens
//in constructor as arguments it gets functions
//that will be used in parsing in class method parser::parse(...)
// - startFunc gets current string to parse and got called at beginning
// - endFunc gets both vectors of token and got called at end
// - numToken gets uint64_t token and got called if it was parsed 
// - strToken gets string token and got called if it was parsed 
// only availible method is parse(...), that extract
// tokens from string if any
class parser
{
	using startFunc = void (*)(const std::string& str);
	using strToken = void (*)(const std::string& token);
	using numToken = void (*)(const uint64_t& token);
	using endFunc = void (*)(std::vector<std::string>& st, std::vector<uint64_t>& nt);

private:

	startFunc onRun;
	endFunc onEnd;
	strToken strTok;
	numToken numTok;

	std::vector<std::string> str_tokens;
	std::vector<uint64_t> num_tokens;

public:

	parser(startFunc start, numToken onNumCallback, strToken onStrCallback, endFunc end);
	parser(numToken onNumCallback, strToken onStrCallback);
	parser(startFunc start, endFunc end);
	parser(numToken onNumCallback);
	parser(strToken onStrCallback);
	parser();
	
	~parser();

	void parseString(const std::string& str);
	std::vector<uint64_t> getNumTokens()const;
	std::vector<std::string> getStrTokens()const;

	void setStartFunction(startFunc start);
	void setEndFunction(endFunc end);
	void setOnStrFunction(strToken str);
	void setOnNumFunction(numToken num);
};
