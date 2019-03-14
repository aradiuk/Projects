//
// Created by aradiuk on 10/29/2018.
//

#ifndef COMPUTORV1_COMPUTORV1_HPP
#define COMPUTORV1_COMPUTORV1_HPP

#include <iostream>
#include <map>
#include <regex>
#include <cctype>

#include "math_functions.hpp"

class ComputorV1 {
private:
	const std::string equation_;
	std::string entity;
	std::string xPart;
	std::string reducedEq_;
	std::string solution_;
	const std::vector<std::regex> allowedEntities_ = {
			std::regex("\\s*[-+]*\\d+(\\.\\d+)?\\s*"),
			std::regex("\\s*[\\+\\-\\*\\/]\\s*"),
			std::regex("\\s*[-+]?X(\\^\\d+)?\\s*"),
			std::regex("\\s*[-+]*\\d+(\\.\\d+)?\\*X(\\^\\d+)?\\s*")};
	std::map<int, double> powerCoefficients_;
	bool valid_ = true;

public:
    struct SolutionResults {
        bool infinite_;
        std::pair<bool, double> first_;
        std::pair<bool, double> second_;

        SolutionResults()
            : infinite_(false)
            , first_(std::make_pair(false, 0))
            , second_(std::make_pair(false, 0))
        {}
    };

	ComputorV1();
	ComputorV1(const std::string &eq);
	~ComputorV1();
	ComputorV1(const ComputorV1 &obj);
	ComputorV1& operator=(const ComputorV1 &obj);
	bool IsEquationValid();
	bool FormEntity(const char &symb);
	bool IsEntityValid(const std::string &ent);
	bool IsStrNumber(const std::string &str) const;
	void ParseXPart(bool isPositive, bool isLeftHand);
	int  DeterminePower(const std::string &str);
	std::string RemoveUnneededSigns(const std::string &str);
	void ProcessEquation();
	void PrintSimplifiedEquation();
	void PrintPolynomialDegree();
	double CalculateDiscriminant();
	SolutionResults FindSolution(double discr);

};
#endif //COMPUTORV1_COMPUTORV1_HPP
