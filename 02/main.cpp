#include "allocator.h"

#include <iostream>
#include <chrono>

using Clock=std::chrono::high_resolution_clock; 
using microseconds=std::chrono::microseconds;

//time comparison of simple linear allocator with std::malloc()
//on different types of memoty allocation

struct testStruct {
	int a;
	char b[100];
	long long c;
	testStruct* pointer;
};

int main() 
{
	std::cout << "==========================================================================" << std::endl;
	std::cout << "    1000 int arrays length of 100 " << std::endl << std::endl;

	auto start = Clock::now();

	for (size_t i = 0; i < 1000; i++)
	{
		int* array = (int*) malloc(sizeof(int) * 100);
		free(array);
	}

	auto duration = std::chrono::duration_cast<microseconds>(Clock::now() - start).count();

	std::cout << "    malloc() result:        " << duration << " us" << std::endl << std::endl;

	start = Clock::now();

	LinearAllocator allocator(sizeof(int) * 100 * 1000);
	for (size_t i = 0; i < 1000; i++)
	{
		int*  array1 = (int*)allocator.alloc(sizeof(int) * 100);
	}
	allocator.reset();

	duration = std::chrono::duration_cast<microseconds>(Clock::now() - start).count();

	std::cout << "    linear allocator result: " << duration << " us" << std::endl << std::endl;

	
	
	std::cout << "==========================================================================" << std::endl;
	std::cout << "    1 char array length of 1000000 " << std::endl << std::endl;

	start = Clock::now();

	char* array = (char*)malloc(sizeof(char) * 1000000);
	free(array);

	duration = std::chrono::duration_cast<microseconds>(Clock::now() - start).count();

	std::cout << "    malloc() result: " << duration << " us" << std::endl << std::endl;

	start = Clock::now();

	LinearAllocator allocator2(sizeof(char)* 1000000);
	char* array1 = (char*)allocator2.alloc(sizeof(char) * 1000000);
	allocator2.reset();

	duration = std::chrono::duration_cast<microseconds>(Clock::now() - start).count();


	std::cout << "    linear allocator result: " << duration << " us" << std::endl << std::endl;

	
	
	std::cout << "==========================================================================" << std::endl;
	std::cout << "    1000 arrays of composite structures length of 1000" <<std::endl<< std::endl;

	start = Clock::now();
	for (size_t i = 0; i < 1000; i++)
	{
		testStruct* array = (testStruct*)malloc(sizeof(testStruct) * 1000);
		free(array);
	}

	duration = std::chrono::duration_cast<microseconds>(Clock::now() - start).count();

	std::cout << "    malloc() result: " << duration << " us" << std::endl << std::endl;

	start = Clock::now();

	LinearAllocator allocator3(sizeof(testStruct) * 1000 * 1000);
	for (size_t i = 0; i < 1000; i++)
	{
		testStruct* array1 = (testStruct*)allocator3.alloc(sizeof(testStruct) * 1000);
	}
	allocator3.reset();

	duration = std::chrono::duration_cast<microseconds>(Clock::now() - start).count();

	std::cout << "    linear allocator result: " << duration << " us" << std::endl << std::endl;


	return 0;
}
