#include <unordered_set>
#include "include/ConcatExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

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

    std::string ConcatExpression::getExpressionName() const {
        return mythtitans::exprl::globals::CONCAT_EXPRESSION;
    }

    std::unordered_set<std::string> ConcatExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operands_);
    }
}
