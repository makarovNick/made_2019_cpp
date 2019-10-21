#include "allocator.h"

#include <new>
//const size_t MAX_CHUNK_SIZE = 4294967294
LinearAllocator::LinearAllocator(size_t maxSize)
{
	if(/*maxSize > MAX_CHUNK_SIZE || */ maxSize == 0)
		throw std::range_error("Initial size of allocator is larger than allowed or 0");
	
	offset = 0;
	size = maxSize;
	basePointer = (byte*) malloc(maxSize * sizeof(byte));
}
byte* LinearAllocator::alloc(size_t _size)
{
	offset += _size;

	if (offset > size)
		return nullptr;

	return (basePointer + offset - _size);
}

void LinearAllocator::reset()
{
	if (offset == 0 || basePointer == nullptr)
	{
		throw std::range_error("An attempt to reset an already freed or not allocated memory");
		return;
	}
	
	offset = 0;
}

