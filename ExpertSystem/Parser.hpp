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
        : operand_(token)
        , evaluated_(eval)
    {}

    std::vector<Token> lhs_;
    std::vector<Token> rhs_;
    Token operand_;
    bool evaluated_;
};

class Parser {
    private:
        std::map<std::string, bool> facts_;
        std::vector<Rule> rules_;
        Token query_;

    public:
        Parser();
        ~Parser();
        Parser(const Parser &obj);
        Parser &operator=(const Parser &obj);
        std::map<std::string, bool> GetFacts() const {return facts_;};
        std::vector<Rule> GetRules() const {return rules_;};

        void ParseTokens(const std::vector<std::vector<Token>> &tokens);
        std::map<std::string, bool> FindAllFacts(const std::vector<std::vector<Token>> &tokens);
        std::vector<Rule> FindAllRules(const std::vector<std::vector<Token>> &tokens);
};


#endif //EXPERTSYSTEM_PARSER_HPP
