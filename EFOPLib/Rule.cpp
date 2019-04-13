#include "stdafx.h"
#include "Rule.h"
#include <regex>
#include "util.h"
#include "Environ.h"
using namespace Efop;

std::string Rule::to_string()
{
	auto string_value{ rule_word + ":[" };//aa:[a,b->IN3]
	int count = 0;
	for (auto operate_pair : operations)
	{
		string_value += operate_pair.first;
		if (!operate_pair.second.empty())
		{
			string_value += ("->" + operate_pair.second);
		}
		count++;
		if (count < operations.size())
		{
			string_value += ",";
		}
	}
	string_value += "]";
	return string_value;
}

void Rule::apply(std::string& multiset)
{
	if (rule_word.empty() && operations.empty())
	{
		throw std::invalid_argument("ERROR: Rule object is not yet setup. It is in \"Default\" state.");
	}

	if (multiset.find(rule_word) == std::string::npos)
	{
		return;
	}

	for (auto operation : operations)
	{
		if (operation.second.empty() || operation.second == "HERE")
		{			
			if (operation.first != rule_word)
			{
				std::vector<int> pos_of_replace{};
				
				size_t pos = multiset.find(rule_word);
				while (pos != std::string::npos)
				{
					pos_of_replace.push_back(pos);
					pos += rule_word.size();
					pos = multiset.find(rule_word, pos);
				}

				for (int i = 0; i < pos_of_replace.size(); ++i)
				{
					const int pos_rpl = pos_of_replace[i] + i * (operation.first.size() - 1);
					multiset.erase(pos_rpl, rule_word.size());
					multiset.insert(pos_rpl, operation.first);
				}
			}			
		}
		else if (operation.second == "OUT")
		{
			const int count = count_occurence(multiset, rule_word);
			std::string word = "";
			for (int i = 0; i < count; ++i)
			{
				word += operation.first;
			}
			Environ::Instance("").process_rule_output(word, operation.second);
			return; //HALTING SIMULATION NOW
		}
		else if (operation.second.find("IN") != std::string::npos)
		{
			auto in_str = operation.second.substr(0, 2);
			auto y = operation.second.substr(2);

			std::string word = "", destination = "";
			if (in_str == "IN")
			{
				destination = operation.second.substr(2);

				const auto count = count_occurence(multiset, rule_word);
				for (int i = 0; i < count; ++i)
				{
					word += operation.first;
				}

				auto & dest_membrane = Environ::Instance("").get_membrane_labeled(destination);
				if (!dest_membrane.get_label().empty())
				{
					dest_membrane.accept_multiset(word);
				}
				else
				{
					throw std::invalid_argument("ERROR: Model String, may have not been properly formulated, destination membrane not found !!! [..IN..]");
				}
			}
			else
			{
				throw std::invalid_argument("ERROR: Model String, may have not been properly formulated !!! [..IN..]");
			}
		}
		else
		{
			Efop::Environ::Instance("").process_rule_output(operation.first, operation.second);
		}
	}
}

//This function should raise an exception if the rule_string is not well formed. 
//But it may also return an empty Rule object, so perform a check
Rule Rule::parse_rule_string(const std::string whole_rule_string)
{
	Rule rule{};
	auto rule_str = split_string_at_first(whole_rule_string, ":");
	if (rule_str.size() != 2)
	{
		throw std::invalid_argument("ERROR: Invalid Rule String !!!");
	}
	
	//assign the rule word
	rule.rule_word = rule_str[0];

	//create the operations   // = a, b->IN2, c->OUT, d->HERE
	remove_cast_string(rule_str[1], '[', ']');
	
	for (const auto operate_str : split_string_repeating(rule_str[1], ","))
	{
		std::pair<std::string, std::string> operate{};
		auto operation_split = split_string_at_first(operate_str, "->");

		//split should either by 0 in case of [a] OR 2 in case of [b-IN2,a->OUT], otherwise raise an error
		if (operation_split.size() == 2)
		{
			operate = { operation_split[0], operation_split[1] };
			rule.operations.push_back(operate);
		}
		else if (operation_split.size() == 0)
		{
			operate = { operate_str, "" };
			rule.operations.push_back(operate);
		}
		else
		{
			throw std::invalid_argument("ERROR: Invalid Rule String !!!");
		}
	}	
	return rule;
}