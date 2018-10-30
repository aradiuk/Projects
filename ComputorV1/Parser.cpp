#include "Parser.hpp"

Parser::Parser() : equation_("")
{}

Parser::Parser(const std::string &str) : equation_(str)
{
	ParseEquation();
}

Parser::Parser(const Parser &obj)
{}

Parser& Parser::operator=(const Parser &obj)
{}

Parser::~Parser()
{}

void Parser::MoveAllToOneSide()
{
	int lhCoef = lhPowerCoefficients_.rbegin()->second;
	int rhCoef = rhPowerCoefficients_.rbegin()->second;

	if (lhCoef > rhCoef) {
		for (const auto it : rhPowerCoefficients_) {
			if (lhPowerCoefficients_.find(it.first) != lhPowerCoefficients_.end()) {
				lhPowerCoefficients_[it.first] -= it.second;
			} else {
				lhPowerCoefficients_[it.first] = -it.second;
			}
		}
	} else if (rhCoef > lhCoef) {
		for (const auto it : lhPowerCoefficients_) {
			if (rhPowerCoefficients_.find(it.first) != rhPowerCoefficients_.end()) {
				rhPowerCoefficients_[it.first] -= it.second;
			} else {
				rhPowerCoefficients_[it.first] = -it.second;
			}
		}
	} else {
		std::cout << "Sides are equal.\n";
	}
}

void Parser::ParseEquation()
{
	std::size_t equalitySign = equation_.find("=");
	if (equalitySign == std::string::npos) {
		std::cout << "Equation is not full.\n";
		return;
	}

	std::string leftHand = equation_.substr(0, equation_.find("="));
	std::string rightHand = equation_.substr(equation_.find("=") + 1);

	ParseOneHand(leftHand, true);
	ParseOneHand(rightHand, false);
	MoveAllToOneSide();
	PrintSimplified();

	std::cout << std::endl;
	std::cout << "Left hand: ";
	for (const auto it : lhPowerCoefficients_) {
		std::cout << it.first << " : " << it.second;
		std::cout << std::endl;

	}
	std::cout << std::endl;
	std::cout << "Right hand: ";
	for (const auto it : rhPowerCoefficients_) {
		std::cout << it.first << " : " << it.second;
		std::cout << std::endl;
	}
}

void Parser::ParseOneHand(const std::string &str, bool isLeftHand)
{
	std::stringstream ss(str);
	std::string eqPart;
	std::string addend;
	int power = 0;
	while (ss >> addend) {
		std::cout << "string: " << addend << std::endl;
		if (!ValidPart(addend)) {
			std::cout << "Equation is invalid. Try again.\n";
			return;
		}
		if (addend != "+" && addend != "-") {
			if (addend.find("X") != std::string::npos) {
				power = FindPower(addend);
				if (eqPart.size() >= 1) {
					eqPart.pop_back();
				}
			} else {
				eqPart += addend;
			}
		} else {
			ParseEqPart(eqPart, power, isLeftHand);
			eqPart = addend == "-" ? "-" : "";
			power = 0;
		}
	}
	ParseEqPart(eqPart, power, isLeftHand);
}

void Parser::ParseEqPart(const std::string &str, int power, bool isLeftHand)
{
	std::stringstream ss(str);
	std::string number;
	std::vector<double> numbers;

	while (std::getline(ss, number, '*')) {
		numbers.push_back(std::stof(number));
	}

	int result = 1;
	for (const auto it : numbers) {
		result *= it;
	}
	if (isLeftHand) {
		lhPowerCoefficients_[power] += result;
	} else {
		rhPowerCoefficients_[power] += result;
	}
}

int Parser::FindPower(const std::string &str)
{
	const auto it = str.find("^");
	if (it != std::string::npos) {
		return std::stoi(str.substr(it + 1));
	} else {
		return 1;
	}
}

bool Parser::ValidPart(const std::string &str)
{
	for (const auto it : allowedEqParts_) {
		if (std::regex_match(str, it)) {
			return true;
		}
	}
	return false;
}

bool Parser::IsEquationValid()
{
	return valid_;
}
