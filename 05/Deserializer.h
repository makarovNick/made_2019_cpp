#pragma once
#include "Serializer.h"
#include <istream>

class Deserializer 
{
	static constexpr char Separator = ' ';

public:

	explicit Deserializer(std::istream& in)
		: in_(in) 
	{
	}

	template<typename T>
	Error load(T&& object) const
	{
		return object.serialize(*this);
	}

	template<typename ...Args>
	Error operator()(Args&& ...args) const
	{
		return process(std::forward<Args>(args)...);
	}

private:

	std::istream& in_;

	
	template<typename T>
	Error process(T&& value) const 
	{

		std::string token;
		in_ >> token;

		if constexpr (std::is_same<T, bool>::value || std::is_same<T, bool&>::value)
		{
			if (token == "true" || token == "false")
			{
				value = token == "true";
			}
			else
			{
				return Error::CorruptedArchive;
			}
		}
		else if constexpr (std::is_same<T, uint64_t>::value || std::is_same<T, uint64_t&>::value)
		{
			if (token.empty())
			{
				return Error::CorruptedArchive;
			}
			for (auto c : token)
			{
				if (!isdigit(c))
				{
					return Error::CorruptedArchive;
				}
			}

			value = strtoull(token.c_str());
		}
		else
		{
			return Error::CorruptedArchive;
		}

		return Error::NoError;
	}

	template<typename T, typename ...Args>
	Error process(T&& value, Args&& ...args) const
	{
		if (process(std::forward<T>(value)) == Error::CorruptedArchive)
		{
			return Error::CorruptedArchive;
		}

		return process(std::forward<Args>(args)...);
	}
};