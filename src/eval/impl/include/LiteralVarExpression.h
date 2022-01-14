#ifndef EXPRL_CPP_LITERALVAREXPRESSION_H
#define EXPRL_CPP_LITERALVAREXPRESSION_H

#include <memory>
#include <unordered_set>
#include <string>

#include "../../include/Expression.h"
#include "../../include/Variable.h"

namespace mythtitans::exprl::eval::impl {

    class LiteralVarExpression : public Expression {

    public:
        explicit LiteralVarExpression(std::string operand);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] long evaluateAsInteger(const Context& context) const override;

        [[nodiscard]] double evaluateAsDecimal(const Context& context) const override;

        [[nodiscard]] std::string evaluateAsText(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const override;

        [[nodiscard]] std::unordered_set<std::string> getLiteralVariables() const override;

    private:
        [[nodiscard]] Variable accessVariable(const Context& context) const;

    private:
        std::string operand_;
    };

    inline auto make_var(std::string operand) {
        return std::make_shared<LiteralVarExpression>(std::move(operand));
    }

}

#endif //EXPRL_CPP_LITERALVAREXPRESSION_H
