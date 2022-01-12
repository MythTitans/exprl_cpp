#include "include/Context.h"

namespace mythtitans::exprl::eval {

    Context::Context() : variables_(), debugMessageHandler_([](std::string) {}) {
    }

    Context::Context(std::function<void(std::string)> debugMessageHandler)
            : debugMessageHandler_(std::move(debugMessageHandler)) {
    }

    void Context::setVariable(const std::string& variable, bool value) {
        variables_[variable] = Variable(variable, value);
    }

    void Context::setVariable(const std::string& variable, long value) {
        variables_[variable] = Variable(variable, value);
    }

    void Context::setVariable(const std::string& variable, double value) {
        variables_[variable] = Variable(variable, value);
    }

    void Context::setVariable(const std::string& variable, std::string value) {
        variables_[variable] = Variable(variable, std::move(value));
    }

    void Context::setVariable(const std::string& variable, int value) {
        setVariable(variable, static_cast<long>(value));
    }

    void Context::setVariable(const std::string& variable, const char* value) {
        setVariable(variable, std::string(value));
    }

    std::optional<Variable> Context::getVariable(const std::string& variable) const {
        const auto& result = variables_.find(variable);
        if (result != variables_.end()) {
            return {result->second};
        }

        return {};
    }

    void Context::reportDebugMessage(std::string message) const {
        debugMessageHandler_(std::move(message));
    }

}