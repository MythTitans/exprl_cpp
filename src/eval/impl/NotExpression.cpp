#include <unordered_set>
#include "include/NotExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

namespace mythtitans::exprl::eval::impl {

    NotExpression::NotExpression(std::shared_ptr<Expression> operand) : operand_(std::move(operand)) {
    }

    bool NotExpression::evaluateAsBoolean(const Context& context) const {
        return !operand_->evaluateAsBoolean(context);
    }

    std::string NotExpression::getExpressionName() const {
        return mythtitans::exprl::globals::NOT_EXPRESSION;
    }

    std::unordered_set<std::string> NotExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operand_);
    }
}