#pragma once

#include <memory>
#include <algorithm>
#include <iterator>

template<class T, class Allocator = std::allocator<T>>
class vector
{
public:

	template <class T>
	class iterator_ : public std::iterator<std::random_access_iterator_tag, T> 
	{
	public:

		using reference = T &;
		using pointer = T *;
		using size_type = size_t;

		iterator_() 
		{
		}

		iterator_(pointer other) 
		{
			value = other;
		}

		bool operator == (const iterator_<T>& other) const 
		{
			return (value == other.value);
		}
		bool operator != (const iterator_<T>& other) const 
		{
			return !(value == other.value);
		}
		reference operator * () 
		{
			return *value;
		}
		iterator_<T> & operator ++ () 
		{
			value++;
			return *this;
		}
		iterator_<T> operator ++ (int)
		{
			iterator_<T> temp(value);
			value++;
			return temp;
		}
		iterator_<T> & operator -- () 
		{
			value--;
			return *this;
		}
		iterator_<T> & operator += (size_type __index) 
		{
			value += __index;
			return *this;
		}
		iterator_<T> & operator -= (size_type __index) 
		{
			value -= __index;
			return *this;
		}
		iterator_<T> operator + (size_type __index) const 
		{
			return iterator_<T>(value + __index);
		}
		iterator_<T> operator - (size_type __index) const 
		{
			return iterator_<T>(value - __index);
		}

	private:
		T* value;
	};


	using value_type = T;
	using size_type = size_t;
	using reference = value_type &;
	using const_reference = const reference;
	using pointer = value_type *;
	using const_pointer = const pointer;
	using iterator = iterator_<value_type>;
	using reverse_iterator = std::reverse_iterator<iterator>;

	vector()
		:	capacity_(8)
		,	size_(0)
		,	alloc_()
		,	data_(alloc_.allocate(capacity_))
	{
	}

	vector(size_type __size)
		:	size_(__size)
		,	alloc_()
		,	capacity_(8)
	{
		while (capacity_ <<= 1, capacity_ < __size);

		data_ = alloc_.allocate(capacity_);
	}

	vector(size_type __size, const_reference defolt)
		:	size_(__size)
		,	alloc_()
		,	capacity_(8)
	{
		while (capacity_ <<= 1, capacity_ < __size);

		data_ = alloc_.allocate(capacity_);
		std::fill(data_, data_ + size_, defolt);
	}

	vector(std::initializer_list<T> list)
		:	size_(list.size())
		,	capacity_(8)

	{
		while (capacity_ <<= 1, capacity_ < size);

		data_ = alloc_.allocate(capacity_);
		std::copy(data_, data_ + size_, list.begin());
	}

	reference operator[](size_type __index) 
	{
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
			resize(capacity_ * 2);
		}

		alloc_.construct(data_ + size_ , __x);
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
			resize(capacity_ * 2);
		}

		alloc_.construct(data_ + size_, std::forward<value_type>(__x));
		size_++;
	}

	void pop_back()
	{
		alloc_.destroy(data_ + size_ - 1);
		size_--;

		if (size_ * 4 <= capacity_)
		{
			resize(capacity_ / 4);
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
			capacity_ = std::max(__new_size, capacity_);
			size_ = std::min(size_, __new_size);

			pointer new_data_ = alloc_.allocate(capacity_);

			for (size_type i = 0; i < size_; ++i) {
				alloc_.construct(new_data_ + i, data_[i]);
				alloc_.destroy(data_ + i);
			}

			data_ = new_data_;
		}
	}

	void reserve(size_type __new_size)
	{
		if (__new_size > capacity_)
		{
			size_type temp = capacity_;
			while (capacity_ <<= 1, capacity_ < __new_size);

			pointer new_data_ = alloc_.allocate(capacity_);

			std::copy(new_data_, new_data_ + size_, data_);

			alloc_.deallocate(data_, temp);
			data_ = new_data_;
		}
	}

private:

	Allocator alloc_;
	size_type capacity_;
	size_type size_;
	pointer data_;

};