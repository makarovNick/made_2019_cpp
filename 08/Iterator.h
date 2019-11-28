#pragma once

#include <iterator>

template <class T>
class Iterator 
    :   public std::iterator<std::random_access_iterator_tag, T> 
{
public:

    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;
    using size_type = size_t;

    Iterator() = default;
    Iterator(Iterator &&) = default;
    Iterator(const Iterator&) = default;
    
    Iterator& operator=(const Iterator& it)
    {
        this->value = it.value;

        return *this;
    }

    Iterator& operator=(Iterator&& it)
    {
        this->value = it.value;
        it.value = nullptr;

        return *this;
    }

    Iterator(pointer other) 
    {
        value = other;
    }

    bool operator == (const Iterator<T>& other) const 
    {
        return (value == other.value);
    }

    bool operator != (const Iterator<T>& other) const 
    {
        return !(value == other.value);
    }

    reference operator * () 
    {
        return *value;
    }

    Iterator<T> & operator ++ () 
    {
        value++;

        return *this;
    }

    Iterator<T> operator ++ (int)
    {
        Iterator<T> temp(value);
        value++;

        return temp;
    }

    Iterator<T> & operator -- () 
    {
        value--;

        return *this;
    }

    Iterator<T> & operator += (size_type __index) 
    {
        value += __index;

        return *this;
    }

    Iterator<T> & operator -= (size_type __index) 
    {
        value -= __index;

        return *this;
    }

    Iterator<T> operator + (size_type __index) const 
    {
        return Iterator<value_type>(value + __index);
    }

    Iterator<T> operator - (size_type __index) const 
    {
        return Iterator<value_type>(value - __index);
    }

private:
    value_type* value;
};