#include "include/MinExpression.h"

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    MinExpression::MinExpression(std::vector<std::shared_ptr<Expression>>&& operands) : operands_(std::move(operands)) {
    }

    long MinExpression::evaluateAsInteger(const Context& context) const {
        if (operands_.size() == 2) {
            return std::min(operands_[0]->evaluateAsInteger(context), operands_[1]->evaluateAsInteger(context));
        }

        long min = operands_[0]->evaluateAsInteger(context);
        for (const auto& expression: operands_) {
            min = std::min(min, expression->evaluateAsInteger(context));
        }

        return min;
    }

    double MinExpression::evaluateAsDecimal(const Context& context) const {
        if (operands_.size() == 2) {
            return std::min(operands_[0]->evaluateAsDecimal(context), operands_[1]->evaluateAsDecimal(context));
        }

        double min = operands_[0]->evaluateAsDecimal(context);
        for (const auto& expression: operands_) {
            min = std::min(min, expression->evaluateAsDecimal(context));
        }

        return min;
    }

    std::string MinExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::MIN_EXPRESSION;
    }
}
