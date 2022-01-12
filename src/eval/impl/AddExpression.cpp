#include "include/AddExpression.h"

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    AddExpression::AddExpression(std::vector<std::shared_ptr<Expression>>&& operands)
            : operands_(std::move(operands)) {
    }

    long AddExpression::evaluateAsInteger(const Context& context) const {
        if (operands_.size() == 2) {
            return operands_[0]->evaluateAsInteger(context) + operands_[1]->evaluateAsInteger(context);
        }

        long sum = 0;
        for (const auto& expression: operands_) {
            sum += expression->evaluateAsInteger(context);
        }

        return sum;
    }

    double AddExpression::evaluateAsDecimal(const Context& context) const {
        if (operands_.size() == 2) {
            return operands_[0]->evaluateAsDecimal(context) + operands_[1]->evaluateAsDecimal(context);
        }

        double sum = 0;
        for (const auto& expression: operands_) {
            sum += expression->evaluateAsDecimal(context);
        }

        return sum;
    }

    std::string AddExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::ADD_EXPRESSION;
    }
}
