#include "include/NeqExpression.h"

#include "../../Globals.h"
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

    std::string NeqExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::NEQ_EXPRESSION;
    }
}
