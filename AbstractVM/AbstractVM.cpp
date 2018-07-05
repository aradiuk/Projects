#include "AbstractVM.hpp"

AbstractVM::AbstractVM() {

}

AbstractVM::~AbstractVM() {

}

AbstractVM::AbstractVM(const AbstractVM& obj) {

}

AbstractVM& AbstractVM::operator=(const AbstractVM &obj) {

}

void AbstractVM::start(int argc, char **argv) {
    if (argc == 1) {
        stdInput();
    } else if (argc == 2) {
        fileInput(argv[1]);
    }

    Logger(__FUNCTION__, "Started!\n");
}

void AbstractVM::stdInput() {
    Logger(__FUNCTION__, "Not supported for now.\n");
}

void AbstractVM::fileInput(std::string filename) {
    
}





const char *AbstractVM::AssemblyErrors::what() const throw()
{
        return "Assembly has some ERRORS";
}

const char *AbstractVM::UnknownInstruction::what() const throw()
{
        return "Assembly contains an UNKNOWN INSTRUCTION";
}

const char *AbstractVM::ValueOverflow::what() const throw()
{
        return "One of the values got OVERFLOWED";
}

const char *AbstractVM::ValueUnderflow::what() const throw()
{
        return "One of the values got UNDERFLOWED";
}

const char *AbstractVM::PopOnEmptyStack::what() const throw()
{
        return "POP was used on an EMPTY STACK";
}

const char *AbstractVM::DivisionByZero::what() const throw()
{
        return "Do not EVER divide by ZERO. Unless you are using a floating point value";
}

const char *AbstractVM::NoExitInstruction::what() const throw()
{
        return "Assembly has not EXIT instruction";
}

const char *AbstractVM::AssertIsNotTrue::what() const throw()
{
        return "ASSERT is not true";
}

const char *AbstractVM::LessThenTwoValues::what() const throw()
{
        return "ARITHMETIC INCTRUTION was used on less than TWO values";
}
