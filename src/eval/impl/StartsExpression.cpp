#include <unordered_set>
#include "include/StartsExpression.h"

#include "../../Globals.h"
#include "../../util/include/StringUtilities.h"
#include "../../util/include/ExpressionUtilities.h"

using namespace mythtitans::exprl::util;

namespace mythtitans::exprl::eval::impl {

    StartsExpression::StartsExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB)
            : operandA_(std::move(operandA)),
              operandB_(std::move(operandB)) {
    }

    bool StartsExpression::evaluateAsBoolean(const Context& context) const {
        const auto str = operandA_->evaluateAsText(context);
        const auto prefix = operandB_->evaluateAsText(context);
        return starts_with(str, prefix);
    }

    std::string StartsExpression::getExpressionName() const {
        return mythtitans::exprl::globals::STARTS_EXPRESSION;
    }

    std::unordered_set<std::string> StartsExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operandA_, operandB_);
    }
}
