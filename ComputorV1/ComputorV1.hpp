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
			std::regex("[-+]*\\d+(\\.\\d+)?"),
			std::regex("[\\+\\-\\*\\/]"),
			std::regex("[-+]*X(\\^\\d+)?")};
	std::map<int, double> powerCoefficients_;
	bool valid_ = true;


public:
	ComputorV1();
	ComputorV1(const std::string &eq);
	~ComputorV1();
	ComputorV1(const ComputorV1 &obj);
	ComputorV1& operator=(const ComputorV1 &obj);
	bool IsEquationValid();
	bool FormEntity(const char &symb);
	bool IsEntityValid();
	void ParseXPart(bool isPositive, bool isLeftHand);
	int  DeterminePower(const std::string &str);
	std::string RemoveUnneededSigns(const std::string &str);
	void ProcessEquation();
	void PrintSimplifiedEquation();
	void PrintPolynomialDegree();
	double CalculateDiscriminant();
	std::pair<double, double> FindSolution(double discr);

};
#endif //COMPUTORV1_COMPUTORV1_HPP
