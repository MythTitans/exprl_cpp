#ifndef EXPRL_CPP_SUBEXPRESSION_H
#define EXPRL_CPP_SUBEXPRESSION_H

#include <memory>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class SubExpression : public Expression {

    public:
        SubExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB);

        [[nodiscard]] long evaluateAsInteger(const Context& context) const override;

        [[nodiscard]] double evaluateAsDecimal(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        std::shared_ptr<Expression> operandA_;
        std::shared_ptr<Expression> operandB_;
    };

    inline auto make_sub(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        return std::make_shared<SubExpression>(std::move(operandA), std::move(operandB));
    }

}

#endif //EXPRL_CPP_SUBEXPRESSION_H
