#include <unordered_set>
#include "include/AndExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

namespace mythtitans::exprl::eval::impl {

    AndExpression::AndExpression(std::vector<std::shared_ptr<Expression>>&& operands)
            : operands_(std::move(operands)) {
    }

    bool AndExpression::evaluateAsBoolean(const Context& context) const {
        if (operands_.size() == 2) {
            return operands_[0]->evaluateAsBoolean(context) && operands_[1]->evaluateAsBoolean(context);
        }

        for (const auto& expression: operands_) {
            if (!expression->evaluateAsBoolean(context)) {
                return false;
            }
        }

        return true;
    }

    std::string AndExpression::getExpressionName() const {
        return mythtitans::exprl::globals::AND_EXPRESSION;
    }

    std::unordered_set<std::string> AndExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operands_);
    }
}
