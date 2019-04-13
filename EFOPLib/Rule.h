#pragma once
#include <vector>
#include <string>

namespace Efop
{
	class Rule
	{		
	public:
		void apply(std::string& multiset);
		Rule() = default;
		~Rule() = default;
		static Rule parse_rule_string(std::string whole_rule_string);
		std::string to_string();
	private:
		std::string rule_word{};
		std::vector<std::pair<std::string, std::string>> operations{}; //a vector of operations i.e. <op_word, command>		
	};
}

