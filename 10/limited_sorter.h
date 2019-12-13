#include <functional>
#include <atomic>
#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include  <algorithm>

//#define pr(a) std::cout<<a<<std::endl

class Sorter
{
public:
    Sorter(const std::string& inpu, const std::string& output, size_t mem = 1024 * 1024 * 8);

    std::string Sort();

private:
    void process();

    void addToQueue(const std::vector<uint64_t>& block);
    void foldQueue();

    void writeBlock(const std::vector<uint64_t>& block, const std::string& file_name);

    std::string mergeFiles(std::string& a, std::string& b);

    std::vector<uint64_t> readBlock();
    std::vector<uint64_t> readBlock(const std::string& file);
    
    std::ifstream input;
    std::ofstream output;

    //needed to various temp files ( in case of rewritting)
    std::atomic<int> num_blocks;

    std::queue<std::string> temp_parts;

    size_t AVAILIBLE_MEMORY;
    size_t input_lenght;

    std::mutex input_mutex;
    std::mutex queue_mutex;
};