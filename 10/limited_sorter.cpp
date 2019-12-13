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

    //easy copy
    std::ifstream source(tmp, std::ios::binary  | std::fstream::out | std::fstream::ate);
    source.seekg(0);

    std::istreambuf_iterator<char> begin_source(source);
    std::istreambuf_iterator<char> end_source;
    std::ostreambuf_iterator<char> begin_dest(output); 
    std::copy(begin_source, end_source, begin_dest);

    std::remove(tmp.c_str());

    return tmp;      
}

Sorter::Sorter(const std::string& inpu, const std::string& output, size_t mem)
    : input(inpu, std::fstream::binary  | std::fstream::out | std::fstream::ate)
    , output(output, std::fstream::binary | std::fstream::out | std::fstream::ate)
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
}

void Sorter::addToQueue(const std::vector<uint64_t>& block)
{
    std::string new_path = "_temp_" + std::to_string(num_blocks) + ".bin";
    num_blocks++;

    writeBlock(block, new_path);

    std::string old_path = "";
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if(!temp_parts.empty())
        {
            old_path = temp_parts.front();
            temp_parts.pop();
        }


        temp_parts.emplace(mergeFiles(new_path, old_path));
    }
}

std::string Sorter::mergeFiles(std::string& a, std::string& b)
{
    std::string new_path = "_temp_" + std::to_string(int(num_blocks.load())) + ".bin";

    if(a == "")
    {
        std::remove(a.c_str());
        return b;
    }

    if(b == "")
    {
        std::remove(b.c_str());
        return a;
    }
    num_blocks ++;

    std::ifstream is_a(a, std::fstream::binary | std::fstream::out  | std::fstream::ate);
    is_a.seekg(0);
    std::ifstream is_b(b, std::fstream::binary | std::fstream::out  | std::fstream::ate);
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

    std::remove(a.c_str());
    std::remove(b.c_str());

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
    std::unique_lock<std::mutex> lock(queue_mutex);
    while(temp_parts.size()!=1)
    {
        std::string a = temp_parts.front();
        temp_parts.pop();
        std::string b = temp_parts.front();
        temp_parts.pop();
        temp_parts.emplace(mergeFiles(a, b));
    }
}

std::vector<uint64_t> Sorter::readBlock()
{
    std::vector<uint64_t> block;

    if(!input.eof())
    {
        std::lock_guard<std::mutex> lock(input_mutex);
        size_t i = 0;
        uint64_t tmp = 0;
        while((i < AVAILIBLE_MEMORY / (2 * sizeof(uint64_t))) && input.read((char*)(&tmp), sizeof(uint64_t)))
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