#ifndef EXPRL_CPP_LENEXPRESSION_H
#define EXPRL_CPP_LENEXPRESSION_H

#include <memory>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class LenExpression : public Expression {

    public:
        explicit LenExpression(std::shared_ptr<Expression> operand);

        [[nodiscard]] long evaluateAsInteger(const Context& context) const override;

        [[nodiscard]] double evaluateAsDecimal(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        std::shared_ptr<Expression> operand_;
    };

    inline auto make_len(std::shared_ptr<Expression> operand) {
        return std::make_shared<LenExpression>(std::move(operand));
    }

}

#endif //EXPRL_CPP_LENEXPRESSION_H
