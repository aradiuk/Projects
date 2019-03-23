//
// Created by Andrew Radiuk on 2019-03-17.
//

#ifndef EXPERTSYSTEM_EXPERTSYSTEM_HPP
#define EXPERTSYSTEM_EXPERTSYSTEM_HPP

#include <iostream>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Validator.hpp"

class ExpertSystem {
    private:
        std::vector<std::vector<Token>> tokens_;
        std::map<std::string, Fact> facts_;
        std::vector<Rule> rules_;
        std::map<std::string, Fact> queryFacts_;
        std::vector<Rule> polishRules_;

	public:
		Parser parser_;
		Lexer lexer_;
		Validator validator_;

		ExpertSystem();
		~ExpertSystem();
		ExpertSystem(const ExpertSystem& obj);
		ExpertSystem &operator=(const ExpertSystem &obj);

		void StartEngine(const std::string &fileName);
		std::vector<Rule> TransformRulesToPolish(const std::vector<Rule> &rules);
		std::vector<Token> TransformOneSide(const std::vector<Token> &tokens);
		bool IsOperator(const Token &token) {return token.type_ == TokenType::And ||
		                                            token.type_ == TokenType::Or ||
		                                            token.type_ == TokenType::Xor;};
		void Evaluate(const std::vector<Rule> &polishRules);
		Fact BackwardChaining(const std::string &name);
		bool Solve(Rule &rule, const std::string &name);
		bool GetStatusOfSide(std::vector<Token> &tokens);
		Token RevertIfNegative(const Token &token);
		bool UseOperator(const Token &first, const Token &second, const Token &operatorToken);
		void UpdateTokensStatus(std::vector<Token> &tokens);
		bool FindFactStatus(const std::string &name, const std::vector<Token> &tokens, bool sideStatus, const Token &operatorToken);
		bool IsFactOnThisSide(const std::string &name, const std::vector<Token> &tokens);

};


#endif //EXPERTSYSTEM_EXPERTSYSTEM_HPP
