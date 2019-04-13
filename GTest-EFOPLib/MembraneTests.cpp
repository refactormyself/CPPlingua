#include "pch.h"
#include "gtest/gtest.h"
#include "../EFOPLib/Membrane.h"
TEST(TestMembrane, TestSimulate_ErrorOnDefaultMembrane) {
	Efop::Membrane membrane{};
	EXPECT_EQ("", membrane.get_label());
	EXPECT_EQ("SKIN", membrane.get_parent_label());
	EXPECT_TRUE(membrane.get_child_labels().empty());
	EXPECT_TRUE(membrane.get_current_state().empty());
	ASSERT_FALSE(membrane.validate_non_default());
	ASSERT_THROW(membrane.simulate(""), std::invalid_argument);
}

TEST(TestMembrane, TestCreateRule_ErrorOnDefaultMembrane) {
	Efop::Membrane membrane{};
	EXPECT_EQ("", membrane.get_label());
	EXPECT_EQ("SKIN", membrane.get_parent_label());
	EXPECT_TRUE(membrane.get_child_labels().empty());
	EXPECT_TRUE(membrane.get_current_state().empty());
	ASSERT_FALSE(membrane.validate_non_default());
	ASSERT_THROW(membrane.set_rules({"a:[aa]"}), std::invalid_argument);
}

TEST(TestMembrane, TestAcceptMultiset_ErrorOnDefaultMembrane) {
	Efop::Membrane membrane{};
	EXPECT_EQ("", membrane.get_label());
	EXPECT_EQ("SKIN", membrane.get_parent_label());
	EXPECT_TRUE(membrane.get_child_labels().empty());
	EXPECT_TRUE(membrane.get_current_state().empty());
	ASSERT_FALSE(membrane.validate_non_default());
	ASSERT_THROW(membrane.accept_multiset("aabbcc"), std::invalid_argument);
}

TEST(TestMembrane, TestPushChild_ErrorOnDefaultMembrane) {
	Efop::Membrane membrane{};
	EXPECT_EQ("", membrane.get_label());
	EXPECT_EQ("SKIN", membrane.get_parent_label());
	EXPECT_TRUE(membrane.get_child_labels().empty());
	EXPECT_TRUE(membrane.get_current_state().empty());
	ASSERT_FALSE(membrane.validate_non_default());
	ASSERT_THROW(membrane.push_child("1"), std::invalid_argument);
}

TEST(TestMembrane, TestMembrane_DefaultState_EmptyChildren_NoRules) {	
	Efop::Membrane membrane("2", "1", {}, {});
	ASSERT_EQ("2", membrane.get_label());
	ASSERT_EQ("1", membrane.get_parent_label());
	ASSERT_TRUE(membrane.get_child_labels().empty());
	ASSERT_TRUE(membrane.get_current_state().empty());
	ASSERT_TRUE(membrane.validate_non_default());
	ASSERT_NO_THROW(membrane.set_rules({ "a:[aa]" }), std::invalid_argument);
	ASSERT_NO_THROW(membrane.accept_multiset("aabbcc"), std::invalid_argument);
	ASSERT_NO_THROW(membrane.simulate(""), std::invalid_argument);
	ASSERT_NO_THROW(membrane.push_child("1"), std::invalid_argument);
}

TEST(TestMembrane, TestMembrane_EmptyChildren_NoRules) {
	Efop::Membrane membrane("2", "1", {"aabb"}, {});
	ASSERT_EQ("2", membrane.get_label());
	ASSERT_EQ("1", membrane.get_parent_label());
	ASSERT_TRUE(membrane.get_child_labels().empty());
	ASSERT_TRUE(membrane.get_rules_strings().empty());
	ASSERT_EQ(membrane.get_current_state(), "aabb");
	ASSERT_TRUE(membrane.validate_non_default());
	ASSERT_NO_THROW(membrane.set_rules({ "a:[aa]" }), std::invalid_argument);
	ASSERT_NO_THROW(membrane.accept_multiset("aabbcc"), std::invalid_argument);
	ASSERT_NO_THROW(membrane.simulate(""), std::invalid_argument);
	ASSERT_NO_THROW(membrane.push_child("1"), std::invalid_argument);
}

TEST(TestMembrane, TestMembrane_EmptyChildren) {
	Efop::Membrane membrane("2", "1", { "aabb" }, {Efop::Rule::parse_rule_string("a:[aa]") });
	ASSERT_EQ("2", membrane.get_label());
	ASSERT_EQ("1", membrane.get_parent_label());
	ASSERT_TRUE(membrane.get_child_labels().empty());
	ASSERT_FALSE(membrane.get_rules_strings().empty());
	ASSERT_EQ(membrane.get_current_state(), "aabb");
	ASSERT_TRUE(membrane.validate_non_default());
	ASSERT_NO_THROW(membrane.set_rules({ "a:[aa]" }), std::invalid_argument);
	ASSERT_NO_THROW(membrane.accept_multiset("aabbcc"), std::invalid_argument);
	ASSERT_NO_THROW(membrane.simulate(""), std::invalid_argument);
	ASSERT_NO_THROW(membrane.push_child("1"), std::invalid_argument);
}

TEST(TestMembrane, TestMembrane_with_Children_Rule_HERE) {
	Efop::Membrane membrane("2", "1", { "abbacca" }, { Efop::Rule::parse_rule_string("a:[aa]") });
	ASSERT_EQ("2", membrane.get_label());
	ASSERT_EQ("1", membrane.get_parent_label());
	ASSERT_TRUE(membrane.get_child_labels().empty());
	ASSERT_FALSE(membrane.get_rules_strings().empty());
	ASSERT_EQ(membrane.get_current_state(), "abbacca");
	ASSERT_TRUE(membrane.validate_non_default());
	
	ASSERT_NO_THROW(membrane.push_child("1"), std::invalid_argument);
	ASSERT_NO_THROW(membrane.simulate(""), std::invalid_argument);
	

}
