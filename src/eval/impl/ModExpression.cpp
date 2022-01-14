#include <unordered_set>
#include "include/ModExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

namespace mythtitans::exprl::eval::impl {

    ModExpression::ModExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB)
            : operandA_(std::move(operandA)),
              operandB_(std::move(operandB)) {
    }

    long ModExpression::evaluateAsInteger(const Context& context) const {
        return operandA_->evaluateAsInteger(context) % operandB_->evaluateAsInteger(context);
    }

    double ModExpression::evaluateAsDecimal(const Context& context) const {
        return static_cast<double>(evaluateAsInteger(context));
    }

    std::string ModExpression::getExpressionName() const {
        return mythtitans::exprl::globals::MOD_EXPRESSION;
    }

    std::unordered_set<std::string> ModExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operandA_, operandB_);
    }
}
