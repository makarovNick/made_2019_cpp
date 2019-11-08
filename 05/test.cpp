#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Serializer.h"
#include "Deserializer.h"

#include <sstream>
#include <fstream>

SCENARIO("Initialiation tests")
{
	GIVEN("Stream")
	{
		WHEN("String Stream")
		{
			std::stringstream file;
			THEN("OK")
			{
				Serializer *ser;
				Deserializer *des;
				REQUIRE_NOTHROW(ser = new Serializer(file));
				REQUIRE_NOTHROW(des = new Deserializer(file));
				delete ser;
				delete des;
			}
		}
		WHEN("COUT/CIN Stream")
		{
			Serializer* ser;
			Deserializer* des;
			REQUIRE_NOTHROW(ser = new Serializer(std::cout));
			REQUIRE_NOTHROW(des = new Deserializer(std::cin));
			delete ser;
			delete des;
		}
		WHEN("File stream")
		{
			Serializer* ser;
			Deserializer* des;
			std::ofstream of;
			std::ifstream ifs;
			REQUIRE_NOTHROW(ser = new Serializer(of));
			REQUIRE_NOTHROW(des = new Deserializer(ifs));
			delete ser;
			delete des;
		}
	}
}
namespace test
{
	struct Data1
	{
		uint64_t a;

		template <typename serializer>
		Error serialize(serializer& Serializer)
		{
			return Serializer(a);
		}
	};
	struct Data2
	{
		bool a;

		template <typename serializer>
		Error serialize(serializer& Serializer)
		{
			return Serializer(a);
		}
	};
	struct Data3
	{
		uint64_t a;
		bool b;
		uint64_t c;

		template <typename serializer>
		Error serialize(serializer& Serializer)
		{
			return Serializer(a, b, c);
		}
	};
}
SCENARIO("Serialize tests")
{
	GIVEN("Struct with bool/uint64_t")
	{
		WHEN("One field")
		{
			test::Data1 x{9999};
			std::stringstream stream;
			Serializer Serializer(stream);
			Serializer.save(x);
			REQUIRE(stream.str() == "9999 ");
		}
		WHEN("One field")
		{
			test::Data2 x{ false };
			std::stringstream stream;
			Serializer Serializer(stream);
			Serializer.save(x);
			REQUIRE(stream.str() == "false ");
		}
		WHEN("More than one fields")
		{
			test::Data3 x{ 123, true, 22 };
			std::stringstream stream;
			Serializer Serializer(stream);
			Serializer.save(x);
			REQUIRE(stream.str() == "123 true 22 ");
		}
	}
}

SCENARIO("Deserialize tests")
{
	GIVEN("Struct with bool/uint64_t")
	{
		WHEN("One field")
		{
			test::Data1 x;
			std::stringstream stream;
			stream << "9999 ";
			Deserializer des(stream);
			des.load(x);
			REQUIRE(x.a == 9999);
		}
		WHEN("One field")
		{
			test::Data2 x;
			std::stringstream stream;
			stream << "false ";
			Deserializer des(stream);
			des.load(x);
			REQUIRE(x.a == false);
		}
		WHEN("More than one fields")
		{
			test::Data3 x;
			std::stringstream stream;
			stream << "123 true 22 ";
			Deserializer des(stream);
			des.load(x);
			REQUIRE(x.a == 123);
			REQUIRE(x.b == true );
			REQUIRE(x.c == 22 );
		}
	}
}
