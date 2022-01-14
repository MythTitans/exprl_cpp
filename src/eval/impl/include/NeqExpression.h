#ifndef EXPRL_CPP_NEQEXPRESSION_H
#define EXPRL_CPP_NEQEXPRESSION_H

#include <memory>
#include <unordered_set>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class NeqExpression : public Expression {

    public:
        NeqExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const override;

        [[nodiscard]] std::unordered_set<std::string> getLiteralVariables() const override;

    private:
        std::shared_ptr<Expression> expression_;
    };

    inline auto make_neq(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        return std::make_shared<NeqExpression>(std::move(operandA), std::move(operandB));
    }

}

#endif //EXPRL_CPP_NEQEXPRESSION_H
