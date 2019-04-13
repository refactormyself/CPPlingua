#include "stdafx.h"
#include "Environ.h"
#include "util.h"
#include <regex>
#include <string>

using namespace Efop;

std::pair < std::string, std::vector<std::string>> Environ::parse_multiset_rules(std::string membrane_string)
{
	std::string ret_multiset{};
	std::string ret_rule_string{};

	auto string_split = split_string_at_first(membrane_string, "(");

	if (string_split.size() == 0)
	{//there is only multiset

		return { membrane_string, {} };
	}
	else if (string_split.size() == 1)
	{//there is no multiset only rules
		
		string_split[0].erase(string_split[0].size() - 1); //remove ")"
		auto rules_strings = split_string_repeating(string_split[0], ";"); //Split Rules ";"
		return { "", rules_strings };
		
	}
	else
	{//Es gibt multisets + rules_string  Z.B.- aabbc(a:[a, b->IN2, c->OUT}; aa:[a->OUT])
		
		string_split[1].erase(string_split[1].size() - 1); //remove ")"
		auto rules_strings = split_string_repeating(string_split[1], ";"); //Split Rules ";"

		return { string_split[0], rules_strings };

	}
}

std::string Environ::get_current_state() const
{
	std::string ret_value = "";
		
	if (!multiset.empty())
	{
		ret_value = multiset[0];
	}
	return ret_value;
}


void Environ::set_state(const std::string& str)
{
	if (multiset.size() > 0)
	{
		multiset[0] += str;
	}
	multiset.push_back(str);
}

void Environ::reset_models(const std::vector<Membrane>& mem_vector)
{
	multiset.clear();
	membranes_.clear();
	membranes_.assign(mem_vector.begin(), mem_vector.end());
}

std::vector<std::string> Environ::simulate(std::string multiset)
{
	if (membranes_.size() > 0)
	{
		is_halt_ = false;
		for (Membrane & membrane : membranes_)
		{
			membrane.simulate(multiset);
		}
	}
	return this->multiset;
}

void Efop::Environ::halt_all_simulation()
{
	is_halt_ = true;
}

void Environ::process_rule_output(std::string multiset, std::string command)
{
	// OUT, #2
	if (command == "OUT")
	{
		if (this->multiset.empty())
		{
			this->multiset.push_back(multiset);
		}
		else { this->multiset[0] += multiset; }
		halt_all_simulation();
	}
	else if (command.find("#") != std::string::npos)
	{
		throw std::invalid_argument("ERROR: SORRY membrane destroy rule is not yet supported !!!");
		/*auto destroy_cmd = split_string_at_first(command, "#");
		std::string word = "", mem2destroy = "";
		if (destroy_cmd.size() == 2)
		{
			word = destroy_cmd[0];
			mem2destroy = destroy_cmd[1];
		}
		else
		{
			mem2destroy = destroy_cmd[1];
		}
		for (auto & membrane : get_membranes())
		{
			if (membrane.get_label() == mem2destroy)
			{
				// destroy_membrane(multiset); 
			}
		}*/
	}
	else
	{
		throw std::invalid_argument("ERROR: Model String, may have not been properly formulated !!!");
	}
}

//Returns reference to the membrane if found, otherwise returns reference to a blank default Membrane object
Membrane& Environ::get_membrane_labeled(const std::string str)
{
	for (auto & membrane : membranes_)
	{
		if (str == membrane.get_label())
		{
			return membrane;
		}
	}

	Membrane empty_brane{};
	return empty_brane;
}

std::vector<Membrane> Efop::Environ::add_membrane(Membrane membrane)
{
	membranes_.push_back(membrane);
	const auto parent_label = membrane.get_parent_label();
	if (parent_label != "SKIN")
	{
		auto & parent = Environ::Instance("").get_membrane_labeled(parent_label);
		parent.push_child(membrane.get_label());
	}

	return membranes_;
}

std::vector<Membrane> Efop::Environ::delete_membrane(Membrane membrane)
{
	
	for (int i = 0; i < membranes_.size(); ++i)
	{
		if (membrane.get_label() == membranes_[i].get_label())
		{
			membranes_.erase(membranes_.begin() + i);
		}
	}
		
	return membranes_;
}

std::vector<Membrane> Efop::Environ::delete_membrane_by_label(const std::string& label)
{	
	for (int i = 0; i < membranes_.size(); ++i)
	{
		if (membranes_[i].get_label() == label)
		{
			if (membranes_[i].get_parent_label() != "SKIN")
			{
				//remove from parent
				Membrane& parent = get_membrane_labeled(membranes_[i].get_parent_label());
				parent.delete_child(label);
			}
			//remove it's children
			auto children = membranes_[i].get_child_labels();
			for (std::vector<std::string>::iterator iter = children.begin(); iter != children.end(); ++iter)
			{
				delete_membrane_by_label(*iter);
			}
			//now remove it
			membranes_.erase(membranes_.begin() + i);
			break;
		}
	}
	// return delete_membrane(membrane_ptr);	
	return membranes_;
}