#include "include/ConcatExpression.h"

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    ConcatExpression::ConcatExpression(std::vector<std::shared_ptr<Expression>>&& operands)
            : operands_(std::move(operands)) {
    }

    std::string ConcatExpression::evaluateAsText(const Context& context) const {
        if (operands_.size() == 2) {
            return operands_[0]->evaluateAsText(context) + operands_[1]->evaluateAsText(context);
        }

        std::string result;
        for (const auto& expression: operands_) {
            result += expression->evaluateAsText(context);
        }

        return result;
    }

    std::string ConcatExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::CONCAT_EXPRESSION;
    }
}
