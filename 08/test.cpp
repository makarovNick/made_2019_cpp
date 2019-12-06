#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Iterator.h"
#include "vector.h"

SCENARIO("Initializattion tests")
{
	WHEN("OK")
	{
		vector<int> *test;
		THEN("Default")
		{
			REQUIRE_NOTHROW(test = new vector<int>());
			delete test;
		}
		THEN("One arg")
		{
			REQUIRE_NOTHROW(test = new vector<int>(10));
			delete test;
		}
		THEN("Two arg")
		{
			REQUIRE_NOTHROW(test = new vector<int>(10, 2));
			delete test;
		}
		THEN("Copy Assign")
		{
			vector<int> test1 = vector<int>(15,2);
			vector<int> test2;
			REQUIRE_NOTHROW(test2 = test1);
		}
		THEN("Copy")
		{
			vector<int> test1 = vector<int>(15,2);
			REQUIRE_NOTHROW(test = new vector<int>(test1));
			delete test;
		}
		THEN("Move Assign")
		{
			vector<int> test2;
			REQUIRE_NOTHROW(test2 = vector<int>(15,2));
		}
		THEN("Move")
		{
			REQUIRE_NOTHROW(test = new vector<int>(vector<int>(15,2)));
			delete test;
		}
	}
} 
SCENARIO("size/capacity tests + reallocation")
{
	WHEN("OK")
	{
		vector<int> test;
		THEN("empty")
		{
			REQUIRE(test.empty());
		}
		THEN("Default const")
		{
			REQUIRE(test.size() == 0);
			REQUIRE(test.capacity() == 8);
		}
		THEN("Resize")
		{
			test.resize(100);
			REQUIRE(test.size() == 100);
			REQUIRE(test.capacity() == 100);
			test.resize(10);
			REQUIRE(test.size() == 10);
		}
		THEN("Reserve")
		{
			test.reserve(200);
			REQUIRE(test.size() == 0);
			REQUIRE(test.capacity() == 256);
			test.reserve(10);
			REQUIRE(test.size() == 0);
		}
		THEN("pop_back realloc")
		{
			test.resize(32);
			for(size_t i = 0; i < 29; i++)
			{
				test.pop_back();
			}
			REQUIRE(test.capacity() == 8);
		}
	}
}
SCENARIO("Iterator tests")
{
	WHEN("Forward")
	{
		vector<int> test;
		THEN("OK")
		{
			int i = 0;
			for(; i < 10; i ++)
			{
				test.push_back(i);
			}
			i = 0;
			for(auto it = test.begin(); it!=test.end(); it++)
			{
				REQUIRE(*it == i++);
			}
		}
	}
	WHEN("Reverse")
	{
		vector<int> test;
		THEN("OK")
		{
			int i = 0;
			for(; i < 10; i ++)
			{
				test.push_back(i);
			}
			i = 9;
			for(auto it = test.rbegin(); it!=test.rend(); it++)
			{
				REQUIRE(*it == i--);
			}
		}
	}
}
SCENARIO("Operator[] tests")
{
	WHEN("ok index")
	{
		vector<int> test(15);
		THEN("OK")
		{
			for(size_t i =0; i< test.size(); i++)
			{
				test[i]=i;
			}
			for(size_t i =0; i< test.size(); i++)
			{
				REQUIRE(test[i]==i);
			}
		}
	}
	WHEN("wrong index")
	{
		vector<int> test(15);
		THEN("OK")
		{
			REQUIRE_THROWS(test[16]=1);
		}
	}
}