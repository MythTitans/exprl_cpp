#ifndef EXPRL_CPP_LITERALEXPRESSION_H
#define EXPRL_CPP_LITERALEXPRESSION_H

#include "../../include/Expression.h"

#include <string>

namespace mythtitans::exprl::eval::impl {

    class BooleanLiteralExpression : public Expression {

    public:
        explicit BooleanLiteralExpression(bool operand);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const override;

        [[nodiscard]] std::unordered_set<std::string> getLiteralVariables() const override;

    private:
        bool operand_;
    };

    class IntegerLiteralExpression : public Expression {

    public:
        explicit IntegerLiteralExpression(long operand);

        [[nodiscard]] long evaluateAsInteger(const Context& context) const override;

        [[nodiscard]] double evaluateAsDecimal(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const override;

        [[nodiscard]] std::unordered_set<std::string> getLiteralVariables() const override;

    private:
        long operand_;
    };

    class DecimalLiteralExpression : public Expression {

    public:
        explicit DecimalLiteralExpression(double operand);

        [[nodiscard]] double evaluateAsDecimal(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const override;

        [[nodiscard]] std::unordered_set<std::string> getLiteralVariables() const override;

    private:
        double operand_;
    };

    class TextLiteralExpression : public Expression {

    public:
        explicit TextLiteralExpression(std::string operand);

        [[nodiscard]] std::string evaluateAsText(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const override;

        [[nodiscard]] std::unordered_set<std::string> getLiteralVariables() const override;

    private:
        std::string operand_;
    };

    template<class T>
    std::shared_ptr<Expression> make_literal(T value);

    template<>
    inline std::shared_ptr<Expression> make_literal(bool value) {
        return std::make_shared<BooleanLiteralExpression>(value);
    }

    template<>
    inline std::shared_ptr<Expression> make_literal(long value) {
        return std::make_shared<IntegerLiteralExpression>(value);
    }

    template<>
    inline std::shared_ptr<Expression> make_literal(double value) {
        return std::make_shared<DecimalLiteralExpression>(value);
    }

    template<>
    inline std::shared_ptr<Expression> make_literal(std::string value) {
        return std::make_shared<TextLiteralExpression>(std::move(value));
    }

    template<>
    inline std::shared_ptr<Expression> make_literal(int value) {
        return make_literal(static_cast<long>(value));
    }

    template<>
    inline std::shared_ptr<Expression> make_literal(const char* value) {
        return make_literal(std::string(value));
    }
}

#endif //EXPRL_CPP_LITERALEXPRESSION_H
