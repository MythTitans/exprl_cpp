#include "include/SubstrlExpression.h"

#include <utility>
#include <cmath>

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    SubstrlExpression::SubstrlExpression(std::shared_ptr<Expression> operandStr,
                                         std::shared_ptr<Expression> operandBegin,
                                         std::shared_ptr<Expression> operandLength)
            : operandStr_(std::move(operandStr)),
              operandBegin_(std::move(operandBegin)),
              operandLength_(std::move(operandLength)) {
    }

    std::string SubstrlExpression::evaluateAsText(const Context& context) const {
        const auto str = operandStr_->evaluateAsText(context);
        auto begin = operandBegin_->evaluateAsInteger(context);
        auto length = operandLength_->evaluateAsInteger(context);

        if (begin < 0) {
            begin = str.length() + begin + 1;
        }

        return str.substr(begin, length);
    }

    std::string SubstrlExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::SUBSTRL_EXPRESSION;
    }
}
