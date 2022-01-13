#include "include/LteExpression.h"

#include "../../Globals.h"
#include "include/OrExpression.h"
#include "include/EqExpression.h"
#include "include/LtExpression.h"

namespace mythtitans::exprl::eval::impl {

    LteExpression::LteExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        auto eqExpression = make_eq(operandA, operandB);
        auto ltExpression = make_lt(std::move(operandA), std::move(operandB));
        auto params = std::vector<std::shared_ptr<Expression>>{std::move(eqExpression), std::move(ltExpression)};
        expression_ = std::make_unique<OrExpression>(std::move(params));
    }

    bool LteExpression::evaluateAsBoolean(const Context& context) const {
        return expression_->evaluateAsBoolean(context);
    }

    std::string LteExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::LTE_EXPRESSION;
    }
}
