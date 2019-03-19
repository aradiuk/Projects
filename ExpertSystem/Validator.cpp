/*
 * Validator.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: aradiuk
 */

#include "Validator.hpp"

#define LOG

Validator::Validator()
{}

Validator::~Validator()
{}

Validator::Validator(const Validator &obj)
{}

Validator& Validator::operator=(const Validator &obj)
{
    return *this;
}

void Validator::ValidateTokens(const std::vector<std::vector<Token>> &tokens)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    if (tokens.empty() || tokens.size() < 3) {
        throw "File is empty or not enough tokens.";
    }

    int rules = 0;
    int initialFacts = 0;
    int queries = 0;
    for (const auto &tokenLine : tokens) {
        if (tokenLine.empty()) {
            throw "Tokenline is empty or contains spaces.";
        }

        if (tokenLine.size() == 1) {
            if (!rules) {
                throw "No rules or an unexpected token before the rules.";
            }
            TokenType type = (initialFacts ? TokenType::Query : TokenType::InitialFact);
            if (tokenLine.front().type_ != type) {
                throw "Unexpected token: " + tokenLine.front().value_;
            }
            if (type == TokenType::InitialFact) {
                ++initialFacts;
            } else if (type == TokenType::Query) {
                ++queries;
            }
        } else {
            ++rules;
        }
    }

    ValidateTokensQuantity(rules, initialFacts, queries);
}

void Validator::ValidateTokensQuantity(int rules, int initialFacts, int queries)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    if (!rules || initialFacts != 1 || queries != 1) {
        std::stringstream ss;
        ss << "(" << rules << ", " << initialFacts << ", " << queries << ")";
        throw "Wrong number of rules, initial facts or queries: " + ss.str();
    }
}


void Validator::ValidateRules(const std::vector<Rule> &rules)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    for (const auto &rule : rules) {
        if ((rule.operand_.type_ != TokenType::Implies &&
             rule.operand_.type_ != TokenType::IfAndOnlyIf) ||
             rule.lhs_.empty() || rule.rhs_.empty()) {
            throw "Part of a rule is empty or operand is wrong.";
        }

        ValidateOneSide(rule.lhs_);
        ValidateOneSide(rule.rhs_);
    }
}

void Validator::ValidateOneSide(const std::vector<Token> &tokens)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    std::set<TokenType> operands_ = {TokenType::And, TokenType::Or, TokenType::Xor};
    if (operands_.find(tokens.front().type_) != operands_.end() ||
        operands_.find(tokens.back().type_) != operands_.end()) {
        throw "Rule part begins or ends with an operand.";
    }

    int openParentheses = std::count_if(tokens.begin(), tokens.end(), [](const Token &token) -> bool {
        return token.type_ == TokenType::OpenParenthesis;
    });
    int closeParentheses = std::count_if(tokens.begin(), tokens.end(), [](const Token &token) -> bool {
        return token.type_ == TokenType::CloseParenthesis;
    });
    if (openParentheses != closeParentheses) {
        throw "No parenthesis to form a parentheses.";
    }
    for (const auto &token : tokens) {
        if (token.type_ >= TokenType::Implies && token.type_ != TokenType::Fact) {
            throw "Unexoected token type in a rule encountered.";
        }


    }
}
