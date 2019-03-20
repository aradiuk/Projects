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
    for (const auto &it : queryFacts_)
        std::cout << it.name_ << " = " << it.status_ << std::endl;
}

std::set<Fact> Parser::FindAllFacts(const std::vector<std::vector<Token>> &tokens)
{
#ifdef LOG
    std::cout << __FUNCTION__ << std::endl;
#endif

    Token initialFacts;
    std::set<Fact> facts;
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
                queryFacts_ = FindAllQueryFacts(itt);
            }
        }
    }

    std::set<Fact> initiatedFacts;
    for (auto &fact : facts) {
        Fact initFact {fact};
        const auto inFact = initialFacts.value_.find(fact.name_.front());
        if (inFact != std::string::npos) {
            initFact.status_ = true;
        }
        initiatedFacts.insert(initFact);
    }
    facts_ = initiatedFacts;

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

std::set<Fact> Parser::FindAllQueryFacts(const Token &token)
{
    std::set<Fact> facts;
    if (token.value_.front() != '?') {
        throw "Query is wrong. Missing '?'";
    }
    for (const auto &symb : token.value_) {
        if (symb == '?') {
            continue;
        }

        std::string factName{symb};
        facts.emplace(factName, false);
    }

    return facts;
}
