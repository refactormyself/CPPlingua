#pragma once
#include <string>
#include <vector>
#include "Membrane.h"

namespace Efop
{
	class Environ
	{

	public:
		
		static Environ& Instance(std::string model_string) {
			static Environ environ_instance;
			return environ_instance;
		}
			   
		// delete copy and move constructors and assign operators
		Environ(Environ const&) = delete;             // Copy construct
		Environ(Environ&&) = delete;                  // Move construct
		Environ& operator=(Environ const&) = delete;  // Copy assign
		Environ& operator=(Environ &&) = delete;      // Move assign

		const std::vector<Membrane> & get_membranes() const { return membranes_; }
		std::string get_current_state() const;
		std::vector<std::string> simulate(std::string multiset);
		void halt_all_simulation();
		void process_rule_output(std::string multiset, std::string command);
		Membrane & get_membrane_stored_at(const int index) { return membranes_.at(index); }
		Efop::Membrane& get_membrane_labeled(std::string str);
		std::vector<Membrane> add_membrane(Membrane membrane);
		std::vector<Membrane> delete_membrane(Membrane membrane);
		std::vector<Membrane> delete_membrane(std::shared_ptr<Membrane> membrane);
		std::vector<Membrane> delete_membrane_by_label(const std::string& cs);
		bool is_simulation_halt() const { return is_halt_; }
		void set_state(const std::string& str);
		void reset_models(const std::vector<Membrane>& vector);
	private:
		Environ() = default;
		~Environ() = default;
		
		std::vector<Membrane> membranes_{};
		bool is_halt_ = true;
		std::vector<std::string> multiset{};

		std::pair < std::string, std::vector<std::string>> parse_multiset_rules(std::string membrane_string);

	};
}