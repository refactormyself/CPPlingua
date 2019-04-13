#include "pch.h"
#include "gtest/gtest.h"
#include "../EFOPLib/Environ.h"


TEST(TestEnviron, Test_Membrane_in_Environ) {
	auto& env = Efop::Environ::Instance("");
	Efop::Membrane membrane("1", "SKIN", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa]") });

	EXPECT_TRUE(env.get_current_state().empty());	
	ASSERT_TRUE(env.get_membranes().empty());
	env.add_membrane(membrane);
	ASSERT_FALSE(env.get_membranes().empty());
	env.reset_models({});
	ASSERT_TRUE(env.get_membranes().empty());
}

TEST(TestEnviron, Test_Membrane_in_Environ_search) {
	auto& env = Efop::Environ::Instance("");
	const Efop::Membrane membrane("1", "SKIN", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa]") });

	EXPECT_TRUE(env.get_current_state().empty());
	ASSERT_TRUE(env.get_membranes().empty());
	env.add_membrane(membrane);
	ASSERT_EQ(env.get_membrane_labeled("1").get_label(), "1");	
	ASSERT_EQ(env.get_membrane_stored_at(0).get_label(), "1");
}

TEST(TestEnviron, Test_1_Membrane_No_Child_HERE_rule) {
	auto& env1 = Efop::Environ::Instance("");
	const Efop::Membrane membrane("1", "SKIN", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa]") });
	env1.reset_models({membrane});
	ASSERT_EQ(env1.get_membrane_labeled("1").get_rules_strings()[0], "a:[aa]");
	env1.simulate("");
	ASSERT_EQ(env1.get_membrane_labeled("1").get_current_state(), "aabbaaccaa");

}

TEST(TestEnviron, Test_1_Membrane_No_Child_OUT_rule) {
	Efop::Environ & env2 = Efop::Environ::Instance("");
	// const Efop::Membrane membrane("1", "SKIN", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa],b:[b->OUT]") });
	const Efop::Membrane membrane("1", "SKIN", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa,b->OUT]") });
	env2.reset_models({ membrane });

	ASSERT_EQ(env2.get_membrane_labeled("1").get_rules_strings().size(), 1);
	ASSERT_EQ(env2.get_membrane_labeled("1").get_rules_strings()[0], "a:[aa,b->OUT]");
	
	env2.simulate("");
	ASSERT_EQ(env2.get_membrane_labeled("1").get_current_state(), "aabbaaccaa");
	ASSERT_EQ(env2.get_current_state(), "bbbbbb");
}

// TEST(TestEnviron, Test_1_Membrane_with_Children_HERE_rule) {
// 	Efop::Environ & env = Efop::Environ::Instance("");
// 	Efop::Membrane membrane1("1", "SKIN", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa]") });
// 	Efop::Membrane membrane2("2", "1", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa]") });
// 	Efop::Membrane membrane3("3", "1", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa]") });
//
// }
//
// TEST(TestEnviron, Test_1_Membrane_with_Children_HERE_OUT_rules) {
// 	Efop::Environ & env = Efop::Environ::Instance("");
// 	Efop::Membrane membrane1("1", "SKIN", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa]") });
// 	Efop::Membrane membrane2("2", "1", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa]") });
// 	Efop::Membrane membrane3("3", "2", {}, { Efop::Rule::parse_rule_string("a:[aa]") });
//
// }

TEST(TestEnviron, Test_1_Membrane_with_Children_HERE_OUT_IN_rules) {
	Efop::Environ & env3 = Efop::Environ::Instance("");
	const Efop::Membrane membrane1("1", "SKIN", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa]") });
	const Efop::Membrane membrane2("2", "1", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[ka->IN3]") });
	const Efop::Membrane membrane3("3", "2", {}, { Efop::Rule::parse_rule_string("a:[aa->OUT]") });
	
	env3.reset_models({ membrane1, membrane2, membrane3 });
	env3.simulate("");
	
	ASSERT_EQ(env3.get_membrane_labeled("1").get_current_state(), "aabbaaccaa");
	ASSERT_EQ(env3.get_membrane_labeled("2").get_current_state(), "abbacca");
	ASSERT_EQ(env3.get_membrane_labeled("3").get_current_state(), "kakaka");
	ASSERT_EQ(env3.get_current_state(), "aaaaaa");
}