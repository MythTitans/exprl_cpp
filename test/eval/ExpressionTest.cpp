#include "doctest/doctest.h"

#include "../../src/eval/include/Context.h"

#include "../../src/eval/impl/include/AddExpression.h"
#include "../../src/eval/impl/include/AndExpression.h"
#include "../../src/eval/impl/include/ConcatExpression.h"
#include "../../src/eval/impl/include/CondExpression.h"
#include "../../src/eval/impl/include/DebugExpression.h"
#include "../../src/eval/impl/include/DivExpression.h"
#include "../../src/eval/impl/include/EndsExpression.h"
#include "../../src/eval/impl/include/EqExpression.h"
#include "../../src/eval/impl/include/GteExpression.h"
#include "../../src/eval/impl/include/GtExpression.h"
#include "../../src/eval/impl/include/InExpression.h"
#include "../../src/eval/impl/include/LenExpression.h"
#include "../../src/eval/impl/include/LiteralExpression.h"
#include "../../src/eval/impl/include/LteExpression.h"
#include "../../src/eval/impl/include/LtExpression.h"
#include "../../src/eval/impl/include/MaxExpression.h"
#include "../../src/eval/impl/include/MinExpression.h"
#include "../../src/eval/impl/include/ModExpression.h"
#include "../../src/eval/impl/include/MulExpression.h"
#include "../../src/eval/impl/include/NeqExpression.h"
#include "../../src/eval/impl/include/NotExpression.h"
#include "../../src/eval/impl/include/OrExpression.h"
#include "../../src/eval/impl/include/StartsExpression.h"
#include "../../src/eval/impl/include/SubExpression.h"
#include "../../src/eval/impl/include/SubstrExpression.h"
#include "../../src/eval/impl/include/SubstrlExpression.h"
#include "../../src/eval/impl/include/VarExpression.h"

using namespace std;
using namespace mythtitans::exprl;
using namespace mythtitans::exprl::eval;
using namespace mythtitans::exprl::eval::impl;
using namespace doctest;

static constexpr double EPSILON = 0.000001;

static eval::Context context;

TEST_CASE("Literal test")
{
    CHECK(make_literal(true)->evaluateAsBoolean(context) == true);
    CHECK(make_literal(false)->evaluateAsBoolean(context) == false);
    CHECK(make_literal(1)->evaluateAsInteger(context) == 1);
    CHECK(make_literal(-1)->evaluateAsInteger(context) == -1);
    CHECK(make_literal(1)->evaluateAsDecimal(context) == Approx(1).epsilon(EPSILON));
    CHECK(make_literal(-1)->evaluateAsDecimal(context) == Approx(-1).epsilon(EPSILON));
    CHECK(make_literal(1.0)->evaluateAsDecimal(context) == Approx(1.0).epsilon(EPSILON));
    CHECK(make_literal(-1.0)->evaluateAsDecimal(context) == Approx(-1.0).epsilon(EPSILON));
    CHECK(make_literal("abcdef")->evaluateAsText(context) == "abcdef");

    CHECK(make_literal(true)->getExpressionName() == "true");
    CHECK(make_literal(false)->getExpressionName() == "false");
    CHECK(make_literal(1)->getExpressionName() == "1");
    CHECK(make_literal(1.0)->getExpressionName() == "1.000000");
    CHECK(make_literal("abcdef")->getExpressionName() == "abcdef");
}

TEST_CASE("Not test")
{
    CHECK(make_not(make_literal(false))->evaluateAsBoolean(context) == true);
    CHECK(make_not(make_literal(true))->evaluateAsBoolean(context) == false);

    CHECK(make_not(make_literal(true))->getExpressionName() == "not");
}

TEST_CASE("And test")
{
    CHECK(make_and(make_literal(false), make_literal(false))->evaluateAsBoolean(context) == false);
    CHECK(make_and(make_literal(false), make_literal(true))->evaluateAsBoolean(context) == false);
    CHECK(make_and(make_literal(true), make_literal(false))->evaluateAsBoolean(context) == false);
    CHECK(make_and(make_literal(true), make_literal(true))->evaluateAsBoolean(context) == true);

    CHECK(make_and(make_literal(false), make_literal(false), make_literal(false))->evaluateAsBoolean(context) == false);
    CHECK(make_and(make_literal(false), make_literal(false), make_literal(true))->evaluateAsBoolean(context) == false);
    CHECK(make_and(make_literal(false), make_literal(true), make_literal(false))->evaluateAsBoolean(context) == false);
    CHECK(make_and(make_literal(false), make_literal(true), make_literal(true))->evaluateAsBoolean(context) == false);
    CHECK(make_and(make_literal(true), make_literal(false), make_literal(false))->evaluateAsBoolean(context) == false);
    CHECK(make_and(make_literal(true), make_literal(false), make_literal(true))->evaluateAsBoolean(context) == false);
    CHECK(make_and(make_literal(true), make_literal(true), make_literal(false))->evaluateAsBoolean(context) == false);
    CHECK(make_and(make_literal(true), make_literal(true), make_literal(true))->evaluateAsBoolean(context) == true);

    CHECK(make_and(make_literal(true), make_literal(true))->getExpressionName() == "and");
}

TEST_CASE("Or test")
{
    CHECK(make_or(make_literal(false), make_literal(false))->evaluateAsBoolean(context) == false);
    CHECK(make_or(make_literal(false), make_literal(true))->evaluateAsBoolean(context) == true);
    CHECK(make_or(make_literal(true), make_literal(false))->evaluateAsBoolean(context) == true);
    CHECK(make_or(make_literal(true), make_literal(true))->evaluateAsBoolean(context) == true);

    CHECK(make_or(make_literal(false), make_literal(false), make_literal(false))->evaluateAsBoolean(context) == false);
    CHECK(make_or(make_literal(false), make_literal(false), make_literal(true))->evaluateAsBoolean(context) == true);
    CHECK(make_or(make_literal(false), make_literal(true), make_literal(false))->evaluateAsBoolean(context) == true);
    CHECK(make_or(make_literal(false), make_literal(true), make_literal(true))->evaluateAsBoolean(context) == true);
    CHECK(make_or(make_literal(true), make_literal(false), make_literal(false))->evaluateAsBoolean(context) == true);
    CHECK(make_or(make_literal(true), make_literal(false), make_literal(true))->evaluateAsBoolean(context) == true);
    CHECK(make_or(make_literal(true), make_literal(true), make_literal(false))->evaluateAsBoolean(context) == true);
    CHECK(make_or(make_literal(true), make_literal(true), make_literal(true))->evaluateAsBoolean(context) == true);

    CHECK(make_or(make_literal(true), make_literal(true))->getExpressionName() == "or");
}

TEST_CASE("Add test")
{
    CHECK(make_add(make_literal(1), make_literal(2))->evaluateAsInteger(context) == 3);
    CHECK(make_add(make_literal(1), make_literal(-2))->evaluateAsInteger(context) == -1);
    CHECK(make_add(make_literal(1), make_literal(2), make_literal(3))->evaluateAsInteger(context) == 6);
    CHECK(make_add(make_literal(1), make_literal(2), make_literal(-3))->evaluateAsInteger(context) == 0);
    CHECK(make_add(make_literal(1), make_literal(-2), make_literal(-3))->evaluateAsInteger(context) == -4);

    CHECK(make_add(make_literal(1), make_literal(2))->evaluateAsDecimal(context) == Approx(3).epsilon(EPSILON));
    CHECK(make_add(make_literal(1), make_literal(-2))->evaluateAsDecimal(context) == Approx(-1).epsilon(EPSILON));
    CHECK(make_add(make_literal(1), make_literal(2), make_literal(3))->evaluateAsDecimal(context) ==
          Approx(6).epsilon(EPSILON));
    CHECK(make_add(make_literal(1), make_literal(2), make_literal(-3))->evaluateAsDecimal(context) ==
          Approx(0).epsilon(EPSILON));
    CHECK(make_add(make_literal(1), make_literal(-2), make_literal(-3))->evaluateAsDecimal(context) ==
          Approx(-4).epsilon(EPSILON));

    CHECK(make_add(make_literal(1), make_literal(2))->getExpressionName() == "add");
}

TEST_CASE("Sub test")
{
    CHECK(make_sub(make_literal(1), make_literal(2))->evaluateAsInteger(context) == -1);
    CHECK(make_sub(make_literal(1), make_literal(-2))->evaluateAsInteger(context) == 3);

    CHECK(make_sub(make_literal(1), make_literal(2))->evaluateAsDecimal(context) == Approx(-1).epsilon(EPSILON));
    CHECK(make_sub(make_literal(1), make_literal(-2))->evaluateAsDecimal(context) == Approx(3).epsilon(EPSILON));

    CHECK(make_sub(make_literal(2), make_literal(1))->getExpressionName() == "sub");
}

TEST_CASE("Mul test")
{
    CHECK(make_mul(make_literal(2), make_literal(3))->evaluateAsInteger(context) == 6);
    CHECK(make_mul(make_literal(2), make_literal(-3))->evaluateAsInteger(context) == -6);
    CHECK(make_mul(make_literal(2), make_literal(3), make_literal(4))->evaluateAsInteger(context) == 24);
    CHECK(make_mul(make_literal(2), make_literal(3), make_literal(-4))->evaluateAsInteger(context) == -24);

    CHECK(make_mul(make_literal(2), make_literal(3))->evaluateAsDecimal(context) == Approx(6).epsilon(EPSILON));
    CHECK(make_mul(make_literal(2), make_literal(-3))->evaluateAsDecimal(context) == Approx(-6).epsilon(EPSILON));
    CHECK(make_mul(make_literal(2), make_literal(3), make_literal(4))->evaluateAsDecimal(context) ==
          Approx(24).epsilon(EPSILON));
    CHECK(make_mul(make_literal(2), make_literal(3), make_literal(-4))->evaluateAsDecimal(context) ==
          Approx(-24).epsilon(EPSILON));

    CHECK(make_mul(make_literal(1), make_literal(2))->getExpressionName() == "mul");
}

TEST_CASE("Div test")
{
    CHECK(make_div(make_literal(6), make_literal(2))->evaluateAsInteger(context) == 3);
    CHECK(make_div(make_literal(6), make_literal(-2))->evaluateAsInteger(context) == -3);
    CHECK(make_div(make_literal(6), make_literal(4))->evaluateAsInteger(context) == 1);

    CHECK(make_div(make_literal(6), make_literal(2))->evaluateAsDecimal(context) == Approx(3).epsilon(EPSILON));
    CHECK(make_div(make_literal(6), make_literal(-2))->evaluateAsDecimal(context) == Approx(-3).epsilon(EPSILON));
    CHECK(make_div(make_literal(6), make_literal(4))->evaluateAsDecimal(context) == Approx(1.5).epsilon(EPSILON));

    CHECK(make_div(make_literal(2), make_literal(2))->getExpressionName() == "div");
}

TEST_CASE("Mod test")
{
    CHECK(make_mod(make_literal(6), make_literal(2))->evaluateAsInteger(context) == 0);
    CHECK(make_mod(make_literal(5), make_literal(2))->evaluateAsInteger(context) == 1);

    CHECK(make_mod(make_literal(6), make_literal(2))->evaluateAsDecimal(context) == Approx(0).epsilon(EPSILON));
    CHECK(make_mod(make_literal(5), make_literal(2))->evaluateAsDecimal(context) == Approx(1).epsilon(EPSILON));

    CHECK(make_mod(make_literal(2), make_literal(2))->getExpressionName() == "mod");
}

TEST_CASE("Starts test")
{
    CHECK(make_starts(make_literal("abcdef"), make_literal(""))->evaluateAsBoolean(context) == true);
    CHECK(make_starts(make_literal("abcdef"), make_literal("a"))->evaluateAsBoolean(context) == true);
    CHECK(make_starts(make_literal("abcdef"), make_literal("ab"))->evaluateAsBoolean(context) == true);
    CHECK(make_starts(make_literal("abcdef"), make_literal("b"))->evaluateAsBoolean(context) == false);
    CHECK(make_starts(make_literal("abcdef"), make_literal("bc"))->evaluateAsBoolean(context) == false);

    CHECK(make_starts(make_literal("abcdef"), make_literal("ab"))->getExpressionName() == "starts");
}

TEST_CASE("Ends test")
{
    CHECK(make_ends(make_literal("abcdef"), make_literal(""))->evaluateAsBoolean(context) == true);
    CHECK(make_ends(make_literal("abcdef"), make_literal("f"))->evaluateAsBoolean(context) == true);
    CHECK(make_ends(make_literal("abcdef"), make_literal("ef"))->evaluateAsBoolean(context) == true);
    CHECK(make_ends(make_literal("abcdef"), make_literal("e"))->evaluateAsBoolean(context) == false);
    CHECK(make_ends(make_literal("abcdef"), make_literal("de"))->evaluateAsBoolean(context) == false);

    CHECK(make_ends(make_literal("abcdef"), make_literal("ab"))->getExpressionName() == "ends");
}

TEST_CASE("In test")
{
    CHECK(make_in(make_literal("abcdef"), make_literal(""))->evaluateAsBoolean(context) == true);
    CHECK(make_in(make_literal("abcdef"), make_literal("a"))->evaluateAsBoolean(context) == true);
    CHECK(make_in(make_literal("abcdef"), make_literal("ab"))->evaluateAsBoolean(context) == true);
    CHECK(make_in(make_literal("abcdef"), make_literal("b"))->evaluateAsBoolean(context) == true);
    CHECK(make_in(make_literal("abcdef"), make_literal("bc"))->evaluateAsBoolean(context) == true);
    CHECK(make_in(make_literal("abcdef"), make_literal("e"))->evaluateAsBoolean(context) == true);
    CHECK(make_in(make_literal("abcdef"), make_literal("ef"))->evaluateAsBoolean(context) == true);
    CHECK(make_in(make_literal("abcdef"), make_literal("ac"))->evaluateAsBoolean(context) == false);

    CHECK(make_in(make_literal("abcdef"), make_literal("ab"))->getExpressionName() == "in");
}

TEST_CASE("Substr test")
{
    CHECK(make_substr(make_literal("abcdef"), make_literal(0), make_literal(6))->evaluateAsText(context) == "abcdef");
    CHECK(make_substr(make_literal("abcdef"), make_literal(0), make_literal(5))->evaluateAsText(context) == "abcde");
    CHECK(make_substr(make_literal("abcdef"), make_literal(1), make_literal(6))->evaluateAsText(context) == "bcdef");
    CHECK(make_substr(make_literal("abcdef"), make_literal(0), make_literal(-1))->evaluateAsText(context) == "abcdef");
    CHECK(make_substr(make_literal("abcdef"), make_literal(-3), make_literal(-1))->evaluateAsText(context) == "ef");
    CHECK(make_substr(make_literal("abcdef"), make_literal(-2), make_literal(-1))->evaluateAsText(context) == "f");

    CHECK(make_substr(make_literal("abcdef"), make_literal(1), make_literal(2))->getExpressionName() == "substr");
}

TEST_CASE("Substrl test")
{
    CHECK(make_substrl(make_literal("abcdef"), make_literal(0), make_literal(6))->evaluateAsText(context) == "abcdef");
    CHECK(make_substrl(make_literal("abcdef"), make_literal(0), make_literal(5))->evaluateAsText(context) == "abcde");
    CHECK(make_substrl(make_literal("abcdef"), make_literal(1), make_literal(5))->evaluateAsText(context) == "bcdef");
    CHECK(make_substrl(make_literal("abcdef"), make_literal(5), make_literal(1))->evaluateAsText(context) == "f");
    CHECK(make_substrl(make_literal("abcdef"), make_literal(-2), make_literal(1))->evaluateAsText(context) == "f");
    CHECK(make_substrl(make_literal("abcdef"), make_literal(-3), make_literal(2))->evaluateAsText(context) == "ef");

    CHECK(make_substrl(make_literal("abcdef"), make_literal(1), make_literal(2))->getExpressionName() == "substrl");
}

TEST_CASE("Len test")
{
    CHECK(make_len(make_literal("abcdef"))->evaluateAsInteger(context) == 6);
    CHECK(make_len(make_literal("abcde"))->evaluateAsInteger(context) == 5);
    CHECK(make_len(make_literal(""))->evaluateAsInteger(context) == 0);

    CHECK(make_len(make_literal("abcdef"))->evaluateAsDecimal(context) == Approx(6).epsilon(EPSILON));
    CHECK(make_len(make_literal("abcde"))->evaluateAsDecimal(context) == Approx(5).epsilon(EPSILON));
    CHECK(make_len(make_literal(""))->evaluateAsDecimal(context) == Approx(0).epsilon(EPSILON));

    CHECK(make_len(make_literal("abcdef"))->getExpressionName() == "len");
}

TEST_CASE("Eq test")
{
    CHECK(make_eq(make_literal(true), make_literal(true))->evaluateAsBoolean(context) == true);
    CHECK(make_eq(make_literal(true), make_literal(false))->evaluateAsBoolean(context) == false);
    CHECK(make_eq(make_literal(1), make_literal(1))->evaluateAsBoolean(context) == true);
    CHECK(make_eq(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_eq(make_literal(1), make_literal(1))->evaluateAsBoolean(context) == true);
    CHECK(make_eq(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_eq(make_literal("abcdef"), make_literal("abcdef"))->evaluateAsBoolean(context) == true);
    CHECK(make_eq(make_literal("abcdef"), make_literal("abcd"))->evaluateAsBoolean(context) == false);

    CHECK(make_eq(make_literal(true), make_literal(true))->getExpressionName() == "eq");
    CHECK(make_eq(make_literal(1), make_literal(1))->getExpressionName() == "eq");
    CHECK(make_eq(make_literal(1.0), make_literal(1.0))->getExpressionName() == "eq");
    CHECK(make_eq(make_literal("abcdef"), make_literal("abcdef"))->getExpressionName() == "eq");
}

TEST_CASE("Neq test")
{
    CHECK(make_neq(make_literal(true), make_literal(true))->evaluateAsBoolean(context) == false);
    CHECK(make_neq(make_literal(true), make_literal(false))->evaluateAsBoolean(context) == true);
    CHECK(make_neq(make_literal(1), make_literal(1))->evaluateAsBoolean(context) == false);
    CHECK(make_neq(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_neq(make_literal(1), make_literal(1))->evaluateAsBoolean(context) == false);
    CHECK(make_neq(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_neq(make_literal("abcdef"), make_literal("abcdef"))->evaluateAsBoolean(context) == false);
    CHECK(make_neq(make_literal("abcdef"), make_literal("abcd"))->evaluateAsBoolean(context) == true);

    CHECK(make_neq(make_literal(true), make_literal(true))->getExpressionName() == "neq");
    CHECK(make_neq(make_literal(1), make_literal(1))->getExpressionName() == "neq");
    CHECK(make_neq(make_literal(1.0), make_literal(1.0))->getExpressionName() == "neq");
    CHECK(make_neq(make_literal("abcdef"), make_literal("abcdef"))->getExpressionName() == "neq");
}

TEST_CASE("Lt test")
{
    CHECK(make_lt(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_lt(make_literal(2), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_lt(make_literal(3), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_lt(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_lt(make_literal(2), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_lt(make_literal(3), make_literal(2))->evaluateAsBoolean(context) == false);

    CHECK(make_lt(make_literal(1), make_literal(1))->getExpressionName() == "lt");
    CHECK(make_lt(make_literal(1.0), make_literal(1.0))->getExpressionName() == "lt");
}

TEST_CASE("Lte test")
{
    CHECK(make_lte(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_lte(make_literal(2), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_lte(make_literal(3), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_lte(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_lte(make_literal(2), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_lte(make_literal(3), make_literal(2))->evaluateAsBoolean(context) == false);

    CHECK(make_lte(make_literal(1), make_literal(1))->getExpressionName() == "lte");
    CHECK(make_lte(make_literal(1.0), make_literal(1.0))->getExpressionName() == "lte");
}

TEST_CASE("Gt test")
{
    CHECK(make_gt(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_gt(make_literal(2), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_gt(make_literal(3), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_gt(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_gt(make_literal(2), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_gt(make_literal(3), make_literal(2))->evaluateAsBoolean(context) == true);

    CHECK(make_gt(make_literal(1), make_literal(1))->getExpressionName() == "gt");
    CHECK(make_gt(make_literal(1.0), make_literal(1.0))->getExpressionName() == "gt");
}

TEST_CASE("Gte test")
{
    CHECK(make_gte(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_gte(make_literal(2), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_gte(make_literal(3), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_gte(make_literal(1), make_literal(2))->evaluateAsBoolean(context) == false);
    CHECK(make_gte(make_literal(2), make_literal(2))->evaluateAsBoolean(context) == true);
    CHECK(make_gte(make_literal(3), make_literal(2))->evaluateAsBoolean(context) == true);

    CHECK(make_gte(make_literal(1), make_literal(1))->getExpressionName() == "gte");
    CHECK(make_gte(make_literal(1.0), make_literal(1.0))->getExpressionName() == "gte");
}

TEST_CASE("Min test")
{
    CHECK(make_min(make_literal(0), make_literal(1))->evaluateAsInteger(context) == 0);
    CHECK(make_min(make_literal(0), make_literal(-1))->evaluateAsInteger(context) == -1);
    CHECK(make_min(make_literal(0), make_literal(-1), make_literal(-5))->evaluateAsInteger(context) == -5);

    CHECK(make_min(make_literal(0), make_literal(1))->evaluateAsDecimal(context) == Approx(0).epsilon(EPSILON));
    CHECK(make_min(make_literal(0), make_literal(-1))->evaluateAsDecimal(context) == Approx(-1).epsilon(EPSILON));
    CHECK(make_min(make_literal(0), make_literal(-1), make_literal(-5))->evaluateAsDecimal(context) ==
          Approx(-5).epsilon(EPSILON));

    CHECK(make_min(make_literal(1), make_literal(2))->getExpressionName() == "min");
}

TEST_CASE("Max test")
{
    CHECK(make_max(make_literal(0), make_literal(1))->evaluateAsInteger(context) == 1);
    CHECK(make_max(make_literal(0), make_literal(-1))->evaluateAsInteger(context) == 0);
    CHECK(make_max(make_literal(0), make_literal(-1), make_literal(5))->evaluateAsInteger(context) == 5);

    CHECK(make_max(make_literal(0), make_literal(1))->evaluateAsDecimal(context) == Approx(1).epsilon(EPSILON));
    CHECK(make_max(make_literal(0), make_literal(-1))->evaluateAsDecimal(context) == Approx(0).epsilon(EPSILON));
    CHECK(make_max(make_literal(0), make_literal(-1), make_literal(5))->evaluateAsDecimal(context) ==
          Approx(5).epsilon(EPSILON));

    CHECK(make_max(make_literal(1), make_literal(2))->getExpressionName() == "max");
}

TEST_CASE("Var test")
{
    CHECK_THROWS_AS(make_var(make_literal("variable-boolean"))->evaluateAsBoolean(context), EvaluationException);
    CHECK_THROWS_AS(make_var(make_literal("variable-integer"))->evaluateAsInteger(context), EvaluationException);
    CHECK_THROWS_AS(make_var(make_literal("variable-decimal"))->evaluateAsDecimal(context), EvaluationException);
    CHECK_THROWS_AS(make_var(make_literal("variable-text"))->evaluateAsText(context), EvaluationException);

    context.setVariable("variable-boolean", true);
    context.setVariable("variable-integer", 1);
    context.setVariable("variable-decimal", 1.5);
    context.setVariable("variable-text", "abcdef");

    CHECK(make_var(make_literal("variable-boolean"))->evaluateAsBoolean(context) == true);
    CHECK(make_var(make_literal("variable-integer"))->evaluateAsInteger(context) == 1);
    CHECK(make_var(make_literal("variable-decimal"))->evaluateAsDecimal(context) == Approx(1.5).epsilon(EPSILON));
    CHECK(make_var(make_literal("variable-text"))->evaluateAsText(context) == "abcdef");

    context.setVariable("variable-boolean", false);
    context.setVariable("variable-integer", 2);
    context.setVariable("variable-decimal", 4.5);
    context.setVariable("variable-text", "abcdefg");

    CHECK(make_var(make_literal("variable-boolean"))->evaluateAsBoolean(context) == false);
    CHECK(make_var(make_literal("variable-integer"))->evaluateAsInteger(context) == 2);
    CHECK(make_var(make_literal("variable-decimal"))->evaluateAsDecimal(context) == Approx(4.5).epsilon(EPSILON));
    CHECK(make_var(make_literal("variable-text"))->evaluateAsText(context) == "abcdefg");

    CHECK(make_var(make_literal("variable"))->getExpressionName() == "var");
}

TEST_CASE("Cond test")
{
    CHECK(make_cond(make_literal(true), make_literal(true), make_literal(false))->evaluateAsBoolean(context) == true);
    CHECK(make_cond(make_literal(false), make_literal(true), make_literal(false))->evaluateAsBoolean(context) == false);

    CHECK(make_cond(make_literal(true), make_literal(1), make_literal(2))->evaluateAsInteger(context) == 1);
    CHECK(make_cond(make_literal(false), make_literal(1), make_literal(2))->evaluateAsInteger(context) == 2);

    CHECK(make_cond(make_literal(true), make_literal(1.5), make_literal(2.5))->evaluateAsDecimal(context) ==
          Approx(1.5).epsilon(EPSILON));
    CHECK(make_cond(make_literal(false), make_literal(1.5), make_literal(2.5))->evaluateAsDecimal(context) ==
          Approx(2.5).epsilon(EPSILON));

    CHECK(make_cond(make_literal(true), make_literal("a"), make_literal("b"))->evaluateAsText(context) == "a");
    CHECK(make_cond(make_literal(false), make_literal("a"), make_literal("b"))->evaluateAsText(context) == "b");

    CHECK(make_cond(make_literal(true), make_literal(true), make_literal(false))->getExpressionName() == "cond");
}

TEST_CASE("Concat test")
{
    CHECK(make_concat(make_literal("abc"), make_literal("def"))->evaluateAsText(context) == "abcdef");
    CHECK(make_concat(make_literal("abc"), make_literal(""))->evaluateAsText(context) == "abc");
    CHECK(make_concat(make_literal(""), make_literal("def"))->evaluateAsText(context) == "def");

    CHECK(make_concat(make_literal("abc"), make_literal("def"), make_literal("ghi"))->evaluateAsText(context) ==
          "abcdefghi");

    CHECK(make_concat(make_literal("abc"), make_literal("def"))->getExpressionName() == "concat");
}

TEST_CASE("Debug test")
{
    std::vector<std::string> debugExpressions;

    auto debugHandler = [&debugExpressions](std::string message) {
        debugExpressions.push_back(std::move(message));
    };

    eval::Context debugContext(debugHandler);

    CHECK(debugExpressions.size() == 0);

    CHECK(make_debug(make_literal(true), make_literal("boolean"))->evaluateAsBoolean(debugContext) == true);
    CHECK(debugExpressions.size() == 1);
    CHECK(debugExpressions[0] == "boolean : true");

    CHECK(make_debug(make_literal(12), make_literal("integer"))->evaluateAsInteger(debugContext) == 12);
    CHECK(debugExpressions.size() == 2);
    CHECK(debugExpressions[1] == "integer : 12");

    CHECK(make_debug(make_literal(15.0), make_literal("decimal"))->evaluateAsDecimal(debugContext) ==
          Approx(15.0).epsilon(EPSILON));
    CHECK(debugExpressions.size() == 3);
    CHECK(debugExpressions[2] == "decimal : 15.000000");

    CHECK(make_debug(make_literal("abcdef"), make_literal("text"))->evaluateAsText(debugContext) == "abcdef");
    CHECK(debugExpressions.size() == 4);
    CHECK(debugExpressions[3] == "text : abcdef");

    CHECK(make_debug(make_literal("abc"), make_literal("def"))->getExpressionName() == "debug");
}