#include "include/SubstrExpression.h"

#include <utility>
#include <cmath>

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    SubstrExpression::SubstrExpression(std::shared_ptr<Expression> operandStr,
                                       std::shared_ptr<Expression> operandBegin,
                                       std::shared_ptr<Expression> operandEnd)
            : operandStr_(std::move(operandStr)),
              operandBegin_(std::move(operandBegin)),
              operandEnd_(std::move(operandEnd)) {
    }

    std::string SubstrExpression::evaluateAsText(const Context& context) const {
        const auto str = operandStr_->evaluateAsText(context);
        auto begin = operandBegin_->evaluateAsInteger(context);
        auto end = operandEnd_->evaluateAsInteger(context);

        if (begin < 0) {
            begin = str.length() + begin + 1;
        }

        if (end < 0) {
            end = str.length() + end + 1;
        }

        begin = std::max(begin, 0L);
        end = std::max(std::min(end, static_cast<long>(str.length())), 0L);

        return str.substr(begin, end - begin);
    }

    std::string SubstrExpression::getExpressionName() const noexcept {
        return mythtitans::exprl::globals::SUBSTR_EXPRESSION;
    }
}
