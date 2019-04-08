//
// Created by Andrew Radiuk on 2019-03-17.
//

//#define LOG

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

std::vector<std::vector<Token>> Lexer::TokeniseFile(const std::string &fileName)
{
#ifdef LOG
    std::cout << __FUNCTION__ << ": " << fileName << std::endl;
#endif

    std::ifstream ifs(fileName.c_str());
    if (!ifs.good()) {
        throw "Couldn't open file. Try another one.";
    }

    std::vector<std::vector<Token>> tokens;
    std::string line;
    while (getline(ifs, line)) {
        if (line.front() == '#' || line.empty()) {
            continue;
        }
        const auto lineTokens = TokeniseLine(line);
        if (!lineTokens.empty()) {
            tokens.push_back(lineTokens);
        }
    }

    return tokens;
}

std::vector<Token> Lexer::TokeniseLine(const std::string &line)
{
#ifdef LOG
    std::cout << __FUNCTION__ << ": " << line << std::endl;
#endif

    std::vector<Token> tokens;
    std::stringstream ss(line);
    std::string tokenLine;

    while (ss >> tokenLine) {
        if (tokenLine.front() == '#') {
            break;
        }

        const auto checkToken = IsTokenValid(tokenLine);
        if (checkToken.second) {
            tokens.push_back(checkToken.first);
        } else {
            std::string tokenStr;
            for (const auto &token : tokenLine) {
                tokenStr += token;
                const auto checkToken = IsTokenValid(tokenStr);
                if (checkToken.second) {
                    tokens.push_back(checkToken.first);
                    tokenStr.clear();
                }
            }
            if (!tokenStr.empty()) {
                throw "Invalid token: " + tokenLine;
            }
        }
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

#ifdef LOG
    std::cout << __FUNCTION__ << ": " << result << std::endl;
#endif
	return result;
}

std::pair<Token, bool> Lexer::IsTokenValid(const std::string &checkToken) const {
#ifdef LOG
    std::cout << __FUNCTION__ << ": " << checkToken << std::endl;
#endif

	for (const auto &it : allowedTokens_) {
		if (std::regex_match(checkToken, it.second)) {
#ifdef LOG
    std::cout << __FUNCTION__ << " VALID: " << checkToken << std::endl;
#endif
			return std::make_pair(Token(it.first, checkToken), true);
		}
	}
#ifdef LOG
    std::cout << __FUNCTION__ << " NOT valid: " << checkToken << std::endl;
#endif
	return std::make_pair(Token(TokenType::Invalid, ""), false);
}

std::ostream &operator<<(std::ostream &os, TokenType token) {
    switch (token) {
        case TokenType::OpenParenthesis:
            os << "(";
            break;
        case TokenType::CloseParenthesis:
            os << ")";
            break;
        case TokenType::Not:
            os << "!";
            break;
        case TokenType::And:
            os << "+";
            break;
        case TokenType::Or:
            os << "|";
            break;
        case TokenType::Xor:
            os << "^";
            break;
        case TokenType::Implies:
            os << "=>";
            break;
        case TokenType::IfAndOnlyIf:
            os << "<=>";
            break;
        case TokenType::Fact:
            os << "Fact";
            break;
        case TokenType::InitialFact:
            os << "InitFact";
            break;
        case TokenType::Query:
            os << "Query";
            break;
        case TokenType::Invalid:
            os << "Invalid";
            break;
    }

    return os;
}
