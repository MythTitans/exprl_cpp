#ifndef EXPRL_CPP_ANDEXPRESSION_H
#define EXPRL_CPP_ANDEXPRESSION_H

#include <vector>
#include <memory>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class AndExpression : public Expression {

    public:
        explicit AndExpression(std::vector<std::shared_ptr<Expression>>&& operands);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        std::vector<std::shared_ptr<Expression>> operands_;
    };

    template<class ... ExpressionType>
    inline auto make_and(std::shared_ptr<Expression> operandA,
                         std::shared_ptr<Expression> operandB,
                         std::shared_ptr<ExpressionType> ... operands) {
        return std::make_shared<AndExpression>(std::vector<std::shared_ptr<Expression>>(
                {std::move(operandA), std::move(operandB), std::move(operands)...}));
    }

}

#endif //EXPRL_CPP_ANDEXPRESSION_H
