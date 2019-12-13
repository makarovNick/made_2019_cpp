#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    std::ifstream file("input", std::fstream::in | std::fstream::binary);
    std:;vector<uint64_t> vec;
    std::ofstream o("output2", std::fstream::out | std::fstream::binary);
	while (!file.eof())
	{
		uint64_t num;
		file.read((char*)(&num),sizeof(uint64_t));
        vec.push_back(num);
	}
    std::sort(vec.begin(),vec.end());

    for(auto& i :  vec)
    {
		o.write((char*)(&i),sizeof(uint64_t));
    }


    return 0;
}