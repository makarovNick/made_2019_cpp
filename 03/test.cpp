#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "parser.h"

SCENARIO("Constructor tests")
{
	GIVEN("Some constructor") 
	{
		WHEN("Correct constructor")
		{
			parser* pr;
			THEN("OK") 
			{
				REQUIRE_NOTHROW( pr = new parser());
				delete pr;
			}
			THEN("OK"){
				auto func = [](const std::string& str) {};
				REQUIRE_NOTHROW( pr = new parser(func));
                                delete pr;
			}
			THEN("OK")
			{
                                auto func = [](const uint64_t& num) {};
                                REQUIRE_NOTHROW( pr = new parser(func));
				delete pr;
			}
                        THEN("OK")
			{
				auto func1 = [](const uint64_t& num) {};
                                auto func = [](const std::string& str) {};
                                REQUIRE_NOTHROW( pr = new parser(func1, func));
                                delete pr;
                        }
                        THEN("OK")
			{
                                auto func1 = [](std::vector<std::string>& st, std::vector<uint64_t>& nt) {};
                                auto func = [](const std::string& str) {};
                                REQUIRE_NOTHROW( pr = new parser(func, func1));
                                delete pr;
			}
                        THEN("OK")
			{
                                auto func1 = [](std::vector<std::string>& st, std::vector<uint64_t>& nt) {};
                                auto func2 = [](const uint64_t& n) {};
                                auto func4 = [](const std::string& str) {};
                                REQUIRE_NOTHROW( pr = new parser(func4, func2, func4, func1));
                                delete pr;
                        }

		}
	}
}

SCENARIO("Setters tests") 
{
        GIVEN("Some functions") 
	{
                WHEN("Correct setters") 
		{
			auto func1 = [](std::vector<std::string>& st, std::vector<uint64_t>& nt) {};
			auto func2 = [](const uint64_t& n) {};
			auto func4 = [](const std::string& str) {};
			parser * pr = new parser();
			THEN("OK")
			{
				REQUIRE_NOTHROW( pr->setStartFunction(func4));
			}
                        THEN("OK")
			{
                                REQUIRE_NOTHROW( pr->setEndFunction(func1));
                        }
                        THEN("OK")
			{
                                REQUIRE_NOTHROW( pr->setOnStrFunction(func4));
                        }
                        THEN("OK")
			{
                                REQUIRE_NOTHROW( pr->setOnNumFunction(func2));
                        }
		}
	}
}

SCENARIO("Parsing tests") 
{
        GIVEN("Some string") 
	{
                WHEN("String tokens") 
		{
			parser *pr = new parser();
                        THEN("OK")
			{
	                        const std::string str1 = "hello hi 0001a yea000z privet         bye yep";
                                pr->parseString(str1);
                        	std::vector<std::string> strs = pr->getStrTokens();
				REQUIRE(strs[0] == "hello");
                                REQUIRE(strs[1] == "hi");
                                REQUIRE(strs[2] == "0001a");
                                REQUIRE(strs[3] == "yea000z");
                                REQUIRE(strs[4] == "privet");
                                REQUIRE(strs[5] == "bye");
                                REQUIRE(strs[6] == "yep");
			}

                        THEN("OK")
                        {
	                        const std::string str1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
                                pr->parseString(str1);
                                std::vector<std::string> strs = pr->getStrTokens();
                                REQUIRE(strs[0] == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
                        }
			delete pr;
                }
                WHEN("Numereal tokens") 
                {
                        parser *pr = new parser();
                        THEN("OK")
                        {
                                const std::string str1 = "999 0002 123    32 929";
                                pr->parseString(str1);
                                std::vector< uint64_t > ns = pr->getNumTokens();
                                REQUIRE(ns[0] == 999);
                                REQUIRE(ns[1] == 2);
                                REQUIRE(ns[2] == 123);
                                REQUIRE(ns[3] == 32);
                                REQUIRE(ns[4] == 929);
			}
                        THEN("OK")
                        {
                                const std::string str1 = "   999999999999 ";
                                pr->parseString(str1);
                                std::vector< uint64_t > n = pr->getNumTokens();
                                REQUIRE( n[0] == 999999999999);
			}
			delete pr;
		}
                WHEN("String and Numeral tokens") 
                {
			parser *pr = new parser();
                        THEN("OK")
                        {
                                const std::string str1 = " hhhh 123 aweaw e123 ads 0002 asd as 000 0";
                                pr->parseString(str1);
                                std::vector< uint64_t > nums = pr->getNumTokens();
                                std::vector<std::string> strs = pr->getStrTokens();
                                REQUIRE(strs[0] == "hhhh");
                                REQUIRE(strs[1] == "aweaw");
                                REQUIRE(strs[2] == "e123");
                                REQUIRE(strs[3] == "ads");
                                REQUIRE(strs[4] == "asd");
                                REQUIRE(strs[5] == "as");
                                REQUIRE(nums[0] == 123);
                                REQUIRE(nums[1] == 2);
                                REQUIRE(nums[2] == 0);
                                REQUIRE(nums[3] == 0);
			}
		}
        }
}

