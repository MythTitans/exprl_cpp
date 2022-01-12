#ifndef EXPRL_CPP_INEXPRESSION_H
#define EXPRL_CPP_INEXPRESSION_H

#include <memory>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class InExpression : public Expression {

    public:
        InExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        std::shared_ptr<Expression> operandA_;
        std::shared_ptr<Expression> operandB_;
    };

    inline auto make_in(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        return std::make_shared<InExpression>(std::move(operandA), std::move(operandB));
    }

}

#endif //EXPRL_CPP_INEXPRESSION_H
