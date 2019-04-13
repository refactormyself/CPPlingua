#pragma once
#include "Membrane.h"
#include "Environ.h"
#include <fstream>

namespace Efop
{

	void to_json(nlohmann::json & j, const Membrane mem)
	{
		std::vector<std::string> rules{};
		std::vector<Membrane> children{};

		nlohmann::json child_json;
		for (const auto child_label : mem.get_child_labels())
		{
			const auto child = Environ::Instance("").get_membrane_labeled(child_label);
			nlohmann::json i;
			to_json(i, child);
			child_json.push_back(i);
		}

		nlohmann::json rules_json;
		for (auto str : mem.get_rules_strings())
		{
			rules_json.push_back(str);
		}

		std::string label = mem.get_label();
		std::string parent_label = mem.get_parent_label();

		j = nlohmann::json{ {"label", label}, {"parent",  parent_label}, {"multiset", mem.get_current_state()},
							{"rules", rules_json}, {"children", child_json} };
	}

	//populate the referenced Membrane (from the pool)
	void from_json(const nlohmann::json & j, Membrane & p)
	{
		std::string label, parent, multiset;
		std::vector<std::string> rule_strings{};

		j.at("label").get_to(label);
		j.at("parent").get_to(parent);
		j.at("multiset").get_to(multiset);
		j.at("rules").get_to<std::vector<std::string>>(rule_strings);
		p.set_label(label);
		p.set_multiset(multiset);
		p.set_rules(rule_strings);

		for (const auto element : j["children"]) {
			nlohmann::json n = element;
			Membrane membrane{};
			membrane.set_parent(p.get_label());
			from_json(n, membrane);

			Environ::Instance("").add_membrane(membrane);			
			p.push_child(membrane.get_label());
		}
	}

	void to_json(nlohmann::json & j, const Environ & p)
	{
		nlohmann::json cells_json;

		if (p.get_membranes().size() != 0)
		{
			to_json(cells_json, p.get_membranes().front());
		}
		std::string m_set = p.get_current_state();
		// auto m_set = p.get_membranes()multiset.size() > 0 ? multiset[0] : "";
		j = nlohmann::json{ {"multiset", m_set}, {"SKIN", cells_json } };
	}

	void from_json(const nlohmann::json & json_membrane, std::vector<Membrane> & membranes)
	{

		membranes.push_back(Membrane());
		Membrane& membrane = membranes.back();

		std::string m_set{};
		json_membrane.at("multiset").get_to(m_set);
		if (!m_set.empty())
		{
			membrane.set_multiset(m_set);
		}

		std::string label{};
		json_membrane.at("label").get_to(label);
		if (!label.empty())
		{
			for (auto mem : membranes)
			{
				if (mem.get_label() == label)
				{
					membranes.pop_back();
					throw std::invalid_argument("ERROR (Json File): Membrane label already exists !!! \nMembrane label must be unique");
				}
			}
			membrane.set_label(label);
		}
		else {
			membranes.pop_back();
			throw std::invalid_argument("ERROR (Json File): Membrane label is Empty !!! \nAll membranes must have a label "); 
		}

		std::string parent_label{};
		if (!json_membrane.at("parent").is_null())
		{
			json_membrane.at("parent").get_to(parent_label);
		}	
		if (!parent_label.empty() && parent_label != "SKIN")
		{
			int parent_id = -1;
			for (int i = 0; i < membranes.size(); ++i)			
			{
				if (membranes[i].get_label() == parent_label)
				{
					parent_id = i;
					break;
				}
			}

			if (parent_id > -1)
			{
				membrane.set_parent(parent_label);
				membranes[parent_id].push_child(membrane.get_label());
			}
			else {
				membranes.pop_back();
				throw std::invalid_argument("ERROR (Json File): Parent does not exist, yet !!! \nMake sure the label is correct"); 
			}
		}
		else
		{
			if (membranes.size() > 1)
			{
				membranes.pop_back();
				throw std::invalid_argument("ERROR (Json File): The root membrane - SKIN exists already ");
			}

			parent_label = "SKIN";
		}
				
		nlohmann::json rule_strings = json_membrane.at("rules");
		if (rule_strings.is_array())
		{
			auto rules = rule_strings.get <std::vector<std::string>>();
			membrane.set_rules(rules);
		}
		else if (!rule_strings.is_null()) {
			membranes.pop_back();
			throw std::invalid_argument("ERROR (Json File): Membrane \"rules\" must be an array !!!"); 
		}

		nlohmann::json children = json_membrane.at("children");
		if (children.is_array())
		{
			for (auto child : children)
			{
				from_json(child, membranes);
			}			
		}
		else if (!children.is_null()){
			membranes.pop_back();
			throw std::invalid_argument("ERROR (Json File): Membrane \"children\" must be an array !!!"); 
		}

	}

	inline nlohmann::json save_environ_json()
	{
		nlohmann::json json_string;

		to_json(json_string, Environ::Instance(""));
		return json_string;
	}

	void load_environ_json(std::string file_path)
	{
		std::ifstream i(file_path);
		nlohmann::json json_string;
		i >> json_string;
		
		std::string environ_m_set{};
		json_string.at("multiset").get_to(environ_m_set);		

		std::vector<Membrane> membranes{};
		
		if (!json_string["SKIN"].is_null())
		{
			from_json(json_string["SKIN"], membranes);		
		}

		Environ::Instance("").set_state(environ_m_set);
		Environ::Instance("").reset_models(membranes);				
	}

}
