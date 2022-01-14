#include <unordered_set>
#include "include/EqExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

namespace mythtitans::exprl::eval::impl {

    static constexpr double EPSILON = 0.000001;

    EqExpression::EqExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB)
            : operandA_(std::move(operandA)),
              operandB_(std::move(operandB)) {
    }

    bool EqExpression::evaluateAsBoolean(const Context& context) const {
        try {
            return operandA_->evaluateAsBoolean(context) == operandB_->evaluateAsBoolean(context);
        } catch (const EvaluationException& e) {
            // Ignored
        }

        try {
            return operandA_->evaluateAsInteger(context) == operandB_->evaluateAsInteger(context);
        } catch (const EvaluationException& e) {
            // Ignored
        }

        try {
            return std::abs(operandA_->evaluateAsDecimal(context) - operandB_->evaluateAsDecimal(context)) < EPSILON;
        } catch (const EvaluationException& e) {
            // Ignored
        }

        try {
            return operandA_->evaluateAsText(context) == operandB_->evaluateAsText(context);
        } catch (const EvaluationException& e) {
            // Ignored
        }

        throw EvaluationException(
                "Expression [" + getExpressionName() + "] failed with all combination of known types.");
    }

    std::string EqExpression::getExpressionName() const {
        return mythtitans::exprl::globals::EQ_EXPRESSION;
    }

    std::unordered_set<std::string> EqExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operandA_, operandB_);
    }
}
