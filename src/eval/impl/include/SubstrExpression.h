#ifndef EXPRL_CPP_SUBSTREXPRESSION_H
#define EXPRL_CPP_SUBSTREXPRESSION_H

#include <memory>
#include <unordered_set>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class SubstrExpression : public Expression {

    public:
        SubstrExpression(std::shared_ptr<Expression> operandStr,
                         std::shared_ptr<Expression> operandBegin,
                         std::shared_ptr<Expression> operandEnd);

        [[nodiscard]] std::string evaluateAsText(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const override;

        [[nodiscard]] std::unordered_set<std::string> getLiteralVariables() const override;

    private:
        std::shared_ptr<Expression> operandStr_;
        std::shared_ptr<Expression> operandBegin_;
        std::shared_ptr<Expression> operandEnd_;
    };

    inline auto make_substr(std::shared_ptr<Expression> operandStr,
                            std::shared_ptr<Expression> operandBegin,
                            std::shared_ptr<Expression> operandEnd) {
        return std::make_shared<SubstrExpression>(
                std::move(operandStr),
                std::move(operandBegin),
                std::move(operandEnd)
        );
    }

}

#endif //EXPRL_CPP_SUBSTREXPRESSION_H
