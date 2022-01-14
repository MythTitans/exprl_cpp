#ifndef EXPRL_CPP_EXPRESSION_H
#define EXPRL_CPP_EXPRESSION_H

#include <exception>
#include <string>
#include <unordered_set>

#include "Context.h"

namespace mythtitans::exprl::eval {

    class Expression {

    public:
        Expression() = default;

        Expression(const Expression& ref) = delete;

        Expression(Expression&& ref) = delete;

        Expression& operator=(const Expression& ref) = delete;

        Expression& operator=(Expression&& ref) = delete;

        virtual ~Expression() = default;

        [[nodiscard]] virtual bool evaluateAsBoolean(const Context& context) const;

        [[nodiscard]] virtual long evaluateAsInteger(const Context& context) const;

        [[nodiscard]] virtual double evaluateAsDecimal(const Context& context) const;

        [[nodiscard]] virtual std::string evaluateAsText(const Context& context) const;

        [[nodiscard]] virtual std::string getExpressionName() const = 0;

        [[nodiscard]] virtual std::unordered_set<std::string> getLiteralVariables() const = 0;
    };

}

#endif //EXPRL_CPP_EXPRESSION_H
