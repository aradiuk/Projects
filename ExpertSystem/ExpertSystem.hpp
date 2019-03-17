//
// Created by Andrew Radiuk on 2019-03-17.
//

#ifndef EXPERTSYSTEM_EXPERTSYSTEM_HPP
#define EXPERTSYSTEM_EXPERTSYSTEM_HPP

#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"

class ExpertSystem {
	private:
		std::vector<TokenType> tokens_;

	public:
		Parser parser_;
		Lexer lexer_;

		ExpertSystem();
		~ExpertSystem();
		ExpertSystem(const ExpertSystem& obj);
		ExpertSystem &operator=(const ExpertSystem &obj);

		void Evaluate();
};


#endif //EXPERTSYSTEM_EXPERTSYSTEM_HPP
