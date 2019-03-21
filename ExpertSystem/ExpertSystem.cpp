//
// Created by Andrew Radiuk on 2019-03-17.
//

#include "ExpertSystem.hpp"

ExpertSystem::ExpertSystem()
{}

ExpertSystem::~ExpertSystem()
{}

ExpertSystem::ExpertSystem(const ExpertSystem &obj)
{}

ExpertSystem& ExpertSystem::operator=(const ExpertSystem &obj)
{
	return *this;
}

void PrintAllTokens(const std::vector<std::vector<Token>> &tokens) {
    for (const auto &it : tokens) {
        for (const auto &itt : it) {
            std::cout << itt.type_ << ": " << itt.value_ << ", ";
        }
        std::cout << std::endl;
    }
}


void ExpertSystem::StartEngine(const std::string &fileName)
{
    tokens_ = lexer_.TokeniseFile(fileName);
    parser_.ParseTokens(tokens_);
    validator_.ValidateTokens(tokens_);
    validator_.ValidateRules(parser_.GetRules());

    std::vector<Rule> polishRules = TransformRulesToPolish(parser_.GetRules());
    PrintAllTokens(tokens_);
}

std::vector<Rule> ExpertSystem::TransformRulesToPolish(const std::vector<Rule> &rules)
{
    std::vector<Rule> polishRules;

    for (const auto &rule : rules) {
        std::cout << "BEFORE" << std::endl;
        for (auto tok : rule.lhs_ ) {
            std::cout << tok.value_ << " ";
        }
        std::cout << rule.operator_.value_ << " ";
        for (auto tok : rule.rhs_ ) {
            std::cout << tok.value_ << " ";
        }
        std::cout << std::endl;
        Rule newRule;
        newRule.lhs_ = TransformOneSide(rule.lhs_);
        newRule.rhs_ = TransformOneSide(rule.rhs_);
        newRule.operator_ = rule.operator_;
        polishRules.push_back(newRule);
        std::cout << "AFTER" << std::endl;
          for (auto tok : newRule.lhs_ ) {
              std::cout << tok.value_ << " ";
          }
          std::cout << newRule.operator_.value_ << " ";
          for (auto tok : newRule.rhs_ ) {
              std::cout << tok.value_ << " ";
          }
          std::cout << std::endl;
    }

    return polishRules;
}

std::vector<Token> ExpertSystem::TransformOneSide(const std::vector<Token> &tokens)
{
    std::vector<Token> operators;
    std::vector<Token> stack;
    bool haveNot = false;

    for (const auto &token : tokens) {
        if (token.type_ == TokenType::CloseParenthesis) {
            std::cout << "Close" << std::endl;
            for (auto it : operators)
                std::cout << "op: " << it.value_ << std::endl;
            for (auto it : stack)
                std::cout << "st: " << it.value_ << std::endl;
            if (operators.empty()) {
                throw "Nothing before ')'";
            }
            if (operators.back().type_ == TokenType::OpenParenthesis) {
                throw "Nothing between parentheses.";
            }
            while (!operators.empty() && operators.back().type_ != TokenType::OpenParenthesis) {
                stack.push_back(operators.back());
                operators.pop_back();
            }
            operators.pop_back();
        } else if (IsOperator(token)) {
            std::cout << "Operator: " << token.value_ << std::endl;
            for (auto it : operators)
                std::cout << "op: " << it.value_ << std::endl;
            for (auto it : stack)
                std::cout << "st: " << it.value_ << std::endl;
            while (!operators.empty() && operators.back().type_ < token.type_ && operators.back().type_ != TokenType::OpenParenthesis) {
                stack.push_back(operators.back());
                operators.pop_back();
            }
            operators.push_back(token);
        } else if (token.type_ == TokenType::Not) {
            std::cout << "Not" << std::endl;
            for (auto it : operators)
                std::cout << "op: " << it.value_ << std::endl;
            for (auto it : stack)
                std::cout << "st: " << it.value_ << std::endl;
            haveNot = true;
        } else {
            std::cout << "Else: " << token.value_ << std::endl;
            for (auto it : operators)
                std::cout << "op: " << it.value_ << std::endl;
            for (auto it : stack)
                std::cout << "st: " << it.value_ << std::endl;
            if (haveNot && token.type_ != TokenType::Fact) {
                throw "Somehow missed '!' before not a fact";
            }
            if (token.type_ == TokenType::OpenParenthesis) {
                operators.push_back(token);
            } else if (token.type_ == TokenType::Fact) {
                Token newToken = token;
                newToken.isNegative_ = haveNot;
                stack.push_back(token);
                haveNot = false;
            } else {
                throw "Should never happen. Unexpected token in transform.";
            }
        }
    }
    while (!operators.empty()) {
        stack.push_back(operators.back());
        operators.pop_back();
    }

    return stack;
}
