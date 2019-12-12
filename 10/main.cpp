// #include <functional>
// #include <atomic>
// #include <queue>
// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <thread>
// #include <mutex>
// #include  <algorithm>

// #define pr(a) std::cout<<a<<std::endl

// class Sorter
// {
// public:
//     Sorter(const std::string& input, const std::string& output, size_t mem = 1024 * 1024 * 8)
//         : input(input, std::fstream::binary | std::fstream::in | std::fstream::ate)
//         , output(output, std::fstream::binary | std::fstream::out)
//         , AVAILIBLE_MEMORY(mem)
//         , num_blocks{0}
//     {
//     }

//     std::string Sort()
//     {
//         std::thread thread1([this](){process();});

//         if(inputSize() < AVAILIBLE_MEMORY / (sizeof(uint64_t) * 2))
//         {
//             std::thread thread2([this](){process();});
//             thread2.join();  
//         }

//         thread1.join();

//         auto tmp = temp_parts.front();
//         temp_parts.pop();

//         std::ifstream source(tmp, std::ios::binary | std::fstream::in);

//         std::istreambuf_iterator<char> begin_source(source);
//         std::istreambuf_iterator<char> end_source;
//         std::ostreambuf_iterator<char> begin_dest(output); 
//         std::copy(begin_source, end_source, begin_dest);

//         std::remove(tmp.c_str());

//         return tmp;      
//     }

//     size_t inputSize()
//     {
//         return input.tellg() / sizeof(uint64_t);
//     }

// private:
//     void process()
//     {
//         auto current_block = readBlock();

//         std::sort(current_block.begin(), current_block.end());

//         addToQueue(current_block);
//     }

//     void addToQueue(const std::vector<uint64_t>& block)
//     {
//         std::string new_path = "_temp_" + num_blocks;
//         num_blocks++;
//         writeBlock(block, new_path);
        
//         std::string old_path;
//         {
//             std::unique_lock<std::mutex> lock(queue_mutex);
//             if(temp_parts.size())
//             {
//                 old_path = temp_parts.front();
//                 temp_parts.pop();
//             }

//             pr(old_path);
//             pr(new_path);

//             temp_parts.emplace(mergeFiles(new_path, old_path));
//         }
//     }

//     void foldQueue()
//     {
//         std::unique_lock<std::mutex> lock(queue_mutex);
//         while(temp_parts.size()!=1)
//         {
//             std::string a = temp_parts.front();
//             temp_parts.pop();
//             std::string b = temp_parts.front();
//             temp_parts.pop();
//             temp_parts.emplace(mergeFiles(a, b));
//         }
//     }

//     std::string mergeFiles(std::string& a, std::string& b)
//     {
//         std::string new_path = "_temp_" + int(num_blocks.load());
//         num_blocks ++;

//         if(a.size())
//         {
//             std::remove(a.c_str());
//             return b;
//         }
//         if(b.size())
//         {
//             std::remove(b.c_str());
//             return a;
//         }

//         std::ifstream is_a(a, std::fstream::binary | std::fstream::in);
//         std::ifstream is_b(b, std::fstream::binary | std::fstream::in);
//         std::ofstream os_new(new_path, std::fstream::binary | std::fstream::out);

//         uint64_t value_a;
//         uint64_t value_b;

//         bool flag_a = !is_a.read((char*)( &value_a ), sizeof(uint64_t));;
//         bool flag_b = !is_b.read((char*)( &value_b ), sizeof(uint64_t));;

//         while ( !( flag_a && flag_b ) ) 
//         {
//             if ( !flag_a && !flag_b ) 
//             {
//                 if ( value_a < value_b ) 
//                 {
//                     os_new.write((char*)( &value_a ), sizeof(uint64_t));
//                     flag_a = !is_a.read((char*)( &value_a ), sizeof(uint64_t));;
//                 }
//                 else 
//                 {
//                     os_new.write((char*)( &value_b ), sizeof(uint64_t));
//                     flag_b = !is_b.read((char*)( &value_b ), sizeof(uint64_t));;
//                 }
//             }
//             if ( !flag_a && flag_b ) 
//             {
//                 os_new.write((char*)( &value_a ), sizeof(uint64_t));
//                 flag_a = !is_a.read((char*)( &value_a ), sizeof(uint64_t));;
//             }
//             if ( flag_a && !flag_b ) 
//             {
//                 os_new.write((char*)( &value_b ), sizeof(uint64_t));
//                 flag_b = !is_b.read((char*)( &value_b ), sizeof(uint64_t));;
//             }
//         }

//         pr(a);
//         pr(b);

//         std::remove(a.c_str());
//         std::remove(b.c_str());

//         return new_path;
//     }

//     void writeBlock(const std::vector<uint64_t>& block, const std::string& file_name)
//     {
//         std::ofstream os(file_name, std::ios::binary | std::fstream::out);
//         for (auto& cur_num : block ) 
//         {
//             os.write((char*)( &cur_num ), sizeof(uint64_t));
//         }
//     }

//     std::vector<uint64_t> readBlock()
//     {
//         std::vector<uint64_t> block(AVAILIBLE_MEMORY / (2 * sizeof(uint64_t)));

//         if(!input.eof())
//         {
//             std::lock_guard<std::mutex> lock(input_mutex);
//             for (auto& cur_num : block)
//             {
//                 if(!input.read((char*)(&cur_num), sizeof(uint64_t)))
//                 {
//                     pr(cur_num);
//                     break;
//                 }
//             }
//         }

//         return block;
//     }

//     std::vector<uint64_t> readBlock(const std::string& file)
//     {
//         std::vector<uint64_t> block;
//         std::ifstream is(file, std::fstream::binary | std::fstream::in);

//         uint64_t temp;
//         while(!is.eof())
//         {
//             is.read((char*)&temp, sizeof(uint64_t));
//             block.push_back(temp);
//         }

//         return block;
//     }

//     std::atomic<int> num_blocks;

//     std::queue<std::string> temp_parts;

//     size_t AVAILIBLE_MEMORY;

//     std::mutex input_mutex;
//     std::mutex queue_mutex;

//     std::ifstream input;
//     std::ofstream output;
// };

// int main()
// {
//     Sorter sorter("input", "output");

//     sorter.Sort();

//     std::ifstream is("output", std::fstream::binary | std::fstream::out);

//     uint64_t temp = 0;
//     while(!is.eof())
//     {
//         is.read((char*)&temp, sizeof(uint64_t));
//         std::cout<<temp<<" ";
//     }

//     return 0;
// }