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
	Query
};

struct Token {
    Token()
        : type_(TokenType::Not)
        , value_("")
    {}
    Token(TokenType type, const std::string &value)
        : type_(type)
        , value_(value)
    {}
    Token(const Token &token)
        : type_(token.type_)
        , value_(token.value_)
    {}

    TokenType type_;
    std::string value_;
};

std::ostream &operator<<(std::ostream &os, TokenType token);

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
		std::pair<Token, bool> IsTokenValid(const std::string &checkToken) const;

		std::vector<std::vector<Token>> TokeniseFile(const std::string &fileName);
		std::vector<Token> TokeniseLine(const std::string &line);

};


#endif //EXPERTSYSTEM_LEXER_HPP
