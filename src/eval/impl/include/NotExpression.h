#ifndef EXPRL_CPP_NOTEXPRESSION_H
#define EXPRL_CPP_NOTEXPRESSION_H

#include <memory>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class NotExpression : public Expression {

    public:
        explicit NotExpression(std::shared_ptr<Expression> operand);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        std::shared_ptr<Expression> operand_;
    };

    inline auto make_not(std::shared_ptr<Expression> operand) {
        return std::make_shared<NotExpression>(std::move(operand));
    }

}

#endif //EXPRL_CPP_NOTEXPRESSION_H
