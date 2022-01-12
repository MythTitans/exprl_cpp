#ifndef EXPRL_CPP_CONTEXT_H
#define EXPRL_CPP_CONTEXT_H

#include <unordered_map>
#include <memory>
#include <optional>
#include <functional>
#include <string>

#include "Variable.h"

namespace mythtitans::exprl::eval {

    class Context {

    public:
        Context();

        explicit Context(std::function<void(std::string)> debugMessageHandler);

        void setVariable(const std::string& variable, bool value);

        void setVariable(const std::string& variable, long value);

        void setVariable(const std::string& variable, double value);

        void setVariable(const std::string& variable, std::string value);

        void setVariable(const std::string& variable, int value);

        void setVariable(const std::string& variable, const char* value);

        [[nodiscard]] std::optional<Variable> getVariable(const std::string& variable) const;

        void reportDebugMessage(std::string message) const;

    private:
        std::unordered_map<std::string, Variable> variables_;
        std::function<void(std::string)> debugMessageHandler_;
    };

}

#endif //EXPRL_CPP_CONTEXT_H
