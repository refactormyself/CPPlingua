#include "pch.h"
#include "gtest/gtest.h"
#include "../EFOPLib/Rule.h"

void throw_error_on_default_rule()
{
	Efop::Rule rule{};
	std::string word = "aa";
	rule.apply(word);
}

void create_rule_and_apply_to_word(const std::string & rule_string, std::string & word)
{
	auto rule = Efop::Rule::parse_rule_string(rule_string);
	rule.apply(word);
}

TEST(TestRule, TestCreationErrorOnDefaultRule) {
	ASSERT_THROW(throw_error_on_default_rule(), std::invalid_argument);
}

TEST(TestRule, TestCreationErrorOnEmptyString) {
	ASSERT_THROW(Efop::Rule rule = Efop::Rule::parse_rule_string(""), std::invalid_argument);
}

TEST(TestRule, TestCreationErrorOn_Illformed_RuleString) {
	ASSERT_THROW(Efop::Rule rule = Efop::Rule::parse_rule_string("a:aa"), std::invalid_argument);
}

TEST(TestRule, TestRuleCreation_HERE) {
	Efop::Rule rule;
	ASSERT_NO_THROW(rule = Efop::Rule::parse_rule_string("a:[aa]"), std::invalid_argument);
	ASSERT_EQ(rule.to_string(), "a:[aa]");
}

TEST(TestRule, TestRuleCreation_IN) {
	Efop::Rule rule;
	ASSERT_NO_THROW(rule = Efop::Rule::parse_rule_string("a:[aa->IN2]"), std::invalid_argument);
	ASSERT_EQ(rule.to_string(), "a:[aa->IN2]");
}

TEST(TestRule, TestRuleCreation_OUT) {
	Efop::Rule rule;
	ASSERT_NO_THROW(rule = Efop::Rule::parse_rule_string("a:[aa->OUT]"), std::invalid_argument);
	ASSERT_EQ(rule.to_string(), "a:[aa->OUT]");
}

TEST(TestRule, TestRuleApply_HERE) {
	Efop::Rule rule;
	ASSERT_NO_THROW(rule = Efop::Rule::parse_rule_string("a:[aa]"), std::invalid_argument);
	std::string word = "baba";
	rule.apply(word);
	ASSERT_EQ(word, "baabaa");
}

TEST(TestRule, TestRuleApply_HERE_Two_Iterations) {
	Efop::Rule rule;
	ASSERT_NO_THROW(rule = Efop::Rule::parse_rule_string("a:[aa]"), std::invalid_argument);
	std::string word = "baba";
	rule.apply(word);
	EXPECT_EQ(word, "baabaa");
	rule.apply(word);
	ASSERT_EQ(word, "baaaabaaaa");
}