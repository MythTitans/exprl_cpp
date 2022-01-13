#include "include/GtExpression.h"

#include "../../Globals.h"
#include "include/NotExpression.h"
#include "include/LteExpression.h"

namespace mythtitans::exprl::eval::impl {

    GtExpression::GtExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        auto lteExpression = make_lte(std::move(operandA), std::move(operandB));
        expression_ = make_not(std::move(lteExpression));
    }

    bool GtExpression::evaluateAsBoolean(const Context& context) const {
        return expression_->evaluateAsBoolean(context);
    }

    std::string GtExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::GT_EXPRESSION;
    }
}
