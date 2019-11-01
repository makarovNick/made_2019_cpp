#pragma once

#include <exception>
#include <vector>
#include <iostream>

class Matrix
{
	class Array
	{
	private:

		size_t columns;
		std::vector<int> data;

	public:

		int& operator[](const size_t index);
		const int& operator[](const size_t index) const;

		Array(size_t c);
		Array() = delete;
		~Array();

		size_t getColumns() const;
	};

private:
	
	size_t rows;
	size_t columns;

	std::vector<Array> arrays;

public:

	Matrix(const size_t r, const size_t c);
	~Matrix();

	Array& operator[](const size_t index);
	const Array& operator[](const size_t index) const;

	bool operator==(const Matrix& right) const;
	bool operator!=(const Matrix& right) const;

	//Matrix& operator*(const int v) const;
	void operator*=(const int v);

	size_t getRows() const;
	size_t getColumns() const;
};
