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

        enum class ExpressionSwitch {
            NOT_EXPRESSION,
            AND_EXPRESSION,
            OR_EXPRESSION,
            ADD_EXPRESSION,
            SUB_EXPRESSION,
            MUL_EXPRESSION,
            DIV_EXPRESSION,
            MOD_EXPRESSION,
            STARTS_EXPRESSION,
            ENDS_EXPRESSION,
            IN_EXPRESSION,
            SUBSTR_EXPRESSION,
            SUBSTRL_EXPRESSION,
            LEN_EXPRESSION,
            EQ_EXPRESSION,
            NEQ_EXPRESSION,
            LT_EXPRESSION,
            LTE_EXPRESSION,
            GT_EXPRESSION,
            GTE_EXPRESSION,
            MIN_EXPRESSION,
            MAX_EXPRESSION,
            VAR_EXPRESSION,
            COND_EXPRESSION,
            CONCAT_EXPRESSION,
            DEBUG_EXPRESSION
        };

    private:
        [[nodiscard]] static std::unique_ptr<TokenNode> buildAST(const std::string& expression);

        [[nodiscard]] static std::shared_ptr<eval::Expression> parseExpression(TokenNode* ast);

        [[nodiscard]] static std::shared_ptr<eval::Expression> parseExpression(const std::string& expression,
                                                                               std::vector<std::shared_ptr<eval::Expression>>&& arguments);

        [[nodiscard]] static std::shared_ptr<eval::Expression> parseLiteral(const std::string& expression);

        [[nodiscard]] static std::shared_ptr<eval::Expression> parseUnaryExpression(const std::string& expressionName,
                                                                                    ExpressionSwitch expressionSwitch,
                                                                                    std::vector<std::shared_ptr<eval::Expression>>&& arguments);

        [[nodiscard]] static std::shared_ptr<eval::Expression> parseBinaryExpression(const std::string& expressionName,
                                                                                     ExpressionSwitch expressionSwitch,
                                                                                     std::vector<std::shared_ptr<eval::Expression>>&& arguments);

        [[nodiscard]] static std::shared_ptr<eval::Expression>
        parseBiOrNaryExpression(const std::string& expressionName,
                                ExpressionSwitch expressionSwitch,
                                std::vector<std::shared_ptr<eval::Expression>>&& arguments);

        [[nodiscard]] static std::shared_ptr<eval::Expression> parseTernaryExpression(const std::string& expressionName,
                                                                                      ExpressionSwitch expressionSwitch,
                                                                                      std::vector<std::shared_ptr<eval::Expression>>&& arguments);
    };

    class ParsingException : public std::exception {

    public:
        explicit ParsingException(std::string&& message);

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

        [[nodiscard]] const std::string& getToken() const;

        [[nodiscard]] const std::vector<std::unique_ptr<TokenNode>>& getChildren() const;

        [[nodiscard]] TokenNode* getParent() const;

    private:
        const std::string token_;
        std::vector<std::unique_ptr<TokenNode>> children_;
        TokenNode* parent_;
    };

}

#endif //EXPRL_CPP_PARSER_H
