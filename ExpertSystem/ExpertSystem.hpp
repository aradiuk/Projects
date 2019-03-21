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
};


#endif //EXPERTSYSTEM_EXPERTSYSTEM_HPP
