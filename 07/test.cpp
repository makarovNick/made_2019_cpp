#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "format.h"

#include <ostream>

namespace
{
struct A
{
    friend std::ostream& operator<<(std::ostream& os, A& a)
    {
        os << "YEA";
    }
};
}

SCENARIO("Unformatted string") 
{
	GIVEN("OK expression") 
    {
		WHEN("No args") 
        {
			THEN("OK") 
            {
				REQUIRE(format("hello i'm a Man") == "hello i'm a Man");
            }
		}
        WHEN("Primitive args") 
        {
			THEN("OK") 
            {
				REQUIRE(format("hello i'm a {0}", "Man") == "hello i'm a Man");
            }
            THEN("OK") 
            {
				REQUIRE(format("hello i'm a {0}", 12) == "hello i'm a 12");
            }
            THEN("OK") 
            {
				REQUIRE(format("hello i'm a {0}, {1}", "Man", 12) == "hello i'm a Man, 12");
            }
		}
        WHEN("Object args") 
        {
			THEN("OK") 
            {
                A a;
				REQUIRE(format("hello i'm a {0}", a) == "hello i'm a YEA");
            }
		}
	}
    GIVEN("Wrong expression") 
    {
		WHEN("Missed { / }")
        {
			THEN("Throws") 
            {
				REQUIRE_THROWS(format("hello  } hi"));
            }
            THEN("Throws") 
            {
				REQUIRE_THROWS(format("hello { hi"));
            }
		}
        WHEN("Wrong index")
        {
			THEN("Throws") 
            {
				REQUIRE_THROWS(format("hello {0} {1}", 1));
            }
            THEN("Throws") 
            {
				REQUIRE_THROWS(format("hello {10}", 12));
            }
                        THEN("Throws") 
            {
				REQUIRE_THROWS(format("hello {hi}", 12));
            }
		}
	}
}