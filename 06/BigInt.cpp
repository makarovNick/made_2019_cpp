#include "BigInt.h"
#include "BigInt.h"

BigInt::BigInt()
	: digits(new char[20]) //int64_t max length is 20 chars
	, _size(1)
	, _capacity(20)
{
	digits[0] = '0';
}

BigInt::~BigInt()
{
	delete[] digits;
}

BigInt::BigInt(const BigInt& copied)
	: digits(new char[copied._capacity])
	, _size(copied._size)
	, _capacity(copied._capacity)
{
	std::copy(copied.digits, copied.digits + _size, digits);
}

BigInt& BigInt::operator=(const BigInt& copied)
{
	if (&copied == this)
		return *this;

	_size = copied._size;
	_capacity = copied._capacity;
	std::copy(copied.digits, copied.digits + copied._size, digits);

	return *this;
}

BigInt::BigInt(BigInt&& moved) noexcept
	: digits(std::move(moved.digits))
	, _size(std::move(moved._size))
	, _capacity(std::move(moved._capacity))
{
	moved.digits = nullptr;
	moved._size = 0;
	moved._capacity = 0;

}

BigInt& BigInt::operator=(BigInt&& moved) noexcept
{
	if (moved._capacity > _capacity)
	{
		if (digits)
			delete[] digits;
		digits = new char[moved._capacity];
	}
	std::copy(moved.digits, moved.digits + moved._size, digits);
	_size = moved._size;
	_capacity = moved._capacity;
	return *this;
}

BigInt::BigInt(const int64_t num)
	: digits(new char[20])
	, _capacity(20)
{
	size_t num_len = 1;
	//count number of digit
	for (uint_fast64_t j = 10; j <= (num < 0 ? -num : num); j *= 10, num_len++)
	{
		//if overflow
		if (j * 10 < j)
		{
			num_len++;
			break;
		}
	}
	//if signed add 1
	_size = num_len + (num < 0 ? 1 : 0);

	std::to_string(num).copy(digits, _size);

	//_i64toa_s(num, digits, 20, 10);
	std::reverse(digits, digits + _size);
}

BigInt::BigInt(const std::string& str)
	: _size(str.size())
	, _capacity(_size < 18 ? 20 : _size + 2)
{
	if (!isdigit(str[0]) && str[0] != '-')
	{
		throw std::invalid_argument("ERROR : Wrong string given");
	}
	for (size_t i = 1; i < _size; i++)
	{
		if (!isdigit(str[i]))
			throw std::invalid_argument("ERROR : Wrong string given");
	}

	digits = new char[_capacity];
	str.copy(digits, _size);

	std::reverse(digits, digits + _size);
}

BigInt::BigInt(const char* array)
	: _size(strlen(array))
	, _capacity(_size < 18 ? 20 : _size + 2)
{
	if (!isdigit(array[0]) && array[0] != '-')
	{
		throw std::invalid_argument("ERROR : Wrong string given");
	}
	for (size_t i = 1; i < _size; i++)
	{
		if (!isdigit(array[i]))
			throw std::invalid_argument("ERROR : Wrong string given");
	}

	digits = new char[_capacity];
	std::copy(array, array + _size, digits);

	std::reverse(digits, digits + _size);
}

//BigInt::BigInt(uint64_t num)
//	: digits(new char[40])
//	, _capacity(40)
//{
//	size_t num_len = 1;
//	for (uint_fast64_t j = 10; j <= num; j *= 10, num_len++)
//	{
//		//if overflow
//		if (j * 10 < j)
//		{
//			num_len++;
//			break;
//		}
//	}
//
//	_ui64toa_s(num, digits, 40, 10);
//	_size = num_len;
//}

bool BigInt::operator==(const BigInt& right) const
{	
	if (right.size() != _size)
	{
		return false;
	}

	for (size_t i = _size; i > 0; i--)
	{
		if (right.digits[i - 1] != digits[i - 1])
			return false;
	}

	return true;
}

bool BigInt::operator!=(const BigInt& right) const
{
	return !(*this == right);
}

BigInt::operator std::string() const
{
	std::string a(digits, digits + _size);
	std::reverse(a.begin(), a.end());

	return a;
}

bool BigInt::operator<(const BigInt& bigint) const
{
	if (digits[_size-1] == '-')
	{
		if (bigint.digits[bigint._size - 1] == '-')
		{	//if both negative
			if (_size != bigint._size)
			{
				return _size > bigint._size;
			}
			for (size_t i = _size ; i > 0; i--)
			{
				if (digits[i-1] != bigint.digits[i-1])
				{
					return digits[i-1] > bigint.digits[i-1];
				}
			}
			return false;
		}
		return true;
	}
	else
	{
		if (bigint.digits[bigint._size - 1] != '-')
		{
			if (_size != bigint._size)
			{	//if lengths are not same
				return _size < bigint._size;
			}
			for (size_t i = _size; i > 0; i--)
			{
				if (digits[i - 1] != bigint.digits[i - 1])
				{	//most significant digit
					return digits[i - 1] < bigint.digits[i - 1];
				}
			}
			//if equal
			return false;
		}

		return false;
	}
}

bool BigInt::operator>(const BigInt& b) const
{
	return b < *this;
}

bool BigInt::operator<=(const BigInt& b) const
{
	return !(*this > b);
}

bool BigInt::operator>=(const BigInt& b) const
{
	return !(*this < b);
}

const BigInt BigInt::operator+(const BigInt& bigint) const
{
	//it's easier to process with positive numbers;
	if (digits[_size - 1] == '-')
	{
		if (bigint.digits[bigint._size - 1] == '-')
		{// -a + (-b) = - ( a + b )
			return -(-*this + -bigint);
		}
		// -a + b = b - a
		return bigint - (-*this);
	}
	else
	{
		if (bigint.digits[bigint._size - 1] == '-')
		{// a + (-b) = a - b
			return *this - (-bigint);
		}
	}
	// for convinience let the first term be the biggest
	if (*this < bigint)
		return bigint + *this;
	//in case of 0
	if (bigint == BigInt("0"))
		return BigInt(*this);

	BigInt new_bigint;
	int64_t i = 0;
	new_bigint._size = _size;
	//always keep offset 2 from size to capacity in case of overflow
	if (std::max(_capacity, bigint._capacity) == _size)
	{
		new_bigint.digits = new char[_capacity + 2];
		new_bigint._capacity = _capacity + 2;
	}
	else
	{
		new_bigint.digits = new char[_capacity];
		new_bigint._capacity = _capacity;
	}

	std::memset(new_bigint.digits, '0', _size + 1);

	//difference in length between numbers
	size_t len_dif = _size - bigint._size;
	//summing each digit and if overflow add 1 to senior digit
	for (; i <= _size - len_dif - 1; i++)
	{	//some char arifmetic magic
		new_bigint.digits[i] = (new_bigint.digits[i] + bigint.digits[i] + digits[i] - 96) % 58;
		if (new_bigint.digits[i] < 48)
		{	// 48 - is ascii '0' and 58 - is '9' + 1
			new_bigint.digits[i + 1] = new_bigint.digits[i + 1] + 1;
			new_bigint.digits[i] = new_bigint.digits[i] + 48;
		}
	}
	//add all remaining digits
	for (i; i < _size; i++)
	{
		new_bigint.digits[i] = (new_bigint.digits[i] + digits[i] - 48) % 58;
		if (new_bigint.digits[i] < 48)
		{	//same magic only with longest nubmer
			new_bigint.digits[i + 1] = new_bigint.digits[i + 1] + 1;
			new_bigint.digits[i] = new_bigint.digits[i] + 48;
		}
	}
	//if first digit was not overflowed
	if (new_bigint.digits[_size] != '0')
	{
		new_bigint._size++;
	}

	return new_bigint;
}

const BigInt BigInt::operator-(const BigInt& bigint) const
{
	if (this == &bigint)
		return BigInt("0");	

	//its easier to subtract positive numbers or go to sum
	if (digits[_size - 1] == '-')
	{
		if (bigint.digits[bigint._size - 1] == '-')
		{// -a - (-b) = b - a
			return (-bigint) - (-*this);
		}
		// -a - b = - (a + b)
		return -((-*this) + bigint);
	}
	else
	{
		if (bigint.digits[bigint._size - 1] == '-')
		{// a - (-b) = a + b
			return *this + (-bigint);
		}
	}
	// for convinience let the first term be the biggest
	if (*this < bigint)
		return -(bigint - *this);

	BigInt new_bigint;
	new_bigint._capacity = _capacity;
	new_bigint._size = _size;
	new_bigint.digits = new char[_capacity];
	int64_t i = 0;
	//needed to perform char arifmetic
	std::memset(new_bigint.digits, '0', _size + 1);

	//difference in length between numbers
	size_t len_dif = _size - bigint._size;
	//summing each digit and if overflow add 1 to senior digit
	for (; i <= _size - len_dif - 1; i++)
	{	//some char arifmetic magic
		new_bigint.digits[i] = (new_bigint.digits[i] - bigint.digits[i] + digits[i]);
		if (new_bigint.digits[i] < 48)
		{	// 48 - is ascii '0' and 58 - is '9' + 1
			new_bigint.digits[i + 1] = new_bigint.digits[i + 1] - 1;
			new_bigint.digits[i] = new_bigint.digits[i] + 10;
		}
	}
	//add all remaining digits
	for (; i < _size; i++)
	{
		new_bigint.digits[i] = (new_bigint.digits[i] + digits[i] - 48);
		if (new_bigint.digits[i] < 48)
		{	//same magic only with longest nubmer
			new_bigint.digits[i + 1] = new_bigint.digits[i + 1] - 1;
			new_bigint.digits[i] = new_bigint.digits[i] + 10;
		}
	}
	
	//count and delete zeroed digits
	while (new_bigint.digits[--i] == '0');

	new_bigint._size = i + 1;
	if (new_bigint._size - i > 3)
	{
		char* temp = new char[new_bigint._size - i + 1];
		std::copy(new_bigint.digits, new_bigint.digits + new_bigint._size, temp);
		delete[] new_bigint.digits;
		new_bigint.digits = temp;
	}


	return new_bigint;
}

BigInt BigInt::operator-()
{
	BigInt bigint(*this);

	if (digits[_size-1] == '-')
	{
		bigint._size = _size - 1;
	}
	else if (digits[_size - 1] != '0')
	{
		bigint.digits[_size] = '-';
		bigint._size = _size + 1;
	}

	bigint._capacity = _capacity;

	return bigint;
}

const BigInt BigInt::operator-() const
{
	BigInt bigint(*this);
	return -bigint;
}

size_t BigInt::size() const
{
	return _size;
}

size_t BigInt::capacity() const
{
	return _capacity;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bigint)
{
	os << std::string(bigint);
	return os;
}

const BigInt operator+(const uint64_t num, const BigInt& bigint)
{
	return BigInt(num) + bigint;
}

const BigInt operator-(const uint64_t num, const BigInt& bigint)
{
	return BigInt(num) - bigint;
}

bool operator<(const uint64_t num, const BigInt& bigint)
{
	return BigInt(num) < bigint;
}

bool operator>(const uint64_t num, const BigInt& bigint)
{
	return BigInt(num) > bigint;
}

bool operator<=(const uint64_t num, const BigInt& bigint)
{
	return BigInt(num) <= bigint;
}

bool operator>=(const uint64_t num, const BigInt& bigint)
{
	return BigInt(num) >= bigint;
}

bool operator==(const uint64_t num, const BigInt& bigint)
{
	return BigInt(num) == bigint;
}

bool operator!=(const uint64_t num, const BigInt& bigint)
{
	return !(BigInt(num) == bigint);
}

