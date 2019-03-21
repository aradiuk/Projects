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
        : evaluated_(false)
    {}
    Rule(Token token, bool eval = false)
        : operator_(token)
        , evaluated_(eval)
    {}

    std::vector<Token> lhs_;
    std::vector<Token> rhs_;
    Token operator_;
    bool evaluated_;
};

struct Fact {
    Fact()
        : name_("")
        , status_(false)

    {}
    Fact(const std::string &name, bool stat)
        : name_(name)
        , status_(stat)
    {}
    Fact(const Fact &obj)
        : name_(obj.name_)
        , status_(obj.status_)
    {}
    bool operator<(const Fact &obj) const {
        return name_ < obj.name_;
    }

    std::string name_;
    bool status_;
};

class Parser {
    private:
        std::set<Fact> facts_;
        std::vector<Rule> rules_;
        std::set<Fact> queryFacts_;

    public:
        Parser();
        ~Parser();
        Parser(const Parser &obj);
        Parser &operator=(const Parser &obj);
        std::set<Fact> GetFacts() const {return facts_;};
        std::vector<Rule> GetRules() const {return rules_;};

        void ParseTokens(const std::vector<std::vector<Token>> &tokens);
        std::set<Fact> FindAllFacts(const std::vector<std::vector<Token>> &tokens);
        std::vector<Rule> FindAllRules(const std::vector<std::vector<Token>> &tokens);
        std::set<Fact> FindAllQueryFacts(const Token &token);
};


#endif //EXPERTSYSTEM_PARSER_HPP
