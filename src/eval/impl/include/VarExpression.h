#ifndef EXPRL_CPP_VAREXPRESSION_H
#define EXPRL_CPP_VAREXPRESSION_H

#include <memory>

#include "../../include/Expression.h"
#include "../../include/Variable.h"

namespace mythtitans::exprl::eval::impl {

    class VarExpression : public Expression {

    public:
        explicit VarExpression(std::shared_ptr<Expression> operand);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] long evaluateAsInteger(const Context& context) const override;

        [[nodiscard]] double evaluateAsDecimal(const Context& context) const override;

        [[nodiscard]] std::string evaluateAsText(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const noexcept override;

    private:
        [[nodiscard]] Variable accessVariable(const Context& context) const;

    private:
        std::shared_ptr<Expression> operand_;
    };

    inline auto make_var(std::shared_ptr<Expression> operand) {
        return std::make_shared<VarExpression>(std::move(operand));
    }

}

#endif //EXPRL_CPP_VAREXPRESSION_H
