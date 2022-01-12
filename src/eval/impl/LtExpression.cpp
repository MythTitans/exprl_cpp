#include "include/LtExpression.h"

#include <cmath>

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    LtExpression::LtExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB)
            : operandA_(std::move(operandA)),
              operandB_(std::move(operandB)) {
    }

    bool LtExpression::evaluateAsBoolean(const Context& context) const {
        try {
            return operandA_->evaluateAsInteger(context) < operandB_->evaluateAsInteger(context);
        } catch (const EvaluationException& e) {
            // Ignored
        }

        try {
            return operandA_->evaluateAsDecimal(context) < operandB_->evaluateAsDecimal(context);
        } catch (const EvaluationException& e) {
            // Ignored
        }

        throw EvaluationException(
                "Expression [" + getExpressionName() + "] failed with all combination of known types.");
    }

    std::string LtExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::LT_EXPRESSION;
    }
}
