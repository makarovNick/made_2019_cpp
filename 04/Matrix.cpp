#include "Matrix.h"

Matrix::Array::Array(size_t c) :
	columns(c)
{
	data.resize(c, 0);
}

Matrix::Array::~Array()
{
	data.clear();
}

Matrix::Matrix(const size_t r, const size_t c) :
	rows(r),
	columns(c)
{
	if (r == 0 || c == 0)
		throw std::logic_error("ERROR : length can't be 0");

	for (size_t i = 0; i < r; i++)
	{
		arrays.push_back(Array(c));
	}
}

Matrix::~Matrix()
{
	arrays.clear();
}

int& Matrix::Array::operator[](const size_t index)
{
	if (index >= columns)
		throw std::out_of_range("ERROR : Matrix cols out of bounds");
	return data[index];
}

const int& Matrix::Array::operator[](const size_t index) const
{
	if (index >= columns)
		throw std::out_of_range("ERROR : Matrix cols out of bounds");
	return data[index];
}

Matrix::Array& Matrix::operator[](const size_t index)
{
	if (index >= rows)
		throw std::out_of_range("ERROR : Matrix rows out of bounds");
	return arrays[index];
}
const Matrix::Array& Matrix::operator[](const size_t index) const
{
	if (index >= rows)
		throw std::out_of_range("ERROR : Matrix rows out of bounds");
	return arrays[index];
}

 bool Matrix::operator==(const Matrix& right) const
{
	 if (this == &right)
		 return true;

	if (columns != right.columns || rows!= right.rows)
		return false;

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			if (arrays[i][j] != right[i][j])
			{
				return false;
			}
		}
	}

	return true;
}
bool Matrix::operator!=(const Matrix& right) const
{
	return ! (*this == right);
}

void Matrix::operator*=(const int v)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			arrays[i][j] *= v;
		}
	}
}

size_t Matrix::Array::getColumns() const
{
	return data.size();
}

size_t Matrix::getRows() const
{
	return arrays.size();
}
size_t Matrix::getColumns() const
{
	return arrays[0].getColumns();
}

//Matrix& Matrix::operator*(const int v) const
//{
//	Matrix *tmp = new Matrix(rows, columns);
//	for (size_t i = 0; i < rows; i++)
//	{
//		for (size_t j = 0; j < columns; j++)
//		{
//			(*tmp)[i][j] = arrays[i][j];
//		}
//	}
//	*tmp *= v;
//	return *tmp;
//}

