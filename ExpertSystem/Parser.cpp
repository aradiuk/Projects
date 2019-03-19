//
// Created by Andrew Radiuk on 2019-03-17.
//
#include "Parser.hpp"

#define LOG


Parser::Parser()
{}

Parser::~Parser()
{}

Parser::Parser(const Parser &obj)
{}

Parser& Parser::operator=(const Parser &obj)
{
	return *this;
}

void Parser::ParseTokens(const std::vector<std::vector<Token>> &tokens)
{
#ifdef LOG
    std::cout << __FUNCTION__ << std::endl;
#endif

    facts_ = FindAllFacts(tokens);
    rules_ = FindAllRules(tokens);
}

std::map<std::string, bool> Parser::FindAllFacts(const std::vector<std::vector<Token>> &tokens)
{
#ifdef LOG
    std::cout << __FUNCTION__ << std::endl;
#endif

    Token initialFacts;
    std::map<std::string, bool> facts;
    for (const auto &it : tokens) {
        for (const auto &itt : it) {
            if (itt.type_ == TokenType::Fact) {
                if (itt.value_.size() != 1) {
                    throw "Fact is too long: " + itt.value_;
                }
                facts.emplace(itt.value_, false);
            } else if (itt.type_ == TokenType::InitialFact) {
                initialFacts = itt;
            } else if (itt.type_ == TokenType::Query) {
                query_ = itt;
            }
        }
    }

    for (auto &it : facts) {
        const auto inFact = initialFacts.value_.find(it.first.front());
        if (inFact != std::string::npos) {
            it.second = true;
        }
    }

    if (facts.empty()) {
        throw "No facts or rules.";
    }

    return facts;
}

std::vector<Rule> Parser::FindAllRules(const std::vector<std::vector<Token>> &tokens)
{
#ifdef LOG
    std::cout << __FUNCTION__ << std::endl;
#endif

    std::vector<Rule> rules;
    for (const auto &tokenLine : tokens) {
        if (tokenLine.size() == 1) {
            continue;
        }

        Rule rule;
        std::vector<Token> *handSide = &rule.lhs_;
        for (const auto &token : tokenLine) {
            if (token.type_ != TokenType::Implies &&
                token.type_ != TokenType::IfAndOnlyIf) {
                handSide->push_back(token);
            } else {
                rule.operand_ = token;
                handSide = &rule.rhs_;
            }
        }
        rules.push_back(rule);
    }

    if (rules.empty()) {
        throw "No rules.";
    }

    return rules;
}
