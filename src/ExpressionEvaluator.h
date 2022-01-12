#ifndef EXPRL_CPP_EXPRESSIONEVALUATOR_H
#define EXPRL_CPP_EXPRESSIONEVALUATOR_H

#include <string>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <utility>

#include "parser/include/Parser.h"

namespace mythtitans::exprl {

    template<typename Parser = parser::Parser>
    class ExpressionEvaluator {

    public:
        ExpressionEvaluator() = default;

        ExpressionEvaluator(Parser&& parser) : parser_(std::move(parser)) {
        }

        ExpressionEvaluator(eval::Context&& context) : context_(std::move(context)) {
        }

        ExpressionEvaluator(Parser&& parser, eval::Context&& context)
                : parser_(std::move(parser)),
                  context_(std::move(context)) {
        }

        void setVariable(const std::string& variable, bool value) {
            std::unique_lock lock(mutex_);
            context_.setVariable(variable, value);
        }

        void setVariable(const std::string& variable, long value) {
            std::unique_lock lock(mutex_);
            context_.setVariable(variable, value);
        }

        void setVariable(const std::string& variable, double value) {
            std::unique_lock lock(mutex_);
            context_.setVariable(variable, value);
        }

        void setVariable(const std::string& variable, std::string value) {
            std::unique_lock lock(mutex_);
            context_.setVariable(variable, std::move(value));
        }

        bool evaluateAsBoolean(const std::string& expression) {
            return evaluateAsBoolean(parser_.parse(expression));
        }

        long evaluateAsInteger(const std::string& expression) {
            return evaluateAsInteger(parser_.parse(expression));
        }

        double evaluateAsDecimal(const std::string& expression) {
            return evaluateAsDecimal(parser_.parse(expression));
        }

        std::string evaluateAsText(const std::string& expression) {
            return evaluateAsText(parser_.parse(expression));
        }

        bool evaluateAsBoolean(const std::shared_ptr<eval::Expression>& expression) {
            std::shared_lock lock(mutex_);
            return expression->evaluateAsBoolean(context_);
        }

        long evaluateAsInteger(const std::shared_ptr<eval::Expression>& expression) {
            std::shared_lock lock(mutex_);
            return expression->evaluateAsInteger(context_);
        }

        double evaluateAsDecimal(const std::shared_ptr<eval::Expression>& expression) {
            std::shared_lock lock(mutex_);
            return expression->evaluateAsDecimal(context_);
        }

        std::string evaluateAsText(const std::shared_ptr<eval::Expression>& expression) {
            std::shared_lock lock(mutex_);
            return expression->evaluateAsText(context_);
        }

    private:
        Parser parser_;
        eval::Context context_;
        std::shared_mutex mutex_;
    };

}

#endif //EXPRL_CPP_EXPRESSIONEVALUATOR_H
