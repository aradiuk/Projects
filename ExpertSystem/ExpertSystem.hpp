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
        std::map<std::string, boost::optional<bool>> facts_;
        std::vector<Rule> rules_;
        std::map<std::string, boost::optional<bool>> queryFacts_;
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
		boost::optional<bool> BackwardChaining(const std::string &name);
		bool Solve(Rule &rule);
		std::pair<std::string, boost::optional<bool>> &FindFact(const Token &token);
		bool CheckNegative(const Token &token, boost::optional<bool> status);
		bool UseOperator(bool first, bool second, TokenType operatorType);
		bool IsFactInSequence(const std::string &name, const std::vector<Token> &sequence);
		void UpdateTokensStatus(Rule &rule);
		bool IsSequenceSimple(const std::vector<Token> &sequence);
};


#endif //EXPERTSYSTEM_EXPERTSYSTEM_HPP
