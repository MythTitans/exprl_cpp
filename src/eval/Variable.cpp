#include "include/Variable.h"

namespace mythtitans::exprl::eval {

    Variable::Variable(std::string variable, Value value)
            : variable_(std::move(variable)),
              value_(std::move(value)) {
    }

    bool Variable::asBoolean() const {
        if (std::holds_alternative<bool>(value_)) {
            return std::get<bool>(value_);
        }

        throw EvaluationException("Variable [" + variable_ + "] cannot be evaluated as [boolean].");
    }

    long Variable::asInteger() const {
        if (std::holds_alternative<long>(value_)) {
            return std::get<long>(value_);
        }

        throw EvaluationException("Variable [" + variable_ + "] cannot be evaluated as [integer].");
    }

    double Variable::asDecimal() const {
        if (std::holds_alternative<double>(value_)) {
            return std::get<double>(value_);
        }

        if (std::holds_alternative<long>(value_)) {
            return std::get<long>(value_);
        }

        throw EvaluationException("Variable [" + variable_ + "] cannot be evaluated as [decimal].");
    }

    std::string Variable::asText() const {
        if (std::holds_alternative<std::string>(value_)) {
            return std::get<std::string>(value_);
        }

        throw EvaluationException("Variable [" + variable_ + "] cannot be evaluated as [text].");
    }
}