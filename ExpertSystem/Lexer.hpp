//
// Created by Andrew Radiuk on 2019-03-17.
//

#ifndef EXPERTSYSTEM_LEXER_HPP
#define EXPERTSYSTEM_LEXER_HPP

#include <iostream>
#include <map>
#include <regex>
#include <fstream>


enum class TokenType { // in order of decreased priority
	OpenParentheses,
	CloseParentheses,
	Not,
	And,
	Or,
	Xor,
	Implies,
	IfAndOnlyIf,
	Fact,
	InitialFact,
	Comment,
	Query
};

class Lexer {
	private:
		const std::map<TokenType, std::regex> allowedTokens_ = {
				{TokenType::OpenParentheses, std::regex(R"(^\()")},
				{TokenType::CloseParentheses, std::regex(R"(^\))")},
				{TokenType::Not, std::regex(R"(^\!)")},
				{TokenType::And, std::regex(R"(^\+)")},
				{TokenType::Or, std::regex(R"(^\|)")},
				{TokenType::Xor, std::regex(R"(^\^)")},
				{TokenType::Implies, std::regex(R"(^=>)")},
				{TokenType::IfAndOnlyIf, std::regex(R"(^<=>)")},
				{TokenType::Fact, std::regex(R"(^[A-Z])")},
				{TokenType::InitialFact, std::regex(R"(^=[A-Z]*)")},
				{TokenType::Comment, std::regex(R"(^#)")},
				{TokenType::Query, std::regex(R"(^\?[A-Z]+)")}
				};
		const std::map<TokenType, std::string> tokenSymbols_ = {
				{TokenType::OpenParentheses, "("},
				{TokenType::CloseParentheses, ")"},
				{TokenType::Not, "!"},
				{TokenType::And, "+"},
				{TokenType::Or, "|"},
				{TokenType::Xor, "^"},
				{TokenType::Implies, "=>"},
				{TokenType::IfAndOnlyIf, "<=>"}
		};

	public:
		Lexer();
		~Lexer();
		Lexer(const Lexer &obj);
	    Lexer &operator=(const Lexer &obj);
		std::string TokenToString(TokenType token) const;
		std::pair<TokenType, bool> IsTokenValid(const std::string
		&checkToken) const;

		std::vector<std::vector<TokenType>> TokeniseFile(const std::string
		&fileName) const;
};


#endif //EXPERTSYSTEM_LEXER_HPP
