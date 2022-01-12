#ifndef EXPRL_CPP_PARSER_H
#define EXPRL_CPP_PARSER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "../../eval/include/Expression.h"

namespace mythtitans::exprl::parser {

    class TokenNode;

    class Parser {

    public:
        [[nodiscard]] static std::shared_ptr<eval::Expression> parse(const std::string& expression);

    private:
        [[nodiscard]] static std::unique_ptr<TokenNode> buildAST(const std::string& expression);

        [[nodiscard]] static std::unique_ptr<eval::Expression> parseExpression(TokenNode* ast);

        [[nodiscard]] static std::unique_ptr<eval::Expression> parseExpression(const std::string& expression,
                                                                               std::vector<std::unique_ptr<eval::Expression>>&& arguments);

        [[nodiscard]] static std::unique_ptr<eval::Expression> parseLiteral(const std::string& expression);

        [[nodiscard]] static std::unique_ptr<eval::Expression> parseUnaryExpression(const std::string& expressionName,
                                                                                    std::vector<std::unique_ptr<eval::Expression>>&& arguments);

        [[nodiscard]] static std::unique_ptr<eval::Expression> parseBinaryExpression(const std::string& expressionName,
                                                                                     std::vector<std::unique_ptr<eval::Expression>>&& arguments);

        [[nodiscard]] static std::unique_ptr<eval::Expression>
        parseBiOrNaryExpression(const std::string& expressionName,
                                std::vector<std::unique_ptr<eval::Expression>>&& arguments);

        [[nodiscard]] static std::unique_ptr<eval::Expression> parseTernaryExpression(const std::string& expressionName,
                                                                                      std::vector<std::unique_ptr<eval::Expression>>&& arguments);
    };

    class ParsingException : public std::exception {

    public:
        explicit ParsingException(std::string&& message) noexcept;

        [[nodiscard]] static ParsingException
        invalidArgumentsCount(const std::string& token, int expectedCount, int actualCount);

        [[nodiscard]] static ParsingException
        invalidArgumentsAtLeastCount(const std::string& token, int expectedCount, int actualCount);

        [[nodiscard]] static ParsingException unexpectedSymbol(char symbol, int index);

        [[nodiscard]] const char* what() const noexcept override;

    private:
        std::string message_;
    };

    class TokenNode {

    public:
        explicit TokenNode(std::string token);

        TokenNode(std::string token, TokenNode* parent);

        TokenNode& addChild(const std::string& token);

        [[nodiscard]] const std::string& getToken() const noexcept;

        [[nodiscard]] const std::vector<std::unique_ptr<TokenNode>>& getChildren() const noexcept;

        [[nodiscard]] TokenNode* getParent() const noexcept;

    private:
        const std::string token_;
        std::vector<std::unique_ptr<TokenNode>> children_;
        TokenNode* parent_;
    };

}

#endif //EXPRL_CPP_PARSER_H
