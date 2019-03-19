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

    if (!rules || initialFacts != 1 || queries != 1) {
        std::stringstream ss;
        ss << "(" << rules << ", " << initialFacts << ", " << queries << ")";
        throw "Wrong number of rules, initial facts or queries: " + ss.str();
    }
}

void Validator::ValidateRule(const Rule &rule)
{

}
