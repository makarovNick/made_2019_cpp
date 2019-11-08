#pragma once
#include <iostream>
#include <string>
#include <type_traits>

enum class Error 
{
	NoError,
	CorruptedArchive
};

class Serializer 
{

	static constexpr char Separator = ' ';
public:

	explicit Serializer(std::ostream& out)
		: out_(out) 
	{
	}

	template<typename T>
	Error save(T&& object) const;

	template<typename... Args>
	Error operator()(Args&& ... args) const;

private:

	std::ostream& out_;

	template<typename T>
	Error process(T&& value) const;
	template<typename T, typename... Args>
	Error process(T&& value, Args&& ... args) const;
};

template<typename T>
inline Error Serializer::save(T&& object) const
{
	return object.serialize(*this);
}

template<typename ...Args>
inline Error Serializer::operator()(Args&& ...args) const
{
	return process(std::forward<Args>(args)...);
}

template<typename T>
inline Error Serializer::process(T&& value) const
{
	if (std::is_same<T, bool>::value || std::is_same<T, bool&>::value) 
	{
		out_ << (value ? "true" : "false") << Separator;
	} 
	else if (std::is_same<T, uint64_t>::value || std::is_same<T, uint64_t&>::value) 
	{
		out_ << value << Separator;
	}
	else 
	{
		return Error::CorruptedArchive;
	}

	return Error::NoError;
}

template<typename T, typename ...Args>
inline Error Serializer::process(T&& value, Args&& ...args) const
{

	if (process(std::forward<T>(value)) == Error::CorruptedArchive)
	{
		return Error::CorruptedArchive;
	}

	return process(std::forward<Args>(args)...);
}