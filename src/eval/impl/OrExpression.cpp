#include "include/OrExpression.h"

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    OrExpression::OrExpression(std::vector<std::shared_ptr<Expression>>&& operands) : operands_(std::move(operands)) {
    }

    bool OrExpression::evaluateAsBoolean(const Context& context) const {
        if (operands_.size() == 2) {
            return operands_[0]->evaluateAsBoolean(context) || operands_[1]->evaluateAsBoolean(context);
        }

        for (const auto& expression: operands_) {
            if (expression->evaluateAsBoolean(context)) {
                return true;
            }
        }

        return false;
    }

    std::string OrExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::OR_EXPRESSION;
    }
}
