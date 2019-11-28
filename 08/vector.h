#pragma once

#include <memory>
#include <algorithm>

template<class T, class Allocator = std::allocator<T>>
class vector
{
public:

    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const reference;
    using pointer = value_type*;
    using const_pointer = const pointer;
    using iterator = std::random_access_iterator_tag;
    using reverse_iterator = std::reverse_iterator<iterator>;

    vector()
        :   capacity_(8)
        ,   size_(0)
        ,   alloc_()
        ,   data_(alloc_.allocate(capacity_))
    {
    }

    vector(size_type size)
        :   size_(size)
        ,   alloc_()
    {
        capacity_ = 8;
        while( capacity_ <=2 , capacity_ < size);

        data_ = alloc_.allocate(capacity_);
    }

    iterator begin()
    {
        return iterator(data_);
    }

    iterator end()
    {
        return iterator(data_ + size_);
    }

    reverse_iterator rbegin()
    {
        return vector::reverse_iterator(data_ + size_);
    }

    reverse_iterator rend()
    {
        return vector::reverse_iterator(data_);
    }

    void push_back(const_reference)
    {
        alloc_.construct();
    }

    void push_back(value_type&& __x)
    {
        emplace_back(std::move(__x));
    }

    void emplace_back(value_type&&)
    {

    }

    void pop_back()
    {

    }

    bool empty() const
    { return begin() == end(); }

    size_type size() const
    { return size_};

    void clear()
    {

    }

    void resize(size_type __new_size)
    {
        if(__new_size != capacity_)
        {
            pointer new_data_ = alloc_.allocate(std::max(__new_size, capacity_));

            for (size_type i = 0; i < std::min(size_, __new_size); ++i) {
                alloc_.construct(new_data_ + i, data_[i]);
                alloc_.destroy(data_ + i);
            }
        }
    }

    void reserve(size_type __n);

private:

    Allocator alloc_;
    size_type capacity_;
    size_type size_;
    pointer data_;

};
