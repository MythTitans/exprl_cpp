#include "include/InExpression.h"

#include "../../Globals.h"
#include "../../util/include/StringUtilities.h"

using namespace mythtitans::exprl::util;

namespace mythtitans::exprl::eval::impl {

    InExpression::InExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB)
            : operandA_(std::move(operandA)),
              operandB_(std::move(operandB)) {
    }

    bool InExpression::evaluateAsBoolean(const Context& context) const {
        const auto str = operandA_->evaluateAsText(context);
        const auto content = operandB_->evaluateAsText(context);
        return contains(str, content);
    }

    std::string InExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::IN_EXPRESSION;
    }
}
