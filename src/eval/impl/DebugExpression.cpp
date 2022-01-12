#include "include/DebugExpression.h"

#include "../../Globals.h"

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

    std::string DebugExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::DEBUG_EXPRESSION;
    }
}
