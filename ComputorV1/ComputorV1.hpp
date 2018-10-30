//
// Created by aradiuk on 10/29/2018.
//

#ifndef COMPUTORV1_COMPUTORV1_HPP
#define COMPUTORV1_COMPUTORV1_HPP

#include "Parser.hpp"

class ComputorV1 {
private:
	const std::string equation_;
	std::string reducedEq_;
	int polinomialDegree_;
	std::string solution_;
	Parser parser_;


public:
	ComputorV1();
	ComputorV1(const std::string &eq);
	~ComputorV1();
	ComputorV1(const ComputorV1 &obj);
	ComputorV1& operator=(const ComputorV1 &obj);

	void processEquation();


};
#endif //COMPUTORV1_COMPUTORV1_HPP
