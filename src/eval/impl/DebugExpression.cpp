#include <unordered_set>
#include "include/DebugExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

namespace mythtitans::exprl::eval::impl {

    DebugExpression::DebugExpression(std::shared_ptr<Expression> operandDebugged,
                                     std::shared_ptr<Expression> operandDebugLabel)
            : operandDebugged_(std::move(operandDebugged)),
              operandDebugLabel_(std::move(operandDebugLabel)) {
    }

    bool DebugExpression::evaluateAsBoolean(const Context& context) const {
        auto result = operandDebugged_->evaluateAsBoolean(context);
        produceDebugMessage(result, context);
        return result;
    }

    long DebugExpression::evaluateAsInteger(const Context& context) const {
        auto result = operandDebugged_->evaluateAsInteger(context);
        produceDebugMessage(result, context);
        return result;
    }

    double DebugExpression::evaluateAsDecimal(const Context& context) const {
        auto result = operandDebugged_->evaluateAsDecimal(context);
        produceDebugMessage(result, context);
        return result;
    }

    std::string DebugExpression::evaluateAsText(const Context& context) const {
        auto result = operandDebugged_->evaluateAsText(context);
        produceDebugMessage(result, context);
        return result;
    }

    std::string DebugExpression::getExpressionName() const {
        return mythtitans::exprl::globals::DEBUG_EXPRESSION;
    }

    std::unordered_set<std::string> DebugExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operandDebugged_, operandDebugLabel_);
    }
}
