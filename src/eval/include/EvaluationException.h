#ifndef EXPRL_CPP_EVALUATIONEXCEPTION_H
#define EXPRL_CPP_EVALUATIONEXCEPTION_H

#include <exception>
#include <string>

namespace mythtitans::exprl::eval {

    class EvaluationException : public std::exception {

    public:
        explicit EvaluationException(std::string&& message) noexcept;

        [[nodiscard]] static EvaluationException booleanEvaluationError(const std::string& operation);

        [[nodiscard]] static EvaluationException integerEvaluationError(const std::string& operation);

        [[nodiscard]] static EvaluationException decimalEvaluationError(const std::string& operation);

        [[nodiscard]] static EvaluationException textEvaluationError(const std::string& operation);

        [[nodiscard]] const char* what() const noexcept override;

    private:
        std::string message_;
    };

}

#endif //EXPRL_CPP_EVALUATIONEXCEPTION_H
