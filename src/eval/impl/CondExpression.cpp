#include "include/CondExpression.h"

#include <utility>
#include <unordered_set>

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

namespace mythtitans::exprl::eval::impl {

    CondExpression::CondExpression(std::shared_ptr<Expression> operandCond,
                                   std::shared_ptr<Expression> operandThen,
                                   std::shared_ptr<Expression> operandElse)
            : operandCond_(std::move(operandCond)),
              operandThen_(std::move(operandThen)),
              operandElse_(std::move(operandElse)) {
    }

    bool CondExpression::evaluateAsBoolean(const Context& context) const {
        return evaluateCondition(context)->evaluateAsBoolean(context);
    }

    long CondExpression::evaluateAsInteger(const Context& context) const {
        return evaluateCondition(context)->evaluateAsInteger(context);
    }

    double CondExpression::evaluateAsDecimal(const Context& context) const {
        return evaluateCondition(context)->evaluateAsDecimal(context);
    }

    std::string CondExpression::evaluateAsText(const Context& context) const {
        return evaluateCondition(context)->evaluateAsText(context);
    }

    std::string CondExpression::getExpressionName() const {
        return mythtitans::exprl::globals::COND_EXPRESSION;
    }

    const std::shared_ptr<Expression>& CondExpression::evaluateCondition(const Context& context) const {
        if (operandCond_->evaluateAsBoolean(context)) {
            return operandThen_;
        } else {
            return operandElse_;
        }
    }

    std::unordered_set<std::string> CondExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operandCond_, operandThen_, operandElse_);
    }
}
