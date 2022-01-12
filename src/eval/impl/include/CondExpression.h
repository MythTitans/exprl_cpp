#ifndef EXPRL_CPP_CONDEXPRESSION_H
#define EXPRL_CPP_CONDEXPRESSION_H

#include <memory>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class CondExpression : public Expression {

    public:
        CondExpression(std::shared_ptr<Expression> operandCond,
                       std::shared_ptr<Expression> operandThen,
                       std::shared_ptr<Expression> operandElse);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] long evaluateAsInteger(const Context& context) const override;

        [[nodiscard]] double evaluateAsDecimal(const Context& context) const override;

        [[nodiscard]] std::string evaluateAsText(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        [[nodiscard]] const std::shared_ptr<Expression>& evaluateCondition(const Context& context) const;

    private:
        std::shared_ptr<Expression> operandCond_;
        std::shared_ptr<Expression> operandThen_;
        std::shared_ptr<Expression> operandElse_;
    };

    inline auto make_cond(std::shared_ptr<Expression> operandCond,
                          std::shared_ptr<Expression> operandThen,
                          std::shared_ptr<Expression> operandElse) {
        return std::make_shared<CondExpression>(std::move(operandCond), std::move(operandThen), std::move(operandElse));
    }

}

#endif //EXPRL_CPP_CONDEXPRESSION_H
