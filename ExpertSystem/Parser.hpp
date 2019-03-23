//
// Created by Andrew Radiuk on 2019-03-17.
//

#ifndef EXPERTSYSTEM_PARSER_HPP
#define EXPERTSYSTEM_PARSER_HPP

#include <set>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "Lexer.hpp"

struct Rule {
    Rule()
        : visited_(false)
    {}
    Rule(Token token, bool eval = false)
        : operator_(token)
        , visited_(eval)
    {}

    std::vector<Token> lhs_;
    std::vector<Token> rhs_;
    Token operator_;
    bool visited_;
};

class Parser {
    private:
        std::map<std::string, Fact> facts_;
        std::vector<Rule> rules_;
        std::map<std::string, Fact> queryFacts_;
        Token initialFacts_;

    public:
        Parser();
        ~Parser();
        Parser(const Parser &obj);
        Parser &operator=(const Parser &obj);
        std::map<std::string, Fact> GetFacts() const {return facts_;};
        std::vector<Rule> GetRules() const {return rules_;};
        std::map<std::string, Fact> GetQueryFacts() const {return queryFacts_;};
        Token GetInitialFacts() const {return initialFacts_;};

        void ParseTokens(const std::vector<std::vector<Token>> &tokens);
        std::map<std::string, Fact> FindAllFacts(const
        std::vector<std::vector<Token>> &tokens);
        std::vector<Rule> FindAllRules(const std::vector<std::vector<Token>> &tokens);
        std::map<std::string, Fact> FindAllQueryFacts(const Token &token);
};


#endif //EXPERTSYSTEM_PARSER_HPP
