#include <unordered_set>
#include "include/SubExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

namespace mythtitans::exprl::eval::impl {

    SubExpression::SubExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB)
            : operandA_(std::move(operandA)),
              operandB_(std::move(operandB)) {
    }

    long SubExpression::evaluateAsInteger(const Context& context) const {
        return operandA_->evaluateAsInteger(context) - operandB_->evaluateAsInteger(context);
    }

    double SubExpression::evaluateAsDecimal(const Context& context) const {
        return operandA_->evaluateAsDecimal(context) - operandB_->evaluateAsDecimal(context);
    }

    std::string SubExpression::getExpressionName() const {
        return mythtitans::exprl::globals::SUB_EXPRESSION;
    }

    std::unordered_set<std::string> SubExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operandA_, operandB_);
    }
}
