#include <unordered_set>
#include "include/NeqExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"
#include "include/NotExpression.h"
#include "include/EqExpression.h"

namespace mythtitans::exprl::eval::impl {

    NeqExpression::NeqExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        auto eqExpression = make_eq(std::move(operandA), std::move(operandB));
        expression_ = make_not(std::move(eqExpression));
    }

    bool NeqExpression::evaluateAsBoolean(const Context& context) const {
        return expression_->evaluateAsBoolean(context);
    }

    std::string NeqExpression::getExpressionName() const {
        return mythtitans::exprl::globals::NEQ_EXPRESSION;
    }

    std::unordered_set<std::string> NeqExpression::getLiteralVariables() const {
        return util::getLiteralVariables(expression_);
    }
}
