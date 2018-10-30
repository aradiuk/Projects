#ifndef COMPUTORV1_PARSER_HPP
#define COMPUTORV1_PARSER_HPP

#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <regex>
#include <algorithm>
#include <string>

class Parser {
private:
	const std::string equation_;
	const std::vector<std::regex> allowedEqParts_ = {
			std::regex("[-]?\\d+(\\.\\d+)?"),
			std::regex("[\\+\\-\\*]"),
			std::regex("X(\\^\\d)?")};
	std::map<int, int> lhPowerCoefficients_;
	std::map<int, int> rhPowerCoefficients_;
	bool valid_ = true;

public:
	Parser();
	Parser(const std::string &str);
	~Parser();
	Parser(const Parser &obj);
	Parser &operator=(const Parser& obj);

	void ParseEquation();
	void ParseOneHand(const std::string &str, bool isLeftHand);
	void ParseEqPart(const std::string &str, int power, bool isLeftHand);
	int FindPower(const std::string &str);
	bool ValidPart(const std::string &str);
	void MoveAllToOneSide();
	bool IsEquationValid();

};

#endif //COMPUTORV1_PARSER_HPP
