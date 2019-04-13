#pragma once
#include <string>
#include <vector>
#include "Rule.h"
#include "include/nlohmann/json.hpp"


namespace Efop
{
	class Membrane
	{
	public:
		Membrane() = default;
		
		Membrane(std::string label, std::string parent_label, std::vector<std::string> multiset, std::vector<Rule> rules)
			:label_(std::move(label)), multiset_(multiset), rules_(rules), parent_label(parent_label) {}
		
		void accept_multiset(std::string multiset);
		bool validate_non_default() const;

		std::string get_label() const { return label_; }
		std::string get_current_state() const { return multiset_.empty() ? "" : multiset_[0]; }
		std::vector<std::string> get_rules_strings() const
		{
			std::vector<std::string> ret_value{};
			for (auto rule : rules_)
			{
				ret_value.push_back(rule.to_string());
			}
			return ret_value;
		}		
		void push_child(std::string label);
		std::vector<std::string> delete_child(std::string child_label);
		std::vector<std::string> get_child_labels() const { return child_labels; }
		std::string get_parent_label() const { return parent_label; }
		void set_parent(const std::string label) {parent_label = label; }
		void set_label(const std::string& label) { label_ = label; }
		void set_multiset(const std::string& multiset)
		{
			if (!multiset.empty())
			{
				if (multiset_.empty())
				{
					multiset_.push_back(multiset);
				}
				else { multiset_[0] + multiset; }
			}
		}

		void simulate(std::string multiset);
		void set_rules(const std::vector<std::string>& rule_strings);

	private:
		std::string label_;
		std::vector<std::string> multiset_{};
		std::vector<Rule> rules_{};
		std::string parent_label{"SKIN"};
		std::vector<std::string> child_labels{};
		
	};

}

