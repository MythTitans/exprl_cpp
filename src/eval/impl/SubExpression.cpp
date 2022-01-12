#include "include/SubExpression.h"

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    SubExpression::SubExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB)
            : operandA_(std::move(operandA)),
              operandB_(std::move(operandB)) {
    }

    long SubExpression::evaluateAsInteger(const Context& context) const {
        return operandA_->evaluateAsInteger(context) - operandB_->evaluateAsInteger(context);
    }

    double SubExpression::evaluateAsDecimal(const Context& context) const {
        return operandA_->evaluateAsDecimal(context) - operandB_->evaluateAsDecimal(context);
    }

    std::string SubExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::SUB_EXPRESSION;
    }
}
