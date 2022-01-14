#include <unordered_set>
#include "include/GteExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"
#include "include/NotExpression.h"
#include "include/LtExpression.h"

namespace mythtitans::exprl::eval::impl {

    GteExpression::GteExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        auto ltExpression = make_lt(std::move(operandA), std::move(operandB));
        expression_ = make_not(std::move(ltExpression));
    }

    bool GteExpression::evaluateAsBoolean(const Context& context) const {
        return expression_->evaluateAsBoolean(context);
    }

    std::string GteExpression::getExpressionName() const {
        return mythtitans::exprl::globals::GTE_EXPRESSION;
    }

    std::unordered_set<std::string> GteExpression::getLiteralVariables() const {
        return util::getLiteralVariables(expression_);
    }
}
