#include "include/Expression.h"

namespace mythtitans::exprl::eval {

    bool Expression::evaluateAsBoolean(const Context& context) const {
        throw EvaluationException::booleanEvaluationError(getExpressionName());
    }

    long Expression::evaluateAsInteger(const Context& context) const {
        throw EvaluationException::integerEvaluationError(getExpressionName());
    }

    double Expression::evaluateAsDecimal(const Context& context) const {
        throw EvaluationException::decimalEvaluationError(getExpressionName());
    }

    std::string Expression::evaluateAsText(const Context& context) const {
        throw EvaluationException::textEvaluationError(getExpressionName());
    }
}