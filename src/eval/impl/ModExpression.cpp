#include "include/ModExpression.h"

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    ModExpression::ModExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB)
            : operandA_(std::move(operandA)),
              operandB_(std::move(operandB)) {
    }

    long ModExpression::evaluateAsInteger(const Context& context) const {
        return operandA_->evaluateAsInteger(context) % operandB_->evaluateAsInteger(context);
    }

    double ModExpression::evaluateAsDecimal(const Context& context) const {
        return static_cast<long>(evaluateAsInteger(context));
    }

    std::string ModExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::MOD_EXPRESSION;
    }
}
