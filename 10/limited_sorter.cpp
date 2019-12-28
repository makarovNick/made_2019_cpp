#include "limited_sorter.h"

std::string Sorter::Sort()
{
    input.seekg(0);

    std::thread thread1([this](){process();});

    if(input_lenght > AVAILIBLE_MEMORY / (sizeof(uint64_t) * 2))
    {
        std::thread thread2([this](){process();});
        thread2.join();  
    }

    thread1.join();

    auto tmp = temp_parts.front();
    temp_parts.pop();

    std::rename(tmp.c_str(), output.c_str());

    return tmp;      
}

Sorter::Sorter(const std::string& inpu, const std::string& output, size_t mem)
    : input(inpu, std::fstream::binary  | std::fstream::out | std::fstream::ate)
    , output(output)
    , AVAILIBLE_MEMORY(mem)
    , num_blocks{0}
    , input_lenght(input.tellg() / sizeof(uint64_t))
{
    input.seekg(0);
}

void Sorter::process()
{
    while(true)
    {
        auto current_block = readBlock();

        std::sort(current_block.begin(), current_block.end());

        addToQueue(current_block);

        {
            std::unique_lock<std::mutex> lock(queue_mutex);    
            if(input.eof())
            {
                break;
            }
        }
    }

    foldQueue();
}

void Sorter::addToQueue(const std::vector<uint64_t>& block)
{
    std::string new_path = "_temp_" + std::to_string(num_blocks) + ".bin";
    num_blocks++;

    writeBlock(block, new_path);

    std::string old_path = "";
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        temp_parts.emplace(new_path);
    }
}

std::string Sorter::mergeFiles(std::string& left_file, std::string& right_file)
{
    std::string new_path = "_temp_" + std::to_string(num_blocks) + ".bin";
    std::ifstream is_b(right_file, std::fstream::binary | std::fstream::out  | std::fstream::ate);
    std::ifstream is_a(left_file, std::fstream::binary | std::fstream::out  | std::fstream::ate);

    if(left_file == "")
    {
        if(is_a.good())
            std::remove(left_file.c_str());
        return right_file;
    }

    if(right_file == "")
    {
        if(is_b.good())
            std::remove(right_file.c_str());
        return left_file;
    }
    num_blocks ++;

    is_a.seekg(0);
   
    is_b.seekg(0);
    std::ofstream os_new(new_path, std::fstream::binary | std::fstream::out);

    uint64_t value_a;
    uint64_t value_b;

    bool flag_a = !is_a.read((char*)( &value_a ), sizeof(uint64_t));;
    bool flag_b = !is_b.read((char*)( &value_b ), sizeof(uint64_t));;

    while ( !( flag_a && flag_b ) ) 
    {
        if ( !flag_a && !flag_b ) 
        {
            if ( value_a < value_b ) 
            {
                os_new.write((char*)( &value_a ), sizeof(uint64_t));
                flag_a = !is_a.read((char*)( &value_a ), sizeof(uint64_t));;
            }
            else 
            {
                os_new.write((char*)( &value_b ), sizeof(uint64_t));
                flag_b = !is_b.read((char*)( &value_b ), sizeof(uint64_t));;
            }
        }
        if ( !flag_a && flag_b ) 
        {
            os_new.write((char*)( &value_a ), sizeof(uint64_t));
            flag_a = !is_a.read((char*)( &value_a ), sizeof(uint64_t));;
        }
        if ( flag_a && !flag_b ) 
        {
            os_new.write((char*)( &value_b ), sizeof(uint64_t));
            flag_b = !is_b.read((char*)( &value_b ), sizeof(uint64_t));;
        }
    }

    std::remove(left_file.c_str());
    std::remove(right_file.c_str());

    return new_path;
}

void Sorter::writeBlock(const std::vector<uint64_t>& block, const std::string& file_name)
{
    std::ofstream os(file_name, std::ios::binary | std::fstream::out);
    for (auto& cur_num : block ) 
    {
        os.write((char*)( &cur_num ), sizeof(uint64_t));
    }
}

void Sorter::foldQueue()
{
    while(true)
    {
        std::string tmp1, tmp2, merged;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if(temp_parts.size() != 1)
            {
                tmp1 = temp_parts.front();
                temp_parts.pop();
                tmp2 = temp_parts.front();
                temp_parts.pop();
            }
            else
            {
                break;
            }
            
        }
        merged = mergeFiles(tmp1, tmp2);
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            temp_parts.emplace(merged);
        }
    }
}

std::vector<uint64_t> Sorter::readBlock()
{
    std::vector<uint64_t> block;
    {
        std::unique_lock<std::mutex> lock(input_mutex);
        size_t i = 0;
        uint64_t tmp = 0;
        while((i++ < AVAILIBLE_MEMORY / (2 * sizeof(uint64_t))) && input.read((char*)(&tmp), sizeof(uint64_t)))
        {
            block.push_back(tmp);
        }
    }

    return block;
}

std::vector<uint64_t> Sorter::readBlock(const std::string& file)
{
    std::vector<uint64_t> block;
    std::ifstream is(file, std::fstream::binary | std::fstream::trunc  | std::fstream::out | std::fstream::ate);
    is.seekg(0);
    uint64_t temp;
    while(!is.eof())
    {
        is.read((char*)&temp, sizeof(uint64_t));
        block.push_back(temp);
    }

    return block;
}