#include "include/MulExpression.h"

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    MulExpression::MulExpression(std::vector<std::shared_ptr<Expression>>&& operands)
            : operands_(std::move(operands)) {
    }

    long MulExpression::evaluateAsInteger(const Context& context) const {
        if (operands_.size() == 2) {
            return operands_[0]->evaluateAsInteger(context) * operands_[1]->evaluateAsInteger(context);
        }

        long product = 1;
        for (const auto& expression: operands_) {
            product *= expression->evaluateAsInteger(context);
        }

        return product;
    }

    double MulExpression::evaluateAsDecimal(const Context& context) const {
        if (operands_.size() == 2) {
            return operands_[0]->evaluateAsDecimal(context) * operands_[1]->evaluateAsDecimal(context);
        }

        double product = 1;
        for (const auto& expression: operands_) {
            product *= expression->evaluateAsDecimal(context);
        }

        return product;
    }

    std::string MulExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::MUL_EXPRESSION;
    }
}
