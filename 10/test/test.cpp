#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../limited_sorter.h"

namespace test
{
        const std::string o5 = "test/output5";
        const std::string o100 = "test/output100";
        const std::string o1000 = "test/output1000";
        const std::string o10000 = "test/output10000";
        const std::string i5 = "test/input5";
        const std::string i100 = "test/input100";
        const std::string i1000 = "test/input1000";
        const std::string i10000 = "test/input10000";

        std::vector<uint64_t> readBlock(const std::string& file)
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
}

SCENARIO("Sorting tests")
{
        WHEN("5")
        {
               THEN("OK")
               {
                       Sorter sorter(test::i5, test::o5);
                       sorter.Sort();
                       auto sorted = test::readBlock(test::o5);
                       auto sorted_default = test::readBlock(test::i5);
                       std::sort(sorted_default.begin(), sorted.end());
                       REQUIRE(std::equal(sorted_default.begin(), sorted_default.end(), sorted.begin()));
               } 
        }

        WHEN("100")
        {
               THEN("OK")
               {
                       Sorter sorter(test::i100, test::o100);
                       sorter.Sort();
                       auto sorted = test::readBlock(test::o100);
                       auto sorted_default = test::readBlock(test::i100);
                       std::sort(sorted_default.begin(), sorted.end());
                       REQUIRE(std::equal(sorted_default.begin(), sorted_default.end(), sorted.begin()));
               } 
        }

        WHEN("1000")
        {
               THEN("OK")
               {
                       Sorter sorter(test::i1000, test::o1000);
                       sorter.Sort();
                       auto sorted = test::readBlock(test::o1000);
                       auto sorted_default = test::readBlock(test::i1000);
                       std::sort(sorted_default.begin(), sorted.end());
                       REQUIRE(std::equal(sorted_default.begin(), sorted_default.end(), sorted.begin()));
               } 
        }

        WHEN("10000")
        {
               THEN("OK")
               {
                       Sorter sorter(test::i10000, test::i10000);
                       sorter.Sort();
                       auto sorted = test::readBlock(test::o10000);
                       auto sorted_default = test::readBlock(test::i10000);
                       std::sort(sorted_default.begin(), sorted.end());
                       REQUIRE(std::equal(sorted_default.begin(), sorted_default.end(), sorted.begin()));
               } 
        }
}
