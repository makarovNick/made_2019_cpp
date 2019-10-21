#pragma once
#include <stdexcept>
#include <cstdlib>
#include <cstdint>

typedef uint8_t byte;
class LinearAllocator
{
private:
	byte* basePointer;
	size_t offset;
	size_t size;
public:
	~LinearAllocator();
	LinearAllocator(size_t maxSize);
	byte* alloc(size_t size);
	void reset();
};
