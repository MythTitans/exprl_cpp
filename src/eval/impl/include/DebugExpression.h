#ifndef EXPRL_CPP_DEBUGEXPRESSION_H
#define EXPRL_CPP_DEBUGEXPRESSION_H

#include <memory>
#include <sstream>
#include <unordered_set>

#include "../../include/Expression.h"

namespace mythtitans::exprl::eval::impl {

    class DebugExpression : public Expression {

    public:
        DebugExpression(std::shared_ptr<Expression> operandDebugged, std::shared_ptr<Expression> operandDebugLabel);

        [[nodiscard]] bool evaluateAsBoolean(const Context& context) const override;

        [[nodiscard]] long evaluateAsInteger(const Context& context) const override;

        [[nodiscard]] double evaluateAsDecimal(const Context& context) const override;

        [[nodiscard]] std::string evaluateAsText(const Context& context) const override;

        [[nodiscard]] std::string getExpressionName() const override;

        [[nodiscard]] std::unordered_set<std::string> getLiteralVariables() const override;

    private:
        template<typename T>
        void produceDebugMessage(const T& result, const Context& context) const {
            std::ostringstream oss;
            oss.precision(6);
            oss << std::fixed << operandDebugLabel_->evaluateAsText(context) << " : " << std::boolalpha << result
                << std::noboolalpha;
            context.reportDebugMessage(oss.str());
        }

    private:
        std::shared_ptr<Expression> operandDebugged_;
        std::shared_ptr<Expression> operandDebugLabel_;
    };

    inline auto make_debug(std::shared_ptr<Expression> operandDebugged,
                           std::shared_ptr<Expression> operandDebugLabel) {
        return std::make_shared<DebugExpression>(std::move(operandDebugged), std::move(operandDebugLabel));
    }

}

#endif //EXPRL_CPP_DEBUGEXPRESSION_H
