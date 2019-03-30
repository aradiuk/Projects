//
// Created by Andrew Radiuk on 2019-03-17.
//
#include "Parser.hpp"

//#define LOG

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

std::map<std::string, Fact> Parser::FindAllFacts(const std::vector<std::vector<Token>> &tokens)
{
#ifdef LOG
    std::cout << __FUNCTION__ << std::endl;
#endif

    std::map<std::string, Fact> facts;
    for (const auto &it : tokens) {
        for (const auto &itt : it) {
            if (itt.type_ == TokenType::Fact) {
                if (itt.value_.size() != 1) {
                    throw "Fact is too long: " + itt.value_;
                }
                facts.emplace(itt.value_, Fact());
            } else if (itt.type_ == TokenType::InitialFact) {
                initialFacts_ = itt;
            } else if (itt.type_ == TokenType::Query) {
                queryFacts_ = FindAllQueryFacts(itt);
            }
        }
    }

    for (const auto &fact : initialFacts_.value_) {
        if (fact != '=') {
            std::string factStr {fact};
            facts[factStr] = Fact(true);
        }
    }

    for (const auto &fact : queryFacts_) {
        facts.emplace(fact.first, Fact());
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
                rule.operator_ = token;
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

std::map<std::string, Fact> Parser::FindAllQueryFacts(const Token &token)
{
    std::map<std::string, Fact> facts;

    if (token.value_.front() != '?') {
        throw "Query is wrong. Missing '?'";
    }
    for (const auto &symb : token.value_) {
        if (symb == '?') {
            continue;
        }

        std::string factName{symb};
        facts.emplace(factName, Fact());
    }

    return facts;
}
