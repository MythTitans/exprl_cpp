#ifndef EXPRL_CPP_SUBSTRLEXPRESSION_H
#define EXPRL_CPP_SUBSTRLEXPRESSION_H

#include <memory>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class SubstrlExpression : public Expression {

    public:
        SubstrlExpression(std::shared_ptr<Expression> operandStr,
                          std::shared_ptr<Expression> operandBegin,
                          std::shared_ptr<Expression> operandLength);

        [[nodiscard]] std::string evaluateAsText(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        std::shared_ptr<Expression> operandStr_;
        std::shared_ptr<Expression> operandBegin_;
        std::shared_ptr<Expression> operandLength_;
    };

    inline auto make_substrl(std::shared_ptr<Expression> operandStr,
                             std::shared_ptr<Expression> operandBegin,
                             std::shared_ptr<Expression> operandLength) {
        return std::make_shared<SubstrlExpression>(
                std::move(operandStr),
                std::move(operandBegin),
                std::move(operandLength)
        );
    }

}

#endif //EXPRL_CPP_SUBSTRLEXPRESSION_H
