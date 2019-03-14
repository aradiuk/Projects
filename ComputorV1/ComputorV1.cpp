#include "ComputorV1.hpp"

#define LOG

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
#ifdef LOG
    std::cout << __FUNCTION__ << std::endl;
#endif

	if (equation_.empty() || equation_.find('=') == std::string::npos) {
		return false;
	}

	std::string eq = equation_ + "\n";
	for (const auto &it : eq) {
		if (!FormEntity(it)) {
		    std::cout << "Entity: " << entity << std::endl;
			return false;
		}
	}
	return true;
}

bool ComputorV1::FormEntity(const char &symb)
{
#ifdef LOG
    std::cout << __FUNCTION__ << "| " << symb << " |" << std::endl;
#endif

	static bool action = true;
	static bool isLeftHand = true;
	static int equals = 0;

	if (symb == ' ') {
		return true;
	}

	if (symb == '=') {
	    if (equals) {
	        throw "Too many '=' symbols. Do you even know how equations look?";
	    }
	    ++equals;
		action = true;
		xPart += " " + entity;
		if (IsEntityValid(entity)) {
			entity.clear();
            ParseXPart(isLeftHand);
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
		bool result = IsEntityValid(entity);
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
		bool result = IsEntityValid(entity);
		if (result) {
			ParseXPart(isLeftHand);
			entity.clear();
			entity += symb;
		}
		return result;
	}

	entity += symb;
	action = false;

#ifdef LOG
    std::cout << __FUNCTION__ << " " << entity << std::endl;
#endif
	return true;
}

void ComputorV1::ParseXPart(bool isLeftHand)
{
#ifdef LOG
	std::cout << __FUNCTION__ << xPart << ": left hand?" << isLeftHand << std::endl;
#endif

	if (!IsEntityValid(xPart)) {
	    throw "xPart is invalid.";
	}
    int power = 0;
    double coef = 1;
    bool isMult = true;

    std::stringstream ss(xPart);
    std::string str;
    while (ss >> str) {
        if (str.find('X') != std::string::npos) {
            power = DeterminePower(str);
            if (str.find('-') != std::string::npos) {
                coef *= -1;
            }
        } else if (str != "*") {
            if (IsStrNumber(str)) {
                std::cout << str << std::endl;
                coef = std::stod(str);
            } else {
                throw "Your equation is invalid. Possibly because of: " + str;
            }
        }
    }
    std::cout << "power: " << power << ", coef: " << coef << std::endl;

    if (!isLeftHand) {
        coef *= -1;
    }
    powerCoefficients_[power] += coef;
    xPart.clear();
#ifdef LOG
    std::cout << "power: " << power << ", coef: " << coef << std::endl;
#endif
}

bool ComputorV1::IsEntityValid(const std::string &ent)
{
#ifdef LOG
    std::cout << __FUNCTION__ << ": before trimming |" << ent << "|" << std::endl;
#endif

    std::stringstream ss(ent);
    std::string ssStr;
    std::string str;
    while (ss >> ssStr) {
        str += ssStr;
    }

	if (str.empty()) {
		return true;
	}

	for (const auto &it : allowedEntities_) {
		if (std::regex_match(str, it)) {
#ifdef LOG
		    std::cout << __FUNCTION__ << ": " << str << " is valid." << std::endl;
#endif
			return true;
		}
	}
#ifdef LOG
    std::cout << __FUNCTION__ << ": " << str << " is NOT valid." << std::endl;
#endif
	return false;
}

void ComputorV1::PrintPolynomialDegree()
{
    std::stringstream degree;

    degree << "Polynomial degree: " << powerCoefficients_.rbegin()->first;
    std::cout << degree.str() << std::endl;
}

void ComputorV1::PrintSimplifiedEquation()
{
    std::stringstream reduced;

    reduced << "Reduced from: ";
    for (const auto &it : powerCoefficients_) {
        if (it.first == 0) {
            reduced << it.second << " * X^" << it.first << " ";
        } else {
            if (it.second < 0) {
                reduced << "- " << -it.second << " * X^" << it.first << " ";
            } else {
                reduced << "+ " << it.second << " * X^" << it.first << " ";
            }
        }
    }
    reduced << "= 0";

    std::cout << reduced.str() << std::endl;
}

double ComputorV1::CalculateDiscriminant()
{
    std::stringstream discrInfo;

    double a = powerCoefficients_[2];
    double b = powerCoefficients_[1];
    double c = powerCoefficients_[0];
    double discr = Pow(b, 2) - 4 * a * c;
    if (discr < 0) {
        discrInfo << "Discriminant is negative.";
        std::cout << discrInfo.str() << std::endl;
        return 0;
    } else if (discr == 0) {
        discrInfo << "Discriminant is equal 0.";
    } else {
        discrInfo << "Discriminant is positive.";
    }

    std::cout << discrInfo.str() << std::endl;

    return discr;
}

ComputorV1::SolutionResults ComputorV1::FindSolution(double discr)
{
    double a = powerCoefficients_[2];
    double b = powerCoefficients_[1];
    double c = powerCoefficients_[0];
    double denominator = 2 * a;

    SolutionResults result;

    if (a == 0) {
        if (b == 0) {
            result.infinite_ = true;
            return result;
        }
        result.first_ = std::make_pair(true, -c / b);
        if (result.first_.second == -0)
            result.first_.second = 0;
        return result;
    } else if (discr == 0) {
        result.first_ = std::make_pair(true, -b / denominator);
        return result;
    } else {
        result.first_ = std::make_pair(true, (-b + Sqrt(discr)) / denominator);
        result.second_ = std::make_pair(true, (-b - Sqrt(discr)) / denominator);
        return result;
    }
}

void ComputorV1::ProcessEquation()
{
#ifdef LOG
    std::cout << __FUNCTION__ << ": " << equation_ << std::endl;
#endif
	if (!IsEquationValid()) {
		std::cout << "Sorry, your equation is not valid. Try again.\n";
		return;
	}
#ifdef LOG
	for (const auto &it : powerCoefficients_)
		std::cout << "MAP: power: " << it.first << ", coef: " << it.second << std::endl;
#endif
	PrintSimplifiedEquation();
	PrintPolynomialDegree();

	if (powerCoefficients_.rbegin()->first > 2) {
	    std::cout << "The polynomial degree is greater than 2. Take it easy!" << std::endl;
	    return;
	}

	double discr = CalculateDiscriminant();
	SolutionResults result = FindSolution(discr);
    if (result.infinite_) {
        std::cout << "Infinite number of solutions" << std::endl;
    } else {
        std::cout << "Solution: ";
        if (result.first_.first) {
            std::cout << result.first_.second;
        }
        if (result.second_.first) {
	        std::cout << ", " << result.second_.second;
	    }
        std::cout << std::endl;
    }
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

bool ComputorV1::IsStrNumber(const std::string &strStart) const
{
    std::string str {strStart};

    if (str.front() == '-' || str.front() == '+')
        str = str.substr(1);

    for (const auto it : str) {
        if (!std::isdigit(it) && it != '.') {
            return false;
        }
    }
    return true;
}
