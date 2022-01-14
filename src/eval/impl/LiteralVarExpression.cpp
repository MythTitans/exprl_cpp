#include <unordered_set>
#include "include/LiteralVarExpression.h"

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    LiteralVarExpression::LiteralVarExpression(std::string operand) : operand_(std::move(operand)) {
    }

    bool LiteralVarExpression::evaluateAsBoolean(const Context& context) const {
        return accessVariable(context).asBoolean();
    }

    long LiteralVarExpression::evaluateAsInteger(const Context& context) const {
        return accessVariable(context).asInteger();
    }

    double LiteralVarExpression::evaluateAsDecimal(const Context& context) const {
        return accessVariable(context).asDecimal();
    }

    std::string LiteralVarExpression::evaluateAsText(const Context& context) const {
        return accessVariable(context).asText();
    }

    std::string LiteralVarExpression::getExpressionName() const {
        return mythtitans::exprl::globals::VAR_EXPRESSION;
    }

    Variable LiteralVarExpression::accessVariable(const Context& context) const {
        const auto variableName = operand_;
        const auto variable = context.getVariable(variableName);
        if (variable.has_value()) {
            return variable.value();
        }

        throw EvaluationException("Cannot find variable [" + variableName + "].");
    }

    std::unordered_set<std::string> LiteralVarExpression::getLiteralVariables() const {
        return {operand_};
    }
}