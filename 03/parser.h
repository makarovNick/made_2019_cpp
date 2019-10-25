#pragma once
#include <string>
#include <vector>
#include <functional>

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
	using startFunc = std::function<void(const std::string& str)> ;
	using endFunc = std::function<void(std::vector<std::string>& st, std::vector<uint64_t>& nt)>;
	using strToken = std::function<void(const std::string& token)>;
	using numToken = std::function<void(const uint64_t& token)>;

private:

	startFunc onRun = nullptr;
	endFunc onEnd = nullptr;
	strToken strTok = nullptr;
	numToken numTok = nullptr;

	std::vector<std::string> str_tokens;
	std::vector<uint64_t> num_tokens;

public:

	parser(const startFunc& start, const numToken& onNumCallback, const strToken& onStrCallback, const endFunc& end);
	parser(const numToken& onNumCallback, const strToken& onStrCallback);
	parser(const startFunc& start, const endFunc& end);
	parser(const numToken& onNumCallback);
	parser(const strToken& onStrCallback);
	parser() = default;
	~parser() = default;

	void parseString(const std::string& str);
	std::vector<uint64_t> getNumTokens()const;
	std::vector<std::string> getStrTokens()const;

	void setStartFunction(const startFunc& start);
	void setEndFunction(const endFunc& end);
	void setOnStrFunction(const strToken& str);
	void setOnNumFunction(const numToken& num);
};
