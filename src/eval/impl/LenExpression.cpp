#include <unordered_set>
#include "include/LenExpression.h"

#include "../../Globals.h"
#include "../../util/include/ExpressionUtilities.h"

namespace mythtitans::exprl::eval::impl {

    LenExpression::LenExpression(std::shared_ptr<Expression> operand) : operand_(std::move(operand)) {
    }

    long LenExpression::evaluateAsInteger(const Context& context) const {
        return operand_->evaluateAsText(context).length();
    }

    double LenExpression::evaluateAsDecimal(const Context& context) const {
        return operand_->evaluateAsText(context).length();
    }

    std::string LenExpression::getExpressionName() const {
        return mythtitans::exprl::globals::LEN_EXPRESSION;
    }

    std::unordered_set<std::string> LenExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operand_);
    }
}