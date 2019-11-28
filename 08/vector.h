#pragma once

#include "Iterator.h"

#include <stdexcept>
#include <memory>
#include <algorithm>


template<class T, class Allocator = std::allocator<T>>
class vector
{
public:

	using value_type = T;
	using size_type = size_t;
	using reference = value_type &;
	using const_reference = const reference;
	using pointer = value_type *;
	using const_pointer = const pointer;
	using iterator = Iterator<value_type>;
	using reverse_iterator = std::reverse_iterator<iterator>;


	~vector()
	{
		alloc_.deallocate(data_, capacity_);
		data_ = nullptr;
	}
	vector()
		:	capacity_(8)
		,	size_(0)
		,	data_(alloc_.allocate(capacity_))
	{
	}

	vector(size_type __size)
		:	size_(__size)
		,	capacity_(8)
	{
		while (capacity_ <<= 1, capacity_ < __size);

		data_ = alloc_.allocate(capacity_);
	}

	vector(size_type __size, const_reference defolt)
		:	size_(__size)
		,	capacity_(8)
	{
		while (capacity_ <<= 1, capacity_ < __size);

		data_ = alloc_.allocate(capacity_);
		std::fill(data_, data_ + size_, defolt);
	}

	vector(size_type __size, value_type&& defolt)
		:	size_(__size)
		,	capacity_(8)
	{
		while (capacity_ <<= 1, capacity_ < __size);

		data_ = alloc_.allocate(capacity_);
		std::fill(data_, data_ + size_, std::forward<value_type>(defolt));
	}

	// vector(std::initializer_list<T> list)
	// 	:	size_(list.size())
	// 	,	capacity_(8)

	// {
	// 	while (capacity_ <<= 1, capacity_ < size_);

	// 	data_ = alloc_.allocate(capacity_);
	// 	std::copy(data_, data_ + size_, list.begin());
	// }

	// vector& operator =(std::initializer_list<T> list)
	// {
	// 	if(capacity_ < list.size())
	// 	{
	// 		alloc_.deallocate(data_, size_);
	// 	}

	// 	size_ = list.size();

	// 	capacity_ = 8;
	// 	while (capacity_ <<= 1, capacity_ < size_);

	// 	data_ = alloc_.allocate(capacity_);
	// 	std::copy(data_, data_ + size_, list.begin());

	// 	return *this;
	// }

	vector(const vector& other)
		:	size_(other.size_)
		,	capacity_(other.capacity_)
	{
		data_ = alloc_.allocate(capacity_);
		std::copy(data_, data_ + size_, other.data_);
	}

	vector& operator =(vector && moved)
	{
		if(capacity_ < moved.size_)
		{
			alloc_.deallocate(data_, size_);
		}

		size_ = moved.size_;
		capacity_ = moved.capacity_;
		data_ = moved.data_;

		moved.data_ = nullptr;

		return *this;
	}

	vector& operator =(const vector& other)
	{
		if(capacity_ < other.size_)
		{
			alloc_.deallocate(data_, size_);
		}

		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = alloc_.allocate(capacity_);

		std::copy(data_, data_ + size_, other.data_);
		return *this;
	}

	vector(vector && moved)
		:	size_(moved.size_)
		,	capacity_(moved.capacity_)
	{
		data_ = moved.data_;
		moved.data_ = nullptr;
	}

	reference operator[](size_type __index) 
	{
		if(__index >= size_)
		{
			throw std::out_of_range("ERROR : vector out of bounds");
		}
		return data_[__index];
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

	void push_back(const_reference __x)
	{
		if (size_ == capacity_)
		{
			__reallocate(capacity_ * 2);
		}

		data_[size_] = __x;
		size_++;
	}

	void push_back(value_type&& __x)
	{
		emplace_back(std::move(__x));
	}

	void emplace_back(value_type&& __x)
	{
		if (size_ == capacity_)
		{
			__reallocate(capacity_ * 2);
		}

		data_[size_] = std::move(__x);
		size_++;
	}

	void pop_back()
	{
		size_--;

		if (size_ * 4 <= capacity_)
		{
			__reallocate(capacity_ / 4);
		}
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

	void clear()
	{
		std::fill(data_, data_ + size_, T());
	}

	void resize(size_type __new_size)
	{
		if (__new_size != capacity_)
		{
			size_type temp  = std::max(__new_size, capacity_);
			pointer new_data_ = alloc_.allocate(temp);
			for (size_type i = 0; i < __new_size; ++i) 
			{
				new_data_[i] =  (i >= size_ ? value_type() : data_[i]);
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

private:

	void __reallocate(size_type __new_size)
	{
		size_type temp = 1;
		while (temp <<= 1, temp < __new_size || temp < 8);
		pointer new_data_ = alloc_.allocate(temp);
		for(size_type i = 0; i < size_; i ++)
		{
			new_data_[i] = data_[i];
		}
		alloc_.deallocate(data_, capacity_);
		
		size_ = std::min(__new_size, size_);
		capacity_ = temp;
		data_ = new_data_;
	}

	Allocator alloc_;
	size_type capacity_;
	size_type size_;
	pointer data_;

};