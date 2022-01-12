#include "include/NotExpression.h"

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    NotExpression::NotExpression(std::shared_ptr<Expression> operand) : operand_(std::move(operand)) {
    }

    bool NotExpression::evaluateAsBoolean(const Context& context) const {
        return !operand_->evaluateAsBoolean(context);
    }

    std::string NotExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::NOT_EXPRESSION;
    }
}