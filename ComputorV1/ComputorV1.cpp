#include "ComputorV1.hpp"

ComputorV1::ComputorV1() : equation_("")
{}

ComputorV1::ComputorV1(const std::string &eq) : equation_(eq)
{}

ComputorV1::ComputorV1(const ComputorV1 &obj)
{}

ComputorV1& ComputorV1::operator=(const ComputorV1 &obj)
{}

ComputorV1::~ComputorV1()
{}

bool ComputorV1::IsEquationValid()
{
	if (equation_.empty() || equation_.find('=') == std::string::npos) {
		return false;
	}

	std::string eq = equation_ + "\n";
	for (const auto &it : eq) {
		if (!FormEntity(it)) {
			return false;
		}
	}
	return true;
}

bool ComputorV1::FormEntity(const char &symb)
{
	static bool action = false;
	static bool isPositive = true;
	static bool isLeftHand = true;
//	std::cout << __FUNCTION__ << " " << symb << std::endl;
	if (symb == ' ') {
		return true;
	}

	if (symb == '=') {
		action = true;
		xPart += " " + entity;
		if (IsEntityValid()) {
			entity.clear();
			ParseXPart(isPositive, isLeftHand);
			if (isLeftHand) {
				isLeftHand = false;
			}
			return true;
		} else {
			return false;
		}

	}

	if (symb == '*' || symb == '/') {
		action = true;
		xPart += " " + entity + " " + symb;
		bool result = IsEntityValid();
		entity.clear();
		return result;
	}

	if (symb == '+' || symb == '-' || symb == '\n') {
		if (action) {
			entity += symb;
			return true;
		}
		action = true;
		xPart += " " + entity;
		bool result = IsEntityValid();
		if (result) {
			ParseXPart(isPositive, isLeftHand);
			entity.clear();
			entity += symb;
		}
		isPositive = symb == '+';
		return result;
	}

	entity += symb;
	action = false;

	return true;
}

void ComputorV1::ParseXPart(bool isPositive, bool isLeftHand)
{
	std::cout << __FUNCTION__ << ": " << xPart << std::endl;
	int partPower = 0;
	double coef = 1;
	bool isMult = true;

	std::stringstream ss(xPart);
	std::string str;
	while (ss >> str) {
		std::cout << "before: " << str << std::endl;
		if (str.find('X') != std::string::npos) {
			int newPower = DeterminePower(str);
			partPower = newPower > partPower ? newPower : partPower;
		} else if (str == "*") {
			isMult = true;
		} else if (str == "/") {
			isMult = false;
		} else {
			if (!isMult) {
				coef /= std::stoi(RemoveUnneededSigns(str));
			}
			else {
				coef *= std::stoi(RemoveUnneededSigns(str));
			}
		}
		std::cout << "Ppower: " << partPower << std::endl;
		std::cout << "Ccoef: " << coef << std::endl;
	}

	if (!isLeftHand) {
		coef *= -1;
	}
	powerCoefficients_[partPower] += coef;
	std::cout << "power: " << partPower << ", coef: " << coef << std::endl;
	xPart.clear();
}

bool ComputorV1::IsEntityValid()
{
	if (entity.empty()) {
		return false;
	}

	std::cout << __FUNCTION__ << ": " << entity << std::endl;
	for (const auto &it : allowedEntities_) {
		if (std::regex_match(entity, it)) {
			return true;
		}
	}
	return false;
}

void ComputorV1::processEquation()
{
	if (!IsEquationValid()) {
		std::cout << "Sorry, your equation is not valid. Try again.\n";
		return;
	}
	for (const auto &it : powerCoefficients_)
		std::cout << "power: " << it.first << ", coef: " << it.second << std::endl;
}

std::string ComputorV1::RemoveUnneededSigns(const std::string &str)
{
	int minuses = 0;
	size_t pos = 0;

	for (const auto &it : str) {
		if (it == '-') {
			++minuses;
		} else if (isdigit(it)) {
			pos = str.find(it);
			break;
		}
	}
	std::string result;
	if (minuses % 2 == 0) {
		result = str.substr(pos);
	} else {
		result = "-" + str.substr(pos);
	}
	std::cout << __FUNCTION__ << ": " << result << std::endl;
	return result;
}

int ComputorV1::DeterminePower(const std::string &str)
{
	size_t pos = str.find('^');
	if (pos != std::string::npos) {
		return std::stoi(str.substr(pos + 1));
	} else {
		return 1;
	}
}




