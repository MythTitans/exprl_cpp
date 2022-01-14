#include <unordered_set>
#include "include/DivExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

namespace mythtitans::exprl::eval::impl {

    DivExpression::DivExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB)
            : operandA_(std::move(operandA)),
              operandB_(std::move(operandB)) {
    }

    long DivExpression::evaluateAsInteger(const Context& context) const {
        return operandA_->evaluateAsInteger(context) / operandB_->evaluateAsInteger(context);
    }

    double DivExpression::evaluateAsDecimal(const Context& context) const {
        return operandA_->evaluateAsDecimal(context) / operandB_->evaluateAsDecimal(context);
    }

    std::string DivExpression::getExpressionName() const {
        return mythtitans::exprl::globals::DIV_EXPRESSION;
    }

    std::unordered_set<std::string> DivExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operandA_, operandB_);
    }
}
