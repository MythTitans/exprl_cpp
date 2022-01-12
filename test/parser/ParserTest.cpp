#include "doctest/doctest.h"

#include "../../src/eval/include/Context.h"
#include "../../src/parser/include/Parser.h"

using namespace std;
using namespace mythtitans;
using namespace mythtitans::exprl::parser;
using namespace doctest;

static constexpr double EPSILON = 0.000001;

static Parser parser;
static exprl::eval::Context context;

TEST_CASE("Literal parsing test")
{
    CHECK(parser.parse("true")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("false")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("1")->evaluateAsInteger(context) == 1);
    CHECK(parser.parse("-1")->evaluateAsInteger(context) == -1);
    CHECK(parser.parse("1")->evaluateAsDecimal(context) == Approx(1).epsilon(EPSILON));
    CHECK(parser.parse("-1")->evaluateAsDecimal(context) == Approx(-1).epsilon(EPSILON));
    CHECK(parser.parse("1.5")->evaluateAsDecimal(context) == Approx(1.5).epsilon(EPSILON));
    CHECK(parser.parse("-1.5")->evaluateAsDecimal(context) == Approx(-1.5).epsilon(EPSILON));
    CHECK(parser.parse("'abcdef'")->evaluateAsText(context) == "abcdef");
}

TEST_CASE("Not parsing test")
{
    CHECK(parser.parse("not(false)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("not(true)")->evaluateAsBoolean(context) == false);
}

TEST_CASE("And parsing test")
{
    CHECK(parser.parse("and(false, false)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("and(false, true)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("and(true, false)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("and(true, true)")->evaluateAsBoolean(context) == true);

    CHECK(parser.parse("and(false, false, false)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("and(false, false, true)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("and(false, true, false)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("and(false, true, true)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("and(true, false, false)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("and(true, false, true)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("and(true, true, false)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("and(true, true, true)")->evaluateAsBoolean(context) == true);
}

TEST_CASE("Or parsing test")
{
    CHECK(parser.parse("or(false, false)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("or(false, true)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("or(true, false)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("or(true, true)")->evaluateAsBoolean(context) == true);

    CHECK(parser.parse("or(false, false, false)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("or(false, false, true)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("or(false, true, false)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("or(false, true, true)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("or(true, false, false)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("or(true, false, true)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("or(true, true, false)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("or(true, true, true)")->evaluateAsBoolean(context) == true);
}

TEST_CASE("Add parsing test")
{
    CHECK(parser.parse("add(1, 2)")->evaluateAsInteger(context) == 3);
    CHECK(parser.parse("add(1, -2)")->evaluateAsInteger(context) == -1);
    CHECK(parser.parse("add(1, 2, 3)")->evaluateAsInteger(context) == 6);
    CHECK(parser.parse("add(1, 2, -3)")->evaluateAsInteger(context) == 0);
    CHECK(parser.parse("add(1, -2, -3)")->evaluateAsInteger(context) == -4);

    CHECK(parser.parse("add(1, 2)")->evaluateAsDecimal(context) == Approx(3).epsilon(EPSILON));
    CHECK(parser.parse("add(1, -2)")->evaluateAsDecimal(context) == Approx(-1).epsilon(EPSILON));
    CHECK(parser.parse("add(1, 2, 3)")->evaluateAsDecimal(context) == Approx(6).epsilon(EPSILON));
    CHECK(parser.parse("add(1, 2, -3)")->evaluateAsDecimal(context) == Approx(0).epsilon(EPSILON));
    CHECK(parser.parse("add(1, -2, -3)")->evaluateAsDecimal(context) == Approx(-4).epsilon(EPSILON));
}

TEST_CASE("Sub parsing test")
{
    CHECK(parser.parse("sub(1, 2)")->evaluateAsInteger(context) == -1);
    CHECK(parser.parse("sub(1, -2)")->evaluateAsInteger(context) == 3);

    CHECK(parser.parse("sub(1, 2)")->evaluateAsDecimal(context) == Approx(-1).epsilon(EPSILON));
    CHECK(parser.parse("sub(1, -2)")->evaluateAsDecimal(context) == Approx(3).epsilon(EPSILON));
}

TEST_CASE("Mul parsing test")
{
    CHECK(parser.parse("mul(2, 3)")->evaluateAsInteger(context) == 6);
    CHECK(parser.parse("mul(2, -3)")->evaluateAsInteger(context) == -6);
    CHECK(parser.parse("mul(2, 3, 4)")->evaluateAsInteger(context) == 24);
    CHECK(parser.parse("mul(2, 3, -4)")->evaluateAsInteger(context) == -24);

    CHECK(parser.parse("mul(2, 3)")->evaluateAsDecimal(context) == Approx(6).epsilon(EPSILON));
    CHECK(parser.parse("mul(2, -3)")->evaluateAsDecimal(context) == Approx(-6).epsilon(EPSILON));
    CHECK(parser.parse("mul(2, 3, 4)")->evaluateAsDecimal(context) == Approx(24).epsilon(EPSILON));
    CHECK(parser.parse("mul(2, 3, -4)")->evaluateAsDecimal(context) == Approx(-24).epsilon(EPSILON));
}

TEST_CASE("Div parsing test")
{
    CHECK(parser.parse("div(6, 2)")->evaluateAsInteger(context) == 3);
    CHECK(parser.parse("div(6, -2)")->evaluateAsInteger(context) == -3);
    CHECK(parser.parse("div(6, 4)")->evaluateAsInteger(context) == 1);

    CHECK(parser.parse("div(6, 2)")->evaluateAsDecimal(context) == Approx(3).epsilon(EPSILON));
    CHECK(parser.parse("div(6, -2)")->evaluateAsDecimal(context) == Approx(-3).epsilon(EPSILON));
    CHECK(parser.parse("div(6, 4)")->evaluateAsDecimal(context) == Approx(1.5).epsilon(EPSILON));
}

TEST_CASE("Mod parsing test")
{
    CHECK(parser.parse("mod(6, 2)")->evaluateAsInteger(context) == 0);
    CHECK(parser.parse("mod(5, 2)")->evaluateAsInteger(context) == 1);

    CHECK(parser.parse("mod(6, 2)")->evaluateAsDecimal(context) == Approx(0).epsilon(EPSILON));
    CHECK(parser.parse("mod(5, 2)")->evaluateAsDecimal(context) == Approx(1).epsilon(EPSILON));
}

TEST_CASE("Starts parsing test")
{
    CHECK(parser.parse("starts('abcdef', '')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("starts('abcdef', 'a')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("starts('abcdef', 'ab')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("starts('abcdef', 'b')")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("starts('abcdef', 'bc')")->evaluateAsBoolean(context) == false);
}

TEST_CASE("Ends parsing test")
{
    CHECK(parser.parse("ends('abcdef', '')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("ends('abcdef', 'f')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("ends('abcdef', 'ef')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("ends('abcdef', 'e')")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("ends('abcdef', 'de')")->evaluateAsBoolean(context) == false);
}

TEST_CASE("In parsing test")
{
    CHECK(parser.parse("in('abcdef', '')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("in('abcdef', 'a')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("in('abcdef', 'ab')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("in('abcdef', 'b')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("in('abcdef', 'bc')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("in('abcdef', 'e')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("in('abcdef', 'ef')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("in('abcdef', 'ac')")->evaluateAsBoolean(context) == false);
}

TEST_CASE("Substr parsing test")
{
    CHECK(parser.parse("substr('abcdef', 0, 6)")->evaluateAsText(context) == "abcdef");
    CHECK(parser.parse("substr('abcdef', 0, 5)")->evaluateAsText(context) == "abcde");
    CHECK(parser.parse("substr('abcdef', 1, 6)")->evaluateAsText(context) == "bcdef");
    CHECK(parser.parse("substr('abcdef', 0, -1)")->evaluateAsText(context) == "abcdef");
    CHECK(parser.parse("substr('abcdef', -3, -1)")->evaluateAsText(context) == "ef");
    CHECK(parser.parse("substr('abcdef', -2, -1)")->evaluateAsText(context) == "f");
}

TEST_CASE("Substrl parsing test")
{
    CHECK(parser.parse("substrl('abcdef', 0, 6)")->evaluateAsText(context) == "abcdef");
    CHECK(parser.parse("substrl('abcdef', 0, 5)")->evaluateAsText(context) == "abcde");
    CHECK(parser.parse("substrl('abcdef', 1, 5)")->evaluateAsText(context) == "bcdef");
    CHECK(parser.parse("substrl('abcdef', 5, 1)")->evaluateAsText(context) == "f");
    CHECK(parser.parse("substrl('abcdef', -2, 1)")->evaluateAsText(context) == "f");
    CHECK(parser.parse("substrl('abcdef', -3, 2)")->evaluateAsText(context) == "ef");
}

TEST_CASE("Len parsing test")
{
    CHECK(parser.parse("len('abcdef')")->evaluateAsInteger(context) == 6);
    CHECK(parser.parse("len('abcde')")->evaluateAsInteger(context) == 5);
    CHECK(parser.parse("len('')")->evaluateAsInteger(context) == 0);

    CHECK(parser.parse("len('abcdef')")->evaluateAsDecimal(context) == Approx(6).epsilon(EPSILON));
    CHECK(parser.parse("len('abcde')")->evaluateAsDecimal(context) == Approx(5).epsilon(EPSILON));
    CHECK(parser.parse("len('')")->evaluateAsDecimal(context) == Approx(0).epsilon(EPSILON));
}

TEST_CASE("Eq parsing test")
{
    CHECK(parser.parse("eq(true, true)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("eq(true, false)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("eq(1, 1)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("eq(1, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("eq(1, 1)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("eq(1, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("eq('abcdef', 'abcdef')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("eq('abcdef', 'abcd')")->evaluateAsBoolean(context) == false);
}

TEST_CASE("Neq parsing test")
{
    CHECK(parser.parse("neq(true, true)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("neq(true, false)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("neq(1, 1)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("neq(1, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("neq(1, 1)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("neq(1, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("neq('abcdef', 'abcdef')")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("neq('abcdef', 'abcd')")->evaluateAsBoolean(context) == true);
}

TEST_CASE("Lt parsing test")
{
    CHECK(parser.parse("lt(1, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("lt(2, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("lt(3, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("lt(1, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("lt(2, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("lt(3, 2)")->evaluateAsBoolean(context) == false);
}

TEST_CASE("Lte parsing test")
{
    CHECK(parser.parse("lte(1, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("lte(2, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("lte(3, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("lte(1, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("lte(2, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("lte(3, 2)")->evaluateAsBoolean(context) == false);
}

TEST_CASE("Gt parsing test")
{
    CHECK(parser.parse("gt(1, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("gt(2, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("gt(3, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("gt(1, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("gt(2, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("gt(3, 2)")->evaluateAsBoolean(context) == true);
}

TEST_CASE("Gte parsing test")
{
    CHECK(parser.parse("gte(1, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("gte(2, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("gte(3, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("gte(1, 2)")->evaluateAsBoolean(context) == false);
    CHECK(parser.parse("gte(2, 2)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("gte(3, 2)")->evaluateAsBoolean(context) == true);
}

TEST_CASE("Min parsing test")
{
    CHECK(parser.parse("min(0, 1)")->evaluateAsInteger(context) == 0);
    CHECK(parser.parse("min(0, -1)")->evaluateAsInteger(context) == -1);
    CHECK(parser.parse("min(0, -1, -5)")->evaluateAsInteger(context) == -5);

    CHECK(parser.parse("min(0, 1)")->evaluateAsDecimal(context) == Approx(0).epsilon(EPSILON));
    CHECK(parser.parse("min(0, -1)")->evaluateAsDecimal(context) == Approx(-1).epsilon(EPSILON));
    CHECK(parser.parse("min(0, -1, -5)")->evaluateAsDecimal(context) == Approx(-5).epsilon(EPSILON));
}

TEST_CASE("Max parsing test")
{
    CHECK(parser.parse("max(0, 1)")->evaluateAsInteger(context) == 1);
    CHECK(parser.parse("max(0, -1)")->evaluateAsInteger(context) == 0);
    CHECK(parser.parse("max(0, -1, 5)")->evaluateAsInteger(context) == 5);

    CHECK(parser.parse("max(0, 1)")->evaluateAsDecimal(context) == Approx(1).epsilon(EPSILON));
    CHECK(parser.parse("max(0, -1)")->evaluateAsDecimal(context) == Approx(0).epsilon(EPSILON));
    CHECK(parser.parse("max(0, -1, 5)")->evaluateAsDecimal(context) == Approx(5).epsilon(EPSILON));
}

TEST_CASE("Var parsing test")
{
    context.setVariable("variable-boolean", true);
    context.setVariable("variable-integer", 1);
    context.setVariable("variable-decimal", 1.5);
    context.setVariable("variable-text", "abcdef");

    CHECK(parser.parse("var('variable-boolean')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("var('variable-integer')")->evaluateAsInteger(context) == 1);
    CHECK(parser.parse("var('variable-decimal')")->evaluateAsDecimal(context) == Approx(1.5).epsilon(EPSILON));
    CHECK(parser.parse("var('variable-text')")->evaluateAsText(context) == "abcdef");
}

TEST_CASE("Cond parsing test")
{
    CHECK(parser.parse("cond(true, true, false)")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("cond(false, true, false)")->evaluateAsBoolean(context) == false);

    CHECK(parser.parse("cond(true, 1, 2)")->evaluateAsInteger(context) == 1);
    CHECK(parser.parse("cond(false, 1, 2)")->evaluateAsInteger(context) == 2);

    CHECK(parser.parse("cond(true, 1.5, 2.5)")->evaluateAsDecimal(context) == Approx(1.5).epsilon(EPSILON));
    CHECK(parser.parse("cond(false, 1.5, 2.5)")->evaluateAsDecimal(context) == Approx(2.5).epsilon(EPSILON));

    CHECK(parser.parse("cond(true, 'a', 'b')")->evaluateAsText(context) == "a");
    CHECK(parser.parse("cond(false, 'a', 'b')")->evaluateAsText(context) == "b");
}

TEST_CASE("Concat parsing test")
{
    CHECK(parser.parse("concat('abc', 'def')")->evaluateAsText(context) == "abcdef");
    CHECK(parser.parse("concat('abc', '')")->evaluateAsText(context) == "abc");
    CHECK(parser.parse("concat('', 'def')")->evaluateAsText(context) == "def");

    CHECK(parser.parse("concat('abc', 'def', 'ghi')")->evaluateAsText(context) == "abcdefghi");
}

TEST_CASE("Debug parsing test")
{
    CHECK(parser.parse("debug(true, 'boolean')")->evaluateAsBoolean(context) == true);
    CHECK(parser.parse("debug(12, 'integer')")->evaluateAsInteger(context) == 12);
    CHECK(parser.parse("debug(15.5, 'decimal')")->evaluateAsDecimal(context) == Approx(15.5).epsilon(EPSILON));
    CHECK(parser.parse("debug('abcdef', 'text')")->evaluateAsText(context) == "abcdef");
}

TEST_CASE("Complex expression parsing test")
{
    CHECK(parser.parse("cond(and(true, true), 'abcdef', '')")->evaluateAsText(context) == "abcdef");
    CHECK(parser.parse("cond(and(true, false), 'abcdef', '')")->evaluateAsText(context) == "");

    CHECK(parser.parse("len(substr('test', 0, sub(len('test'), 1)))")->evaluateAsInteger(context) == 3);
    CHECK(parser.parse("len(substr('test', add(0, 1), -1))")->evaluateAsInteger(context) == 3);
}

TEST_CASE("Text literal escape parsing test")
{
    CHECK(parser.parse("'add(1, 2)'")->evaluateAsText(context) == "add(1, 2)");
    CHECK(parser.parse("len('add(1, 2)')")->evaluateAsInteger(context) == 9);
}

TEST_CASE("Invalid expression parsing test")
{
    CHECK_THROWS_AS(parser.parse("'test"), ParsingException);
    CHECK_THROWS_AS(parser.parse("test'"), ParsingException);
    CHECK_THROWS_AS(parser.parse("("), ParsingException);
    CHECK_THROWS_AS(parser.parse("(("), ParsingException);
    CHECK_THROWS_AS(parser.parse(")"), ParsingException);
    CHECK_THROWS_AS(parser.parse("))"), ParsingException);
    CHECK_THROWS_AS(parser.parse("()"), ParsingException);
    CHECK_THROWS_AS(parser.parse("i(2)"), ParsingException);
    CHECK_THROWS_AS(parser.parse("42a"), ParsingException);
    CHECK_THROWS_AS(parser.parse("add(1,"), ParsingException);
    CHECK_THROWS_AS(parser.parse("add(1, 2"), ParsingException);
    CHECK_THROWS_AS(parser.parse("42'test'"), ParsingException);
    CHECK_THROWS_AS(parser.parse("'test'42"), ParsingException);
    CHECK_THROWS_AS(parser.parse("not(true, true)"), ParsingException);
    CHECK_THROWS_AS(parser.parse("and(true)"), ParsingException);
}