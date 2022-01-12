#ifndef EXPRL_CPP_MAXEXPRESSION_H
#define EXPRL_CPP_MAXEXPRESSION_H

#include <vector>
#include <memory>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class MaxExpression : public Expression {

    public:
        explicit MaxExpression(std::vector<std::shared_ptr<Expression>>&& operands);

        [[nodiscard]] long evaluateAsInteger(const Context& context) const override;

        [[nodiscard]] double evaluateAsDecimal(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        std::vector<std::shared_ptr<Expression>> operands_;
    };

    template<class ... ExpressionType>
    inline auto make_max(std::shared_ptr<Expression> operandA,
                         std::shared_ptr<Expression> operandB,
                         std::shared_ptr<ExpressionType> ... operands) {
        return std::make_shared<MaxExpression>(std::vector<std::shared_ptr<Expression>>(
                {std::move(operandA), std::move(operandB), std::move(operands)...}));
    }

}

#endif //EXPRL_CPP_MAXEXPRESSION_H
