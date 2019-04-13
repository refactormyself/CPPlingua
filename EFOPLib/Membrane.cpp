#include "stdafx.h"
#include <string>
#include "Membrane.h"
#include "Environ.h"

using namespace std;
using namespace Efop;

void Efop::Membrane::accept_multiset(std::string multiset)
{
	if (!validate_non_default())
	{
		throw std::invalid_argument("ERROR: Membrane object is not yet setup. It is in \"Default\" state.");
	}
	
	if (multiset_.empty())
	{
		multiset_.push_back(multiset);
	}
	else { multiset_[0] += multiset; }
}

bool Membrane::validate_non_default() const
{
	if (label_.empty() && parent_label == "SKIN")
	{
		return false;
	}
	return true;
}

void Efop::Membrane::push_child(std::string label)
{
	if (!validate_non_default())
	{
		throw std::invalid_argument("ERROR: Membrane object is not yet setup. It is in \"Default\" state.");
	}
	
	child_labels.push_back(label);
}

std::vector<std::string> Efop::Membrane::delete_child(std::string child_label)
{

	for (int i = 0; i < child_labels.size(); ++i)
	{
		if (child_label == child_labels[i])
		{
			child_labels.erase(child_labels.begin() + i);
		}
	}
	return child_labels;
}

void Membrane::simulate(const std::string multiset)
{
	if (!validate_non_default())
	{
		throw std::invalid_argument("ERROR: Membrane object is not yet setup. It is in \"Default\" state.");
	}
	
	if (Efop::Environ::Instance("").is_simulation_halt())
	{
		return;
	}

	accept_multiset(multiset);

	if (multiset_.empty())
	{
		multiset_.push_back("");
	}

	for (auto rule : rules_)
	{
		if (!Efop::Environ::Instance("").is_simulation_halt())
		{
			rule.apply(multiset_[0]);
		}
	}
}


void Membrane::set_rules(const std::vector<std::string>& rule_strings)
{
	if (!validate_non_default())
	{
		throw std::invalid_argument("ERROR: Membrane object is not yet setup. It is in \"Default\" state.");
	}

	for (const auto rule_string : rule_strings)
	{
		rules_.push_back(Rule::parse_rule_string(rule_string));
	}
}

/*
bool operator==(const Membrane& membrane1, const Membrane& membrane2)
{
	return membrane1.get_label() == membrane2.get_label();
}
*/
