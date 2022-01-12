#include "include/EvaluationException.h"

namespace mythtitans::exprl::eval {

    EvaluationException::EvaluationException(std::string&& message) noexcept: message_(std::move(message)) {
    }

    const char* EvaluationException::what() const noexcept {
        return message_.c_str();
    }

    EvaluationException EvaluationException::booleanEvaluationError(const std::string& operation) {
        std::string message = "Expression [" + operation + "] cannot be evaluated as [boolean].";
        return EvaluationException{std::move(message)};
    }

    EvaluationException EvaluationException::integerEvaluationError(const std::string& operation) {
        std::string message = "Expression [" + operation + "] cannot be evaluated as [integer].";
        return EvaluationException{std::move(message)};
    }

    EvaluationException EvaluationException::decimalEvaluationError(const std::string& operation) {
        std::string message = "Expression [" + operation + "] cannot be evaluated as [decimal].";
        return EvaluationException{std::move(message)};
    }

    EvaluationException EvaluationException::textEvaluationError(const std::string& operation) {
        std::string message = "Expression [" + operation + "] cannot be evaluated as [text].";
        return EvaluationException{std::move(message)};
    }
}