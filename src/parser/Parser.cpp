#include "include/Parser.h"

#include <sstream>
#include <vector>
#include <regex>

#include "../Globals.h"
#include "../util/include/StringUtilities.h"
#include "../eval/impl/include/LiteralExpression.h"
#include "../eval/impl/include/NotExpression.h"
#include "../eval/impl/include/AndExpression.h"
#include "../eval/impl/include/OrExpression.h"
#include "../eval/impl/include/AddExpression.h"
#include "../eval/impl/include/SubExpression.h"
#include "../eval/impl/include/MulExpression.h"
#include "../eval/impl/include/DivExpression.h"
#include "../eval/impl/include/ModExpression.h"
#include "../eval/impl/include/StartsExpression.h"
#include "../eval/impl/include/EndsExpression.h"
#include "../eval/impl/include/InExpression.h"
#include "../eval/impl/include/SubstrExpression.h"
#include "../eval/impl/include/SubstrlExpression.h"
#include "../eval/impl/include/LenExpression.h"
#include "../eval/impl/include/EqExpression.h"
#include "../eval/impl/include/NeqExpression.h"
#include "../eval/impl/include/LtExpression.h"
#include "../eval/impl/include/LteExpression.h"
#include "../eval/impl/include/GtExpression.h"
#include "../eval/impl/include/GteExpression.h"
#include "../eval/impl/include/MinExpression.h"
#include "../eval/impl/include/MaxExpression.h"
#include "../eval/impl/include/VarExpression.h"
#include "../eval/impl/include/CondExpression.h"
#include "../eval/impl/include/ConcatExpression.h"
#include "../eval/impl/include/DebugExpression.h"

using namespace mythtitans::exprl::eval;
using namespace mythtitans::exprl::eval::impl;
using namespace mythtitans::exprl::globals;
using namespace mythtitans::exprl::util;

namespace mythtitans::exprl::parser {

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

    static const std::unordered_map<std::string, ExpressionSwitch> SWITCH_MAP = {
            {NOT_EXPRESSION,     ExpressionSwitch::NOT_EXPRESSION},
            {AND_EXPRESSION,     ExpressionSwitch::AND_EXPRESSION},
            {OR_EXPRESSION,      ExpressionSwitch::OR_EXPRESSION},
            {ADD_EXPRESSION,     ExpressionSwitch::ADD_EXPRESSION},
            {SUB_EXPRESSION,     ExpressionSwitch::SUB_EXPRESSION},
            {MUL_EXPRESSION,     ExpressionSwitch::MUL_EXPRESSION},
            {DIV_EXPRESSION,     ExpressionSwitch::DIV_EXPRESSION},
            {MOD_EXPRESSION,     ExpressionSwitch::MOD_EXPRESSION},
            {STARTS_EXPRESSION,  ExpressionSwitch::STARTS_EXPRESSION},
            {ENDS_EXPRESSION,    ExpressionSwitch::ENDS_EXPRESSION},
            {IN_EXPRESSION,      ExpressionSwitch::IN_EXPRESSION},
            {SUBSTR_EXPRESSION,  ExpressionSwitch::SUBSTR_EXPRESSION},
            {SUBSTRL_EXPRESSION, ExpressionSwitch::SUBSTRL_EXPRESSION},
            {LEN_EXPRESSION,     ExpressionSwitch::LEN_EXPRESSION},
            {EQ_EXPRESSION,      ExpressionSwitch::EQ_EXPRESSION},
            {NEQ_EXPRESSION,     ExpressionSwitch::NEQ_EXPRESSION},
            {LT_EXPRESSION,      ExpressionSwitch::LT_EXPRESSION},
            {LTE_EXPRESSION,     ExpressionSwitch::LTE_EXPRESSION},
            {GT_EXPRESSION,      ExpressionSwitch::GT_EXPRESSION},
            {GTE_EXPRESSION,     ExpressionSwitch::GTE_EXPRESSION},
            {MIN_EXPRESSION,     ExpressionSwitch::MIN_EXPRESSION},
            {MAX_EXPRESSION,     ExpressionSwitch::MAX_EXPRESSION},
            {VAR_EXPRESSION,     ExpressionSwitch::VAR_EXPRESSION},
            {COND_EXPRESSION,    ExpressionSwitch::COND_EXPRESSION},
            {CONCAT_EXPRESSION,  ExpressionSwitch::CONCAT_EXPRESSION},
            {DEBUG_EXPRESSION,   ExpressionSwitch::DEBUG_EXPRESSION}
    };

    static const auto DECIMAL_PATTERN = std::regex("[+-]?\\d*.\\d+");
    static const auto INTEGER_PATTERN = std::regex("[+-]?\\d+");

    std::shared_ptr<Expression> Parser::parse(const std::string& expression) {
        auto ast = buildAST(expression);
        // Ignores abstract root node
        return parseExpression(ast->getChildren()[0].get());
    }

    std::unique_ptr<TokenNode> Parser::buildAST(const std::string& expression) {
        // Abstract root node to simplify building the tree
        auto ast = std::make_unique<TokenNode>("");
        auto currentNode = ast.get();
        bool interpret = true;

        std::string token;
        for (int i = 0; i < expression.length(); ++i) {
            char currentCharacter = expression[i];

            if (interpret) {
                TokenNode* childNode;
                switch (currentCharacter) {
                    case '(':
                        childNode = &currentNode->addChild(token);
                        if (childNode == currentNode) {
                            throw ParsingException::unexpectedSymbol('(', i);
                        }
                        currentNode = childNode;
                        token.clear();
                        break;

                    case ')':
                        currentNode->addChild(token);
                        currentNode = currentNode->getParent();
                        if (currentNode == nullptr) {
                            throw ParsingException::unexpectedSymbol(')', i);
                        }
                        token.clear();
                        break;

                    case ',':
                        currentNode->addChild(token);
                        token.clear();
                        break;

                    case ' ':
                        break;

                    case '\'':
                        interpret = false;
                    default:
                        token += expression[i];
                        break;
                }
            } else {
                if (currentCharacter == '\'') {
                    interpret = true;
                }

                token += expression[i];
            }
        }

        currentNode->addChild(token);

        if (ast.get() != currentNode) {
            throw ParsingException("Incomplete expression.");
        }

        return ast;
    }

    std::unique_ptr<Expression> Parser::parseExpression(TokenNode* ast) {
        const auto& children = ast->getChildren();

        std::vector<std::unique_ptr<Expression>> arguments;

        for (const auto& child: children) {
            arguments.push_back(parseExpression(child.get()));
        }

        if (!arguments.empty()) {
            return parseExpression(ast->getToken(), std::move(arguments));
        }

        return parseLiteral(ast->getToken());
    }

    std::unique_ptr<Expression> Parser::parseExpression(const std::string& expression,
                                                        std::vector<std::unique_ptr<Expression>>&& arguments) {

        ExpressionSwitch expressionCase;

        try {
            expressionCase = SWITCH_MAP.at(expression);
        } catch (std::out_of_range& e) {
            throw ParsingException("Unrecognized expression [" + expression + "].");
        }

        switch (expressionCase) {
            case ExpressionSwitch::NOT_EXPRESSION:
            case ExpressionSwitch::LEN_EXPRESSION:
            case ExpressionSwitch::VAR_EXPRESSION:
                return parseUnaryExpression(expression, std::move(arguments));

            case ExpressionSwitch::EQ_EXPRESSION:
            case ExpressionSwitch::NEQ_EXPRESSION:
            case ExpressionSwitch::LT_EXPRESSION:
            case ExpressionSwitch::LTE_EXPRESSION:
            case ExpressionSwitch::GT_EXPRESSION:
            case ExpressionSwitch::GTE_EXPRESSION:
            case ExpressionSwitch::SUB_EXPRESSION:
            case ExpressionSwitch::DIV_EXPRESSION:
            case ExpressionSwitch::MOD_EXPRESSION:
            case ExpressionSwitch::STARTS_EXPRESSION:
            case ExpressionSwitch::ENDS_EXPRESSION:
            case ExpressionSwitch::IN_EXPRESSION:
            case ExpressionSwitch::DEBUG_EXPRESSION:
                return parseBinaryExpression(expression, std::move(arguments));

            case ExpressionSwitch::AND_EXPRESSION:
            case ExpressionSwitch::OR_EXPRESSION:
            case ExpressionSwitch::ADD_EXPRESSION:
            case ExpressionSwitch::MUL_EXPRESSION:
            case ExpressionSwitch::MIN_EXPRESSION:
            case ExpressionSwitch::MAX_EXPRESSION:
            case ExpressionSwitch::CONCAT_EXPRESSION:
                return parseBiOrNaryExpression(expression, std::move(arguments));

            case ExpressionSwitch::SUBSTR_EXPRESSION:
            case ExpressionSwitch::SUBSTRL_EXPRESSION:
            case ExpressionSwitch::COND_EXPRESSION:
                return parseTernaryExpression(expression, std::move(arguments));
        }

        throw ParsingException("Unrecognized expression [" + expression + "].");
    }

    std::unique_ptr<Expression> Parser::parseLiteral(const std::string& expression) {
        bool startsAsText = starts_with(expression, "'");
        bool endsAsText = ends_with(expression, "'");
        if (startsAsText || endsAsText) {
            if (!(startsAsText && endsAsText)) {
                throw ParsingException("Invalid text literal [" + expression + "].");
            }

            return std::make_unique<TextLiteralExpression>(expression.substr(1, expression.length() - 2));
        }

        if (expression == "true") {
            return std::make_unique<BooleanLiteralExpression>(true);
        } else if (expression == "false") {
            return std::make_unique<BooleanLiteralExpression>(false);
        }

        if (contains(expression, ".")) {
            if (std::regex_match(std::cbegin(expression), std::cend(expression), DECIMAL_PATTERN)) {
                try {
                    return std::make_unique<DecimalLiteralExpression>(std::stod(expression));
                } catch (const std::invalid_argument& e) {
                    // Ignored
                }
            }
        } else {
            if (std::regex_match(std::cbegin(expression), std::cend(expression), INTEGER_PATTERN)) {
                try {
                    return std::make_unique<IntegerLiteralExpression>(std::stol(expression));
                } catch (const std::invalid_argument& e) {
                    // Ignored
                }
            }
        }

        throw ParsingException("Invalid literal [" + expression + "].");
    }

    std::unique_ptr<Expression> Parser::parseUnaryExpression(const std::string& expressionName,
                                                             std::vector<std::unique_ptr<Expression>>&& arguments) {
        if (arguments.size() != 1) {
            throw ParsingException::invalidArgumentsCount(expressionName, 1, arguments.size());
        }

        auto arg = std::move(arguments[0]);

        switch (SWITCH_MAP.at(expressionName)) {
            case ExpressionSwitch::NOT_EXPRESSION:
                return std::make_unique<NotExpression>(std::move(arg));
            case ExpressionSwitch::LEN_EXPRESSION:
                return std::make_unique<LenExpression>(std::move(arg));
            case ExpressionSwitch::VAR_EXPRESSION:
                return std::make_unique<VarExpression>(std::move(arg));
            default:
                throw ParsingException("Unrecognized expression [" + expressionName + "].");
        }
    }

    std::unique_ptr<Expression> Parser::parseBinaryExpression(const std::string& expressionName,
                                                              std::vector<std::unique_ptr<Expression>>&& arguments) {
        if (arguments.size() != 2) {
            throw ParsingException::invalidArgumentsCount(expressionName, 2, arguments.size());
        }

        auto argA = std::move(arguments[0]);
        auto argB = std::move(arguments[1]);

        switch (SWITCH_MAP.at(expressionName)) {
            case ExpressionSwitch::SUB_EXPRESSION:
                return std::make_unique<SubExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::DIV_EXPRESSION:
                return std::make_unique<DivExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::MOD_EXPRESSION:
                return std::make_unique<ModExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::STARTS_EXPRESSION:
                return std::make_unique<StartsExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::ENDS_EXPRESSION:
                return std::make_unique<EndsExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::IN_EXPRESSION:
                return std::make_unique<InExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::EQ_EXPRESSION:
                return std::make_unique<EqExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::NEQ_EXPRESSION:
                return std::make_unique<NeqExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::LT_EXPRESSION:
                return std::make_unique<LtExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::LTE_EXPRESSION:
                return std::make_unique<LteExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::GT_EXPRESSION:
                return std::make_unique<GtExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::GTE_EXPRESSION:
                return std::make_unique<GteExpression>(std::move(argA), std::move(argB));
            case ExpressionSwitch::DEBUG_EXPRESSION:
                return std::make_unique<DebugExpression>(std::move(argA), std::move(argB));
            default:
                throw ParsingException("Unrecognized expression [" + expressionName + "].");
        }
    }

    std::unique_ptr<Expression> Parser::parseBiOrNaryExpression(const std::string& expressionName,
                                                                std::vector<std::unique_ptr<Expression>>&& arguments) {
        if (arguments.size() < 2) {
            throw ParsingException::invalidArgumentsAtLeastCount(expressionName, 2, arguments.size());
        }

        std::vector<std::shared_ptr<Expression>> sharedArguments;
        std::move(arguments.begin(), arguments.end(), std::back_inserter(sharedArguments));

        switch (SWITCH_MAP.at(expressionName)) {
            case ExpressionSwitch::AND_EXPRESSION:
                return std::make_unique<AndExpression>(std::move(sharedArguments));
            case ExpressionSwitch::OR_EXPRESSION:
                return std::make_unique<OrExpression>(std::move(sharedArguments));
            case ExpressionSwitch::ADD_EXPRESSION:
                return std::make_unique<AddExpression>(std::move(sharedArguments));
            case ExpressionSwitch::MUL_EXPRESSION:
                return std::make_unique<MulExpression>(std::move(sharedArguments));
            case ExpressionSwitch::MIN_EXPRESSION:
                return std::make_unique<MinExpression>(std::move(sharedArguments));
            case ExpressionSwitch::MAX_EXPRESSION:
                return std::make_unique<MaxExpression>(std::move(sharedArguments));
            case ExpressionSwitch::CONCAT_EXPRESSION:
                return std::make_unique<ConcatExpression>(std::move(sharedArguments));
            default:
                throw ParsingException("Unrecognized expression [" + expressionName + "].");
        }
    }

    std::unique_ptr<Expression> Parser::parseTernaryExpression(const std::string& expressionName,
                                                               std::vector<std::unique_ptr<Expression>>&& arguments) {
        if (arguments.size() != 3) {
            throw ParsingException::invalidArgumentsCount(expressionName, 3, arguments.size());
        }

        auto argA = std::move(arguments[0]);
        auto argB = std::move(arguments[1]);
        auto argC = std::move(arguments[2]);

        switch (SWITCH_MAP.at(expressionName)) {
            case ExpressionSwitch::SUBSTR_EXPRESSION:
                return std::make_unique<SubstrExpression>(std::move(argA), std::move(argB), std::move(argC));
            case ExpressionSwitch::SUBSTRL_EXPRESSION:
                return std::make_unique<SubstrlExpression>(std::move(argA), std::move(argB), std::move(argC));
            case ExpressionSwitch::COND_EXPRESSION:
                return std::make_unique<CondExpression>(std::move(argA), std::move(argB), std::move(argC));
            default:
                throw ParsingException("Unrecognized expression [" + expressionName + "].");
        };
    }

    ParsingException::ParsingException(std::string&& message) noexcept: message_(std::move(message)) {
    }

    ParsingException ParsingException::invalidArgumentsCount(const std::string& token,
                                                             const int expectedCount,
                                                             const int actualCount) {
        std::ostringstream oss;
        oss << "Invalid arguments count for [" << token << "], expected [" << expectedCount << "] but got ["
            << actualCount << "].";
        return ParsingException(oss.str());
    }

    ParsingException ParsingException::invalidArgumentsAtLeastCount(const std::string& token,
                                                                    const int expectedCount,
                                                                    const int actualCount) {
        std::ostringstream oss;
        oss << "Invalid arguments count for [" << token << "], expected at least [" << expectedCount << "] but got ["
            << actualCount << "].";
        return ParsingException(oss.str());
    }

    ParsingException ParsingException::unexpectedSymbol(const char symbol, const int index) {
        std::ostringstream oss;
        oss << "Unexpected symbol [" << symbol << "] at index [" << index << "].";
        return ParsingException(oss.str());
    }

    const char* ParsingException::what() const noexcept {
        return message_.c_str();
    }

    TokenNode::TokenNode(std::string token) : TokenNode(std::move(token), nullptr) {
    }

    TokenNode::TokenNode(std::string token, TokenNode* parent) : token_(std::move(token)), parent_(parent) {
    }

    TokenNode& TokenNode::addChild(const std::string& token) {
        if (token.empty()) {
            return *this;
        }

        auto node = std::make_unique<TokenNode>(token, this);
        children_.push_back(std::move(node));
        return *children_.back();
    }

    const std::string& TokenNode::getToken() const noexcept {
        return token_;
    }

    const std::vector<std::unique_ptr<TokenNode>>& TokenNode::getChildren() const noexcept {
        return children_;
    }

    TokenNode* TokenNode::getParent() const noexcept {
        return parent_;
    }
}