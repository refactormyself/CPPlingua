#pragma once
#include <string>
#include <vector>

//Returns empty vector if delimiter is not found, splits to at most 2 parts
static std::vector<std::string> split_string_at_first(std::string text, const std::string& delimiter)
{
	std::vector<std::string> result{};
	size_t pos = 0;

	if (text.empty())
	{
		return result;
	}

	pos = text.find(delimiter);
	if (pos != std::string::npos)
	{
		auto token1 = text.substr(0, pos);
		auto token2 = text.substr(pos + delimiter.length());
		if (!token1.empty())
		{
			result.push_back(token1);
		}
		if (!token2.empty())
		{
			result.push_back(token2);
		}
	}
	return result;
}

static std::vector<std::string> split_string_repeating(std::string text, const std::string& delimiter)
{
	std::vector<std::string> result{};
	size_t pos = 0;

	while ((pos = text.find(delimiter)) != std::string::npos) {
		auto token = text.substr(0, pos);
		if (!token.empty())
		{
			result.push_back(token);
		}

		text.erase(0, pos + delimiter.length());
	}
	if (!text.empty())
	{
		result.push_back(text);
	}
	return result;
}

static void remove_cast_string(std::string &text, const char & left_char, const char & right_char)
{
	if (left_char == text.at(0) && right_char == text.at(text.size()-1))
	{
		text.erase(0, 1);
		text.erase(text.size() - 1);
	}
	else
	{
		throw std::invalid_argument("ERROR: Invalid Rule String !!!");
	}
}

static int count_occurence(std::string text, std::string key)
{
	int count = 0, pos;

	while ((pos = text.find(key)) != std::string::npos) {
		count++;
		text.erase(0, pos + key.length());
	}

	return count;
}