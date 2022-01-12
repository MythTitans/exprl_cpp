#include "include/GteExpression.h"

#include "../../Globals.h"
#include "include/NotExpression.h"
#include "include/LtExpression.h"

namespace mythtitans::exprl::eval::impl {

    GteExpression::GteExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        auto ltExpression = std::make_unique<LtExpression>(std::move(operandA), std::move(operandB));
        expression_ = std::make_unique<NotExpression>(std::move(ltExpression));
    }

    bool GteExpression::evaluateAsBoolean(const Context& context) const {
        return expression_->evaluateAsBoolean(context);
    }

    std::string GteExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::GTE_EXPRESSION;
    }
}
