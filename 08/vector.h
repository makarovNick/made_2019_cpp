#pragma once

#include "Iterator.h"
#include "Allocator.h"

#include <stdexcept>
#include <algorithm>


template <class T, class Allocator = Allocator<T>>
class vector
{
public:

    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const reference;
    using pointer = value_type*;
    using iterator = Iterator<value_type>;
    using reverse_iterator = std::reverse_iterator<iterator>;


    ~vector()
    {
        clear();

        alloc_.deallocate(data_, capacity_);
        data_ = nullptr;
    }
    vector()
        : capacity_(8)
        , size_(0)
        , data_(alloc_.allocate(capacity_))
    {
    }

    vector(size_type __size)
        : size_(__size)
        , capacity_(8)
    {
        while (capacity_ <<= 1, capacity_ < __size);

        data_ = alloc_.allocate(capacity_);
    }

    vector(size_type __size, const_reference defolt)
        : size_(__size)
        , capacity_(8)
    {
        while (capacity_ <<= 1, capacity_ < __size);

        data_ = alloc_.allocate(capacity_);


        for(size_type i = 0 ; i < size_; i++)
        {
            alloc_.construct(data_ + i, defolt);
        }
    }

    vector(size_type __size, value_type&& defolt)
        : size_(__size)
        , capacity_(8)
    {
        while (capacity_ <<= 1, capacity_ < __size);

        data_ = alloc_.allocate(capacity_);

        for(size_type i = 0 ; i < size_; i++)
        {
            alloc_.construct(data_ + i, std::forward<value_type>(defolt));
        }
    }

    vector(const vector& other)
        : size_(other.size_)
        , capacity_(other.capacity_)
    {
        data_ = alloc_.allocate(capacity_);

        for(size_type i = 0 ; i < size_; i++)
        {
            alloc_.construct(data_ + i, other.data_[i]);
        }
    }

    vector& operator=(vector&& moved)
    {
        if(data_)
        {
            clear();
            alloc_.deallocate(data_, capacity_);
        }

        size_ = moved.size_;
        capacity_ = moved.capacity_;
        data_ = moved.data_;

        moved.data_ = nullptr;

        return *this;
    }

    vector& operator=(const vector& other)
    {
        if(data_)
        {
            clear();
            alloc_.deallocate(data_, capacity_);
        }

        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = alloc_.allocate(capacity_);
        for(size_type i = 0 ; i < size_; i++)
        {
            alloc_.construct(data_ + i, other.data_[i]);
        }
        return *this;
    }

    vector(vector&& moved)
        : size_(moved.size_)
        , capacity_(moved.capacity_)
    {
        data_ = moved.data_;
        moved.data_ = nullptr;
    }

    reference operator[](size_type __index)
    {
        if (__index >= size_)
        {
            throw std::out_of_range("ERROR : vector out of bounds");
        }
        return data_[__index];
    }

    void push_back(const_reference __x)
    {
        if (size_ == capacity_)
        {
            __reallocate(capacity_ * 2);
        }

        alloc_.construct(data_+size_, __x);
        size_++;
    }

    void push_back(value_type&& __x)
    {
        emplace_back(std::forward<value_type>(__x));
    }

    void emplace_back(value_type&& __x)
    {
        if (size_ == capacity_)
        {
            __reallocate(capacity_ * 2);
        }

        alloc_.construct(data_+size_, std::forward<value_type>(__x));
        size_++;
    }

    void pop_back()
    {
        alloc_.destroy(data_+size_);
        size_--;

        if (size_ * 4 <= capacity_)
        {
            __reallocate(capacity_ / 4);
        }

    }

    void resize(size_type __new_size)
    {
        if (__new_size != capacity_)
        {
            size_type temp = std::max(__new_size, capacity_);
            pointer new_data_ = alloc_.allocate(temp);
            for (size_type i = 0; i < size_; ++i)
            {
                alloc_.construct(new_data_ + i, data_[i]);
                alloc_.destroy(data_ + i);
            }
            alloc_.deallocate(data_, capacity_);

            size_ = __new_size;
            capacity_ = temp;
            data_ = new_data_;
        }
    }

    void reserve(size_type __new_size)
    {
        if (__new_size > capacity_)
        {
            __reallocate(__new_size);
        }
    }
	 
	void clear()
    {
        for(size_type i = 0 ; i < size_; i++)
        {
            alloc_.destroy(data_+i);
        }

        size_ = 0;
    }

	bool empty() const
    {
        return size_ == 0;
    }

    size_type size() const
    {
        return size_;
    }

    size_type capacity() const
    {
        return capacity_;
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
        return reverse_iterator(data_ + size_);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(data_);
    }

private:
    void __reallocate(size_type __new_size)
    {
        size_type temp = 1;
        while (temp <<= 1, temp < __new_size || temp < 8)
        ;
        pointer new_data_ = alloc_.allocate(temp);
        for (size_type i = 0; i < size_; i++)
        {
            alloc_.construct(new_data_ + i , data_[i]);
            alloc_.destroy(data_ + i);
        }
        alloc_.deallocate(data_, capacity_);

        size_ = std::min(__new_size, size_);
        capacity_ = temp;
        data_ = new_data_;
    }

    Allocator alloc_;
    size_type capacity_;
    size_type size_;
    pointer data_ = nullptr;
};