#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "threadpool.h"

SCENARIO("Initializattion tests")
{
    WHEN("OK")
    {
        ThreadPool *pool;
            THEN("Default")
            {
                REQUIRE_NOTHROW(pool = new ThreadPool(228));
                delete pool;
            }
    }
}

namespace test
{
    struct A
    {
        bool operator()()
        {
            return true;
        }
    };
    auto sum =[](int a, int v){return a+v;};
    auto less5 = [](int a){return a<5;};
    int _5_()
    {
        return 5;
    }
    ulong add1000000_loop(ulong a)
    {
        for(ulong i = 0; i < 1000000; i++)
        {
            a++;
        }
        return a;
    }
}

SCENARIO("functions tests")
{
    ThreadPool pool(10);
    WHEN("functor")
    {
        THEN("OK")
        {
            test::A a;
            auto func = pool.exec(a);
            REQUIRE(func.get() == true);
        }
    }
    WHEN("lambda (2args)")
    {
        THEN("OK")
        {
            auto func = pool.exec(test::sum, 10 , 15);
            REQUIRE(func.get() == 25);
        }
    }
    WHEN("lambda 1 arg")
    {
        THEN("OK")
        {
            auto func = pool.exec(test::add1000000_loop, 10UL);
            REQUIRE(func.get() == 1000010);
        }
    }
    WHEN("lambda no arg")
    {
        THEN("OK")
        {
            auto func = pool.exec(test::_5_);
            REQUIRE(func.get() == 5);
        }
        THEN("OK")
        {
            auto func = pool.exec(test::less5, 2);
            REQUIRE(func.get() == true);
        }
    }
}