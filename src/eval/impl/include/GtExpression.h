#ifndef EXPRL_CPP_GTEXPRESSION_H
#define EXPRL_CPP_GTEXPRESSION_H

#include <memory>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class GtExpression : public Expression {

    public:
        GtExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        std::shared_ptr<Expression> expression_;
    };

    inline auto make_gt(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        return std::make_shared<GtExpression>(std::move(operandA), std::move(operandB));
    }

}

#endif //EXPRL_CPP_GTEXPRESSION_H
