//
// Created by aradiuk on 10/29/2018.
//

#ifndef COMPUTORV1_COMPUTORV1_HPP
#define COMPUTORV1_COMPUTORV1_HPP

#include <iostream>
#include <map>
#include <regex>
#include <cctype>

class ComputorV1 {
private:
	const std::string equation_;
	bool isLeftHand = true;
	std::string entity;
	std::string xPart;
	std::string reducedEq_;
	std::string solution_;
	const std::vector<std::regex> allowedEntities_ = {
			std::regex("[-+]*\\d+(\\.\\d+)?"),
			std::regex("[\\+\\-\\*\\/]"),
			std::regex("[-+]?X(\\^\\d+)?")};
	std::map<int, int> lhPowerCoefficients_;
	std::map<int, int> rhPowerCoefficients_;
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
	void processEquation();


};
#endif //COMPUTORV1_COMPUTORV1_HPP
