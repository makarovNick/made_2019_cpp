#include <iostream>
#include <random>
#include <fstream>


int main(int argc, const char *argv[])
{
	unsigned int seed = 42;

	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " <file name> <number of ints> [random seed]" << std::endl;;
		return 1;
	}
	std::ofstream file(argv[1], std::fstream::out | std::fstream::binary);

	size_t n = strtol(argv[2], NULL, 0);

	if (argc == 4)
	{
		seed = strtol(argv[3], NULL, 0);
	}

	std::default_random_engine generator;
	generator.seed(seed);
	std::uniform_int_distribution<uint64_t> distribution(1, UINT64_MAX);
	while (n--)
	{
		uint64_t num = distribution(generator);
		file.write((char*)(&num),sizeof(uint64_t));
		//std::cout<<num<<std::endl;
	}

	return 0;
} 