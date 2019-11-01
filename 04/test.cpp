#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Matrix.h"

SCENARIO("Initialiation tests") 
{
	GIVEN("Rows and columns size") 
	{
		WHEN("Correct sizes") 
		{
			Matrix *m;
			THEN("OK")
			{
				REQUIRE_NOTHROW(m = new Matrix(10, 10));
				delete m;
			}
			THEN("OK")
			{
				REQUIRE_NOTHROW(m = new Matrix(1, 999999));
				delete m;
			}
		}
		WHEN("Wrong sizes")
		{
			Matrix* m;
			THEN("NOT OK")
			{
				REQUIRE_THROWS(m = new Matrix(0, 0));
				delete m;
			}
			THEN("NOT OK")
			{
				REQUIRE_THROWS(m = new Matrix(0, 999999));
				delete m;
			}
		}
	}
}
SCENARIO("Memort access tests")
{
	GIVEN("indexes and value")
	{
		WHEN("Correct indexes")
		{
			Matrix m(10, 10);
			THEN("OK")
			{
				for (size_t i = 0; i < 10; i++)
				{
					for (size_t j = 0; j < 10; j++)
					{
						REQUIRE(m[i][j] == 0);
					}
				}
			}
			THEN("OK")
			{
				REQUIRE_NOTHROW(m[0][0] = 0);
				REQUIRE_NOTHROW(m[9][5] = 0);
				REQUIRE_NOTHROW(m[0][4] = 0);
				REQUIRE_NOTHROW(m[8][7] = 0);
				REQUIRE(m[0][0] == 0);
				REQUIRE(m[9][5] == 0);
				REQUIRE(m[0][4] == 0);
				REQUIRE(m[8][7] == 0);
			}
		}
		WHEN("Out of boundes indexes")
		{
			Matrix m(10, 10);
			THEN("NOT OK")
			{
				REQUIRE_THROWS(m[10][2] = 10 );
			}
			THEN("NOT OK")
			{
				REQUIRE_THROWS(m[100][100] = 15);
			}
		}
	}
}
SCENARIO("Compare tests")
{
	GIVEN("Two matrix")
	{
		WHEN("Equal")
		{
			Matrix m(10, 10);
			Matrix n(10, 10);
			THEN("OK")
			{
				REQUIRE(m == n);
			}
			THEN("OK")
			{
				m[9][2] = 2;
				n[9][2] = 2;
				REQUIRE(m == n);
			}
		}
		WHEN("Not equal")
		{
			Matrix m(10, 10);
			Matrix c(9, 10);
			Matrix n(10, 10);
			THEN("OK")
			{
				REQUIRE(m != c);
			}
			THEN("OK")
			{
				m[9][9] = 999;
				REQUIRE(m != n);
			}
		}
	}
}

SCENARIO("Multiplication tests")
{
	GIVEN("Matrix and value")
	{
		WHEN("OK")
		{
			Matrix m(10, 10);
			for (size_t i = 0; i < 10; i++)
			{
				for (size_t j = 0; j < 10; j++)
				{
					m[i][j] = i*j;
				}
			}
			THEN("OK")
			{
				m *= 9;
				for (size_t i = 0; i < 10; i++)
				{
					for (size_t j = 0; j < 10; j++)
					{
						REQUIRE(m[i][j] == i * j * 9);
					}
				}
			}
			for (size_t i = 0; i < 10; i++)
			{
				for (size_t j = 0; j < 10; j++)
				{
					m[i][j] = 1;
				}
			}
			THEN("OK")
			{
				m *= 0;
				for (size_t i = 0; i < 10; i++)
				{
					for (size_t j = 0; j < 10; j++)
					{
						REQUIRE(m[i][j] == 0);
					}
				}
			}
		}
	}
}
