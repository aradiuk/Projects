#include "AbstractVM.hpp"

AbstractVM::AbstractVM() {

}

AbstractVM::~AbstractVM() {

}

AbstractVM::AbstractVM(const AbstractVM& obj) {

}

AbstractVM& AbstractVM::operator=(const AbstractVM &obj) {

}

void AbstractVM::Start(int argc, char **argv) {
    if (argc == 1) {
        StdInput();
    } else if (argc == 2) {
        FileInput(argv[1]);
    }

    Logger(__FUNCTION__, "Started!\n");
}

void AbstractVM::StdInput() {
    Logger(__FUNCTION__, "Not supported for now.\n");
}

void AbstractVM::FileInput(std::string filename) {
    int lineCount = 0;
    std::string error = "Error was encountered on line ";
    std::string readLine;
    std::ifstream fileStream(filename.c_str());

    if (!fileStream.is_open() || fileStream.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "File is empty or there is a problem opening it.\n";    
        exit(1);
    }

    while(std::getline(fileStream, readLine)) {
        ++lineCount;
        ValidateLine(readLine, lineCount);
    }

}

void AbstractVM::ValidateLine(std::string str, int lineCount) {
    try {
        if (str == "hey")
            throw AssemblyErrors();
    
    } catch (std::out_of_range &o) {
        std::cout << o.what() << "OOR";
    } catch (std::exception &e) {
        std::cout << e.what();
    }
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
