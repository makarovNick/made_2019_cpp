#define CATCH_CONFIG_MAIN
#include "main.h"
#include "catch.hpp"
// https://github.com/catchorg/Catch2/tree/master/docs
SCENARIO("Delete spaces tests") {
	GIVEN("Any expression") {
		std::string test_str;
		WHEN("Simple string with single spaces") {
			test_str = "10 + 6 * -1 / 5 - -2";
			DeleteSpaces(test_str);
			THEN("Spaces removed") { REQUIRE(test_str == "10+6*-1/5--2"); }
			test_str = "13 - 2 / 2 - 17 +1000 ";
			DeleteSpaces(test_str);
			THEN("Spaces removed") { REQUIRE(test_str == "13-2/2-17+1000"); }
		}
		WHEN("Multyple spaces") {
			test_str = "    11 - 224        * 8 - 123 / 34  + 0 -  - - 4 +2";
			DeleteSpaces(test_str);
			THEN("Spaces removed") { REQUIRE(test_str == "11-224*8-123/34+0---4+2"); }
			test_str = "    8 *   9     /2  *11 - 12 +  2 - -2 * 3 ";
			DeleteSpaces(test_str);
			THEN("Spaces removed") { REQUIRE(test_str == "8*9/2*11-12+2--2*3"); }
		}
		WHEN("Tabs appearence") {
			test_str =
				"17		+ 4 - 3		* 2		-4444 *		9		/3";
			DeleteSpaces(test_str);
			THEN("Spaces removed") { REQUIRE(test_str == "17+4-3*2-4444*9/3"); }
			test_str =
				"	7 -9		*2	/2	*	-	2	*11/123";
			DeleteSpaces(test_str);
			THEN("Spaces removed") { REQUIRE(test_str == "7-9*2/2*-2*11/123"); }
		}
	}
}
SCENARIO("Check expression syntax") {
	GIVEN("Any expression") {
		std::string test_str;
		WHEN("Simple correct expression") {
			test_str = "10 + 6 * -1 / 5 - -2";
			THEN("Correct expression") { REQUIRE(CheckString(test_str)); }
			test_str = "7-9*2/2*-2*11/123 ";
			THEN("Correct expression") { REQUIRE(CheckString(test_str)); }
		}
		WHEN("Wrong expressions") {
			test_str = "11 - 2 24 * 8 - 12 3 / 34 + 0 - - - 4 + 2";
			THEN("Missed opperation signs") { REQUIRE_FALSE(CheckString(test_str)); }
			test_str = "  hello  8 *   9     /2  *11 - 12 +  2 - -2 * 3 ";
			THEN("Forbidden symbols appeares") {
				REQUIRE_FALSE(CheckString(test_str));
			}
			test_str = " /12+5 *2 - -1 * 2 ";
			THEN("Wrong opperation signs use") {
				REQUIRE_FALSE(CheckString(test_str));
			}
		}
	}
}
SCENARIO("Simplification tests") {
	GIVEN("Any expression") {
		std::string test_str;
		WHEN("Double negation to positiveness") {
			test_str = "7--9--9";
			SimplifyMinuses(test_str);
			THEN("Simplified expression") { REQUIRE(test_str == "7+9+9"); }
			test_str = "12--1*2/2+4--1";
			SimplifyMinuses(test_str);
			THEN("Simplified expression") { REQUIRE(test_str == "12+1*2/2+4+1"); }
		}
		WHEN("Addition with negative to subtraction") {
			test_str = "12*3+-123+-4";
			SimplifyMinuses(test_str);
			THEN("Simplified expression") { REQUIRE(test_str == "12*3-123-4"); }
			test_str = "228+-12*2*3-3+-442";
			SimplifyMinuses(test_str);
			THEN("Simplified expression") { REQUIRE(test_str == "228-12*2*3-3-442"); }
		}
		WHEN("Multyple minuses fold") {
			test_str = "-----------2";
			SimplifyMinuses(test_str);
			THEN("Simplified expression") { REQUIRE(test_str == "-2"); }
			test_str = "----------------------3";
			SimplifyMinuses(test_str);
			THEN("Simplified expression") { REQUIRE(test_str == "+3"); }
		}
	}
}
SCENARIO("Evaluating parser") {
	GIVEN("Any expression") {
		std::string test_str;
		WHEN("Simple addition") {
			test_str = "9+9";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == 18);
			}
			test_str = "3000+3000+3000";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == 9000);
			}
		}
		WHEN("Simple subtraction") {
			test_str = "-9-9";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == -18);
			}
			test_str = "-500-500-500";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == -1500);
			}
		}
		WHEN("Simple multiplication") {
			test_str = "10*16";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == 160);
			}
			test_str = "3*3*3*3*3*2";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == 486);
			}
		}
		WHEN("Simple division") {
			test_str = "180/3";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == 60);
			}
			test_str = "256/2/2/2/2/2/2/2/2";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == 1);
			}
			test_str = "1/2";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == 0);
			}
		}
		WHEN("Composite expression") {
			test_str = "123123*233/123+4-1212*-1+3------12312/2 + 4";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == 245496);
			}
			test_str = "521*2112/1/1/1/1/1/1/2/1/1/1*-1*222";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == -122139072);
			}
			test_str =
				"123+3123+123+123+3123--123123--123123--132123*123*213/3/2-100000";
			THEN("Evaluated expression") {
				REQUIRE(ParseArithmeticEspression(test_str) == 284984);
			}
		}
	}
}
SCENARIO("Handling exception tests") {
	GIVEN("Wrong expression") {
		std::string test_str;
		WHEN("Division by zero") {
			test_str = "9/0";
			THEN("Handled exception") {
				REQUIRE_THROWS(ParseArithmeticEspression(test_str));
			}

		}
	}
}
