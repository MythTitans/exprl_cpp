#include "doctest/doctest.h"

#include <chrono>
#include <thread>
#include <atomic>

#include "../src/eval/include/Context.h"
#include "../src/parser/include/Parser.h"
#include "../src/ExpressionEvaluator.h"
#include "../src/eval/impl/include/VarExpression.h"
#include "../src/eval/impl/include/LiteralExpression.h"
#include "../src/eval/impl/include/AndExpression.h"

using namespace std;
using namespace mythtitans::exprl;
using namespace mythtitans::exprl::parser;
using namespace mythtitans::exprl::eval::impl;
using namespace doctest;

using Duration = std::chrono::duration<long, std::milli>;

class Latch {
public:
    explicit Latch(int count) : count_(count) {
    }

    void await() const {
        while (count_.load() > 0) {
            std::this_thread::yield();
        }
    }

    void countDown() {
        count_.fetch_sub(1);
    }

private:
    std::atomic<int> count_;
};

class ControlledVarExpression : public eval::impl::VarExpression {

public:
    ControlledVarExpression(std::shared_ptr<Expression> operand, Duration evaluationDelay, Latch* afterEvaluationLatch)
            : VarExpression(std::move(operand)),
              evaluationDelay_(evaluationDelay),
              afterEvaluationLatch_(afterEvaluationLatch) {
    }

    [[nodiscard]] bool evaluateAsBoolean(const eval::Context& context) const override {
        std::this_thread::sleep_for(evaluationDelay_);

        auto result = VarExpression::evaluateAsBoolean(context);

        if (afterEvaluationLatch_) {
            afterEvaluationLatch_->countDown();
        }

        return result;
    }

private:
    Duration evaluationDelay_;
    Latch* afterEvaluationLatch_;
};

class ControlledParser {

public:
    ControlledParser(std::shared_ptr<eval::Expression> operandA, std::shared_ptr<eval::Expression> operandB)
            : operandA_(std::move(operandA)), operandB_(std::move(operandB)) {
    }

    std::shared_ptr<eval::Expression> parse(const std::string& expression) {
        return make_and(operandA_, operandB_);
    }

private:
    std::shared_ptr<eval::Expression> operandA_;
    std::shared_ptr<eval::Expression> operandB_;
};

static constexpr double EPSILON = 0.000001;

static ExpressionEvaluator evaluator;

TEST_CASE("Evaluate raw expression")
{
    CHECK(evaluator.evaluateAsBoolean("true") == true);
    CHECK(evaluator.evaluateAsInteger("42") == 42);
    CHECK(evaluator.evaluateAsDecimal("42.5") == Approx(42.5).epsilon(EPSILON));
    CHECK(evaluator.evaluateAsText("'abcdef'") == "abcdef");
    CHECK(evaluator.evaluateAsBoolean("and(true, true)") == true);
}

TEST_CASE("Evaluate already parsed expression")
{
    auto expr1 = Parser::parse("true");
    auto expr2 = Parser::parse("42");
    auto expr3 = Parser::parse("42.5");
    auto expr4 = Parser::parse("'abcdef'");
    auto expr5 = Parser::parse("and(true, true)");

    CHECK(evaluator.evaluateAsBoolean(expr1) == true);
    CHECK(evaluator.evaluateAsInteger(expr2) == 42);
    CHECK(evaluator.evaluateAsDecimal(expr3) == Approx(42.5).epsilon(EPSILON));
    CHECK(evaluator.evaluateAsText(expr4) == "abcdef");
    CHECK(evaluator.evaluateAsBoolean(expr5) == true);
}

TEST_CASE("Updating variable is thread safe for evaluation")
{
    Latch afterOperandALatch(1);

    auto operandA = std::make_shared<ControlledVarExpression>(make_literal("var1"), Duration::zero(),
                                                              &afterOperandALatch);
    // A delay of 1 second should be enough to check that var2 was not updated during the evaluation process
    auto operandB = std::make_shared<ControlledVarExpression>(make_literal("var2"), std::chrono::seconds(1), nullptr);

    ControlledParser controlledParser(operandA, operandB);
    ExpressionEvaluator<ControlledParser> controlledEvaluator(std::move(controlledParser));

    // Change var2 to false right after var('var1') is evaluated
    std::thread variableChanger([&]() {
        afterOperandALatch.await();
        controlledEvaluator.setVariable("var2", false);
    });

    controlledEvaluator.setVariable("var1", true);
    controlledEvaluator.setVariable("var2", true);

    CHECK(controlledEvaluator.evaluateAsBoolean("and(var('var1'), var('var2'))") == true);

    variableChanger.join();
}