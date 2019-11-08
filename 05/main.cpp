#include "Serializer.h"
#include "Deserializer.h"

#include <sstream>
#include <iostream>
#include <cassert>



struct Data
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
int main()
{
	Data x{ 1, true, 2 };

	std::stringstream stream;
	Serializer Serializer(stream);
	Serializer.save(x);

	Data y{ 0, false, 0 };

	Deserializer deserializer(stream);
	const Error err = deserializer.load(y);
	//Serializer.save(y);

	assert(err == Error::NoError);

	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);
}
