#include "ComputorV1.hpp"

ComputorV1::ComputorV1() : equation_(""), parser_(Parser())
{}

ComputorV1::ComputorV1(const std::string &eq) : equation_(eq), parser_(Parser(eq))
{}

ComputorV1::ComputorV1(const ComputorV1 &obj)
{}

ComputorV1& ComputorV1::operator=(const ComputorV1 &obj)
{}

ComputorV1::~ComputorV1()
{}

void ComputorV1::processEquation()
{
	if (!parser_.IsEquationValid()) {
		std::cout << "Sorry, your equation is not valid. Try again.\n";
		return;
	}

}




