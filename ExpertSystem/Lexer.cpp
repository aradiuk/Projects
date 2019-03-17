//
// Created by Andrew Radiuk on 2019-03-17.
//

#include "Lexer.hpp"

Lexer::Lexer()
{}

Lexer::~Lexer()
{}

Lexer::Lexer(const Lexer &obj)
{}

Lexer& Lexer::operator=(const Lexer &obj)
{
	return *this;
}

std::vector<std::vector<TokenType>> Lexer::TokeniseFile(const std::string
&fileName) const
{
	std::ifstream ifs(fileName.c_str());
	if (!ifs.good()) {
		throw "Couldn't open your file. Try another one.";
	}

	std::vector<std::vector<TokenType>> tokens;
	std::string line;
	while (getline(ifs, line)) {
		std::cout << line << std::endl;
	}

	return tokens;
}

std::string Lexer::TokenToString(TokenType token) const
{
	std::string result;

	const auto it = tokenSymbols_.find(token);
	if (it != tokenSymbols_.end()) {
		result = it->second;
	}
	return result;
}

std::pair<TokenType, bool> Lexer::IsTokenValid(const std::string &checkToken)
const {
	for (const auto &it : allowedTokens_) {
		if (std::regex_match(checkToken, it.second)) {
			return std::make_pair(it.first, true);
		}
	}
	return std::make_pair(TokenType::Not, false);
}