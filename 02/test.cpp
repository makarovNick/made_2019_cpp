#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "allocator.h"

SCENARIO("Initializaion tests") {
	GIVEN("Allocation max size") {
		WHEN("size is ok") {
			LinearAllocator *alloc;
			THEN("OK") {
				REQUIRE_NOTHROW(alloc = new LinearAllocator(100 * sizeof(int)));
			}
			THEN("OK") {
				REQUIRE_NOTHROW(alloc = new LinearAllocator(4294967293));
			}
		}
		WHEN("size is not ok") {
			LinearAllocator* alloc2;
			//THEN("size is too large") {
			//	REQUIRE_THROWS(alloc2 = new LinearAllocator(4294967295));
			//}
			THEN("0 size") {
				REQUIRE_THROWS(alloc2 = new LinearAllocator(0));
			}
		}
	}
}

SCENARIO("Allocation tests") {
	GIVEN("Allocation size") {
		WHEN("1 alloc") {
			THEN("OK") {
				LinearAllocator alloc3(100 * sizeof(int));
				int* array = (int*)alloc3.alloc(100 * sizeof(int));
				for (size_t i = 0; i < 100; i++)
				{
					array[i] = i;
				}
				for (size_t i = 0; i < 100; i++)
				{
					REQUIRE(array[i] == i);
				}

			}
		}
		WHEN("Multyple allocation") {
			THEN("OK") {
				LinearAllocator alloc4(10000*sizeof(int)+ 100 * sizeof(int**));
				int** array = (int**)alloc4.alloc(sizeof(int*) * 100);
				for (size_t i = 0; i < 100; i++)
				{
					array[i] = (int*)alloc4.alloc(sizeof(int) * 100);
				}
				for (size_t i = 0; i < 100; i++)
				{
					for (size_t j = 0; j < 100; j++)
					{
						array[i][j] = i * j;
					}
				}
				for (size_t i = 0; i < 100; i++)
				{
					for (size_t j = 0; j < 100; j++)
					{
						REQUIRE(array[i][j] == i * j);
					}
				}
			}
		}
	}
}
SCENARIO("Deallocation tests") {
	GIVEN("Allocation size") {
		WHEN("ok dealloc") {
			THEN("OK") {
				LinearAllocator alloc5(100 * sizeof(int));
				int* array = (int*)alloc5.alloc(100 * sizeof(int));
				for (size_t i = 0; i < 100; i++)
				{
					array[i] = i;
				}
				REQUIRE_NOTHROW(alloc5.reset());

			}
		}
		WHEN("failed dealloc") {
			THEN("freed memory free") {
				LinearAllocator alloc6(100);
				int* array = (int*)alloc6.alloc(100 * sizeof(int));
				alloc6.reset();
				REQUIRE_THROWS(alloc6.reset());
			}
			THEN("reset reseted memory") {
				LinearAllocator alloc6(100);
				REQUIRE_THROWS(alloc6.reset());
			}
		}
	}
}
