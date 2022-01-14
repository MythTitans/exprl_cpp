#ifndef EXPRL_CPP_CONCATEXPRESSION_H
#define EXPRL_CPP_CONCATEXPRESSION_H

#include <vector>
#include <memory>
#include <unordered_set>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class ConcatExpression : public Expression {

    public:
        explicit ConcatExpression(std::vector<std::shared_ptr<Expression>>&& operands);

        [[nodiscard]] std::string evaluateAsText(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const override;

        [[nodiscard]] std::unordered_set<std::string> getLiteralVariables() const override;

    private:
        std::vector<std::shared_ptr<Expression>> operands_;
    };

    template<class ... ExpressionType>
    inline auto make_concat(std::shared_ptr<Expression> operandA,
                            std::shared_ptr<Expression> operandB,
                            std::shared_ptr<ExpressionType> ... operands) {
        return std::make_shared<ConcatExpression>(
                std::vector{std::move(operandA), std::move(operandB), std::move(operands)...});
    }

}

#endif //EXPRL_CPP_CONCATEXPRESSION_H
