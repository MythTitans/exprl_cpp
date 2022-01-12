#ifndef EXPRL_CPP_VARIABLE_H
#define EXPRL_CPP_VARIABLE_H

#include <string>
#include <variant>

#include "EvaluationException.h"

namespace mythtitans::exprl::eval {

    class Variable {

        using Value = std::variant<bool, long, double, std::string>;

    public:
        Variable() = default;

        Variable(std::string variable, Value value);

        [[nodiscard]] bool asBoolean() const;

        [[nodiscard]] long asInteger() const;

        [[nodiscard]] double asDecimal() const;

        [[nodiscard]] std::string asText() const;

    protected:
        Value value_;

    private:
        std::string variable_;
    };

}

#endif //EXPRL_CPP_VARIABLE_H
