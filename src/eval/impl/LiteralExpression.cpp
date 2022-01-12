#include "include/LiteralExpression.h"

#include <sstream>

#include "../../Globals.h"

namespace mythtitans::exprl::eval::impl {

    BooleanLiteralExpression::BooleanLiteralExpression(bool operand) : operand_{operand} {
    }

    bool BooleanLiteralExpression::evaluateAsBoolean(const Context& context) const {
        return operand_;
    }

    std::string BooleanLiteralExpression::getExpressionName() const noexcept {
        return operand_ ? "true" : "false";
    }

    IntegerLiteralExpression::IntegerLiteralExpression(long operand) : operand_{operand} {
    }

    long IntegerLiteralExpression::evaluateAsInteger(const Context& context) const {
        return operand_;
    }

    double IntegerLiteralExpression::evaluateAsDecimal(const Context& context) const {
        return static_cast<double>(operand_);
    }

    std::string IntegerLiteralExpression::getExpressionName() const noexcept {
        return std::to_string(operand_);
    }

    DecimalLiteralExpression::DecimalLiteralExpression(double operand) : operand_{operand} {
    }

    double DecimalLiteralExpression::evaluateAsDecimal(const Context& context) const {
        return operand_;
    }

    std::string DecimalLiteralExpression::getExpressionName() const noexcept {
        std::ostringstream oss;
        oss.precision(6);
        oss << std::fixed << operand_;
        return oss.str();
    }

    TextLiteralExpression::TextLiteralExpression(std::string operand) : operand_{std::move(operand)} {
    }

    std::string TextLiteralExpression::evaluateAsText(const Context& context) const {
        return operand_;
    }

    std::string TextLiteralExpression::getExpressionName() const noexcept {
        return operand_;
    }
}
