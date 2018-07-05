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
        return "Assembly has some errors";
}

const char *AbstractVM::UnknownInstruction::what() const throw()
{
        return "Assembly has some errors";
}

const char *AbstractVM::ValueOverflow::what() const throw()
{
        return "Assembly has some errors";
}

const char *AbstractVM::ValueUnderflow::what() const throw()
{
        return "Assembly has some errors";
}

const char *AbstractVM::PopOnEmptyStack::what() const throw()
{
        return "Assembly has some errors";
}

const char *AbstractVM::DivisionByZero::what() const throw()
{
        return "Assembly has some errors";
}

const char *AbstractVM::NoExitInstruction::what() const throw()
{
        return "Assembly has some errors";
}

const char *AbstractVM::AssertIsNotTrue::what() const throw()
{
        return "Assembly has some errors";
}

const char *AbstractVM::LessThenTwoValues::what() const throw()
{
        return "Assembly has some errors";
}
