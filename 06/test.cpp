#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "BigInt.h"

#include <sstream>

namespace test
{
	using std::string;
	using std::stringstream;
}

SCENARIO("Initializattion tests")
{
	WHEN("OK format")
	{
		BigInt bigint;
		BigInt another = 2;
		THEN("OK")
		{
			REQUIRE_NOTHROW(bigint = BigInt(13478235));
			REQUIRE_NOTHROW(bigint = BigInt(-1241324132));
			REQUIRE_NOTHROW(bigint = BigInt("12434324231324324234"));
			REQUIRE_NOTHROW(bigint = BigInt(test::string("918473014")));
			REQUIRE_NOTHROW(another = bigint);

		}
	}
	WHEN("Wrong syntax")
	{
		BigInt bigint;
		THEN("Throws")
		{
			REQUIRE_THROWS(bigint = BigInt("1243432as4324234"));
			REQUIRE_THROWS(bigint = BigInt(test::string("91847ss3014")));
		}
	}
} 

SCENARIO("Comparison tests")
{
	WHEN("G")
	{
		BigInt bigint;
		BigInt another;
		THEN("OK")
		{
			bigint = 100500;
			another = 999999;
			REQUIRE(bigint > 100499);
			REQUIRE_FALSE(bigint > 9999999999999);
			REQUIRE(bigint < another);
		}
	}
	WHEN("L")
	{
		BigInt bigint;
		BigInt another;
		THEN("OK")
		{
			bigint = 100500;
			another = 999999;
			REQUIRE(bigint < 100501);
			REQUIRE_FALSE(bigint < 999);
			REQUIRE(bigint < another);
		}
	}
	WHEN("GE")
	{
		BigInt bigint;
		BigInt another;
		THEN("OK")
		{
			bigint = 100501;
			another = 9999;
			REQUIRE(bigint >= 123);
			REQUIRE(bigint >= 100501);
			REQUIRE_FALSE(bigint >= 3333333);
			REQUIRE(bigint >= another);
		}
	}
	WHEN("LE")
	{
		BigInt bigint;
		BigInt another;
		THEN("OK")
		{
			bigint = 100500;
			another = 999999;
			REQUIRE(bigint <= 100501);
			REQUIRE(bigint <= 100500);
			REQUIRE_FALSE(bigint <= 100499);
			REQUIRE(bigint <= another);
		}
	}
	WHEN("E")
	{
		BigInt bigint;
		BigInt another;
		THEN("OK")
		{
			bigint = 100500;
			another = 100500;
			REQUIRE(bigint == 100500);
			REQUIRE_FALSE(bigint == 123);
			REQUIRE(bigint == another);
		}
	}
	WHEN("NE")
	{
		BigInt bigint;
		BigInt another;
		THEN("OK")
		{
			bigint = 100500;
			another = 123123123;
			REQUIRE(bigint != 3123);
			REQUIRE_FALSE(bigint != 100500);
			REQUIRE(bigint != another);
		}
	}
}
SCENARIO("Sum tests")
{
	WHEN("int64_t test")
	{
		BigInt bigint;
		THEN("OK")
		{
			bigint = "10";
			REQUIRE(bigint + 999 == 1009);
			REQUIRE(bigint + (-100) == -90);
			REQUIRE(0 + bigint == 10);
			REQUIRE(bigint + 2 == 12);
		}
	}
	WHEN("BigInt test")
	{
		BigInt bigint;
		BigInt another;
		THEN("OK")
		{
			bigint = "99999999999999999999999999999999";
			another = "-23574363254523453426583876734";
			BigInt res("99976425636745476546573416123265");
			REQUIRE(bigint + another == res);
		}
		THEN("OK")
		{
			bigint = "56789876567890";
			another = "540345340500034";
			BigInt res = "597135217067924";
			REQUIRE(bigint + another == res);
		}
	}
}

SCENARIO("Sub tests")
{
	WHEN("int64_t test")
	{
		BigInt bigint;
		THEN("OK")
		{
			bigint = 10;
			REQUIRE(bigint - 999 == -989);
			REQUIRE(bigint - (-100) == 110);
			REQUIRE(0 - bigint == -10);
			REQUIRE(bigint - 2 == 8);
		}
	}
	WHEN("BigInt test")
	{
		BigInt bigint;
		BigInt another;
		THEN("OK")
		{
			bigint = "99999999999999999999999999999999";
			another = "-23574363254523453426583876734";
			BigInt res("99976425636745476546573416123265");
			REQUIRE(bigint + another == res);
		}
		THEN("OK")
		{
			bigint = "45678912498765126472000012";
			another = "143242342341999";
			BigInt res = "45678912498908368814342011";
			REQUIRE(bigint + another == res);
		}
	}
}
SCENARIO("Unary tests")
{
	WHEN("BigInt test")
	{
		BigInt bigint;
		BigInt another;
		THEN("OK")
		{
			bigint = "99999999999999999999999999999999";
			another = "-99999999999999999999999999999999";
			REQUIRE((-bigint) == another);
		}
		THEN("OK")
		{
			bigint = "0";
			another = "0";
			REQUIRE(-bigint == another);
		}
	}
}
SCENARIO("Stream tests")
{
	WHEN("BigInt test")
	{
		BigInt bigint;
		BigInt another;
		THEN("OK")
		{
			test::stringstream s;
			bigint = "99999999999999999999999999999999";
			s << bigint;
			REQUIRE(s.str() == "99999999999999999999999999999999");
		}
		THEN("OK")
		{
			test::stringstream s;
			bigint = "-1243";
			s << bigint;
			REQUIRE(s.str() == "-1243");
		}
	}
}
