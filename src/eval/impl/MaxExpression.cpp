#include <unordered_set>
#include "include/MaxExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

namespace mythtitans::exprl::eval::impl {

    MaxExpression::MaxExpression(std::vector<std::shared_ptr<Expression>>&& operands)
            : operands_(std::move(operands)) {
    }

    long MaxExpression::evaluateAsInteger(const Context& context) const {
        if (operands_.size() == 2) {
            return std::max(operands_[0]->evaluateAsInteger(context), operands_[1]->evaluateAsInteger(context));
        }

        long max = operands_[0]->evaluateAsInteger(context);
        for (const auto& expression: operands_) {
            max = std::max(max, expression->evaluateAsInteger(context));
        }

        return max;
    }

    double MaxExpression::evaluateAsDecimal(const Context& context) const {
        if (operands_.size() == 2) {
            return std::max(operands_[0]->evaluateAsDecimal(context), operands_[1]->evaluateAsDecimal(context));
        }

        double max = operands_[0]->evaluateAsDecimal(context);
        for (const auto& expression: operands_) {
            max = std::max(max, expression->evaluateAsDecimal(context));
        }

        return max;
    }

    std::string MaxExpression::getExpressionName() const {
        return mythtitans::exprl::globals::MAX_EXPRESSION;
    }

    std::unordered_set<std::string> MaxExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operands_);
    }
}
