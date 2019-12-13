#include <iostream>
#include <random>
#include <fstream>


int main(int argc, const char *argv[])
{
	unsigned int seed = 42;

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <file name> " << std::endl;;
		return 1;
	}
	std::ifstream file(argv[1], std::fstream::in | std::fstream::binary);

	while (!file.eof())
	{
		uint64_t num;
		file.read((char*)(&num),sizeof(uint64_t));
        
		std::cout<<num<<std::endl;
	}

	return 0;
} 