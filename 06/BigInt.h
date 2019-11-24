#pragma once
#include <type_traits>
#include <ostream>
#include <algorithm>
#include <string>
#include <cstring>

class BigInt
{
public:

	BigInt();
	~BigInt();
	BigInt(const BigInt& copied);
	BigInt& operator = (const BigInt& copied);
	BigInt(BigInt&& moved) noexcept;
	BigInt& operator = (BigInt&& moved) noexcept;
	BigInt(const int64_t num);
	BigInt(const std::string& str);
	BigInt(const char* array);
	//BigInt(uint64_t num);

	bool operator==(const BigInt& right) const;
	bool operator!=(const BigInt& right) const;

	friend std::ostream& operator<<(std::ostream& os, const BigInt& bigint);
	operator std::string() const;

	bool operator <(const BigInt& b) const;
	bool operator >(const BigInt& b) const;
	bool operator <=(const BigInt& b) const;
	bool operator >=(const BigInt& b) const;

	const BigInt operator+(const BigInt& bigint) const;
	const BigInt operator-(const BigInt& bigint) const;

	friend const BigInt operator+(const uint64_t num, const BigInt& bigint);
	friend const BigInt operator-(const uint64_t num, const BigInt& bigint);

	friend bool operator <(const uint64_t num, const BigInt& bigint);
	friend bool operator >(const uint64_t num, const BigInt& bigint);
	friend bool operator <=(const uint64_t num, const BigInt& bigint);
	friend bool operator >=(const uint64_t num, const BigInt& bigint);
	friend bool operator ==(const uint64_t num, const BigInt& bigint);
	friend bool operator !=(const uint64_t num, const BigInt& bigint);


	BigInt operator -();
	const BigInt operator -() const;

	size_t size() const;
	size_t capacity() const;

private:

	size_t _size;
	size_t _capacity;

	char* digits = nullptr;

};

