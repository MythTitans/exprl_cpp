#include "include/VarExpression.h"

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    VarExpression::VarExpression(std::shared_ptr<Expression> operand) : operand_(std::move(operand)) {
    }

    bool VarExpression::evaluateAsBoolean(const Context& context) const {
        return accessVariable(context).asBoolean();
    }

    long VarExpression::evaluateAsInteger(const Context& context) const {
        return accessVariable(context).asInteger();
    }

    double VarExpression::evaluateAsDecimal(const Context& context) const {
        return accessVariable(context).asDecimal();
    }

    std::string VarExpression::evaluateAsText(const Context& context) const {
        return accessVariable(context).asText();
    }

    std::string VarExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::VAR_EXPRESSION;
    }

    Variable VarExpression::accessVariable(const Context& context) const {
        const auto variableName = operand_->evaluateAsText(context);
        const auto variable = context.getVariable(variableName);
        if (variable.has_value()) {
            return variable.value();
        }

        throw EvaluationException("Cannot find variable [" + variableName + "].");
    }
}