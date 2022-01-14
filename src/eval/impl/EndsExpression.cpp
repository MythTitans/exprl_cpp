#include <unordered_set>
#include "include/EndsExpression.h"

#include "../../Globals.h"
#include "../../util/include/StringUtilities.h"
#include "../../util/include/ExpressionUtilities.h"

using namespace mythtitans::exprl::util;

namespace mythtitans::exprl::eval::impl {

    EndsExpression::EndsExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB)
            : operandA_(std::move(operandA)),
              operandB_(std::move(operandB)) {
    }

    bool EndsExpression::evaluateAsBoolean(const Context& context) const {
        const auto str = operandA_->evaluateAsText(context);
        const auto suffix = operandB_->evaluateAsText(context);
        return ends_with(str, suffix);
    }

    std::string EndsExpression::getExpressionName() const {
        return mythtitans::exprl::globals::ENDS_EXPRESSION;
    }

    std::unordered_set<std::string> EndsExpression::getLiteralVariables() const {
        return util::getLiteralVariables(operandA_, operandB_);
    }
}
