#ifndef EXPRL_CPP_MODEXPRESSION_H
#define EXPRL_CPP_MODEXPRESSION_H

#include <memory>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class ModExpression : public Expression {

    public:
        ModExpression(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB);

        [[nodiscard]] long evaluateAsInteger(const Context& context) const override;

        [[nodiscard]] double evaluateAsDecimal(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        std::shared_ptr<Expression> operandA_;
        std::shared_ptr<Expression> operandB_;
    };

    inline auto make_mod(std::shared_ptr<Expression> operandA, std::shared_ptr<Expression> operandB) {
        return std::make_shared<ModExpression>(std::move(operandA), std::move(operandB));
    }

}

#endif //EXPRL_CPP_MODEXPRESSION_H
