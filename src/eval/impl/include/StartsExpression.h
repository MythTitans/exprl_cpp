#ifndef EXPRL_CPP_STARTSEXPRESSION_H
#define EXPRL_CPP_STARTSEXPRESSION_H

#include <memory>
#include <unordered_set>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class StartsExpression : public Expression {

    public:
        StartsExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const override;

        [[nodiscard]] std::unordered_set<std::string> getLiteralVariables() const override;

    private:
        std::shared_ptr<Expression> operandA_;
        std::shared_ptr<Expression> operandB_;
    };

    inline auto make_starts(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        return std::make_shared<StartsExpression>(std::move(operandA), std::move(operandB));
    }

}

#endif //EXPRL_CPP_STARTSEXPRESSION_H
