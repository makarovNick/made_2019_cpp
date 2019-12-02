#pragma once

#include <memory>

template <class T>
class Allocator : public std::allocator<T>
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type n)
    {
        return static_cast<pointer>(
            ::operator new(n * sizeof(value_type)));
    }

    void deallocate(pointer __pointer, size_type n)
    {
        ::operator delete(__pointer, n * sizeof(value_type));
    }

    template <class... Args>
    void construct(pointer __pointer, Args&&... args)
    {
        ::new(__pointer) value_type(std::forward<Args>(args)...);
    }

    void destroy(pointer __pointer)
    {
        __pointer->~value_type();
    }
};