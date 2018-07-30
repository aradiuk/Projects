#include "AbstractVM.hpp"

AbstractVM::AbstractVM() : lineCount_(0) {

}

AbstractVM::~AbstractVM() {

}

AbstractVM::AbstractVM(const AbstractVM& obj) {

}

AbstractVM& AbstractVM::operator=(const AbstractVM &obj) {

}

void AbstractVM::Start(int argc, char **argv) {
    try {
        if (argc == 1) {
            StdInput();
        } else if (argc == 2) {
            FileInput(argv[1]);
        }
    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    OperandFactory factory;
    factory.createOperand(Int8, "hey");
    factory.createOperand(Int16, "hey");
    factory.createOperand(Int32, "hey");
    factory.createOperand(Float, "hey");
    factory.createOperand(Double, "hey");
    Logger(__FUNCTION__, "Started!\n");
}

void AbstractVM::ProcessCommands() {

}

void AbstractVM::StdInput() {
    std::string readLine;
    bool exitFound = false;

    while (std::cin) {
        IncrLineCount();
        std::getline(std::cin, readLine);
        if (readLine.empty()) {
            continue;
        }

        if (readLine == ";;") {
            exitFound = true;
            break;
        }

        if (ValidateLine(readLine)) {
//            if (ProcessCommand(readLine))
        } else {
            throw UnknownInstruction();
        }
    }

    if (!exitFound)
        throw NoExitInstruction();
}

void AbstractVM::FileInput(std::string filename) {
    std::string readLine;
    std::ifstream fileStream(filename.c_str());
    bool exitFound = false;

    Logger(__FUNCTION__);
    if (!fileStream.is_open() || fileStream.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "File is empty or there was a problem opening it.\n";
        exit(1);
    }

    while(std::getline(fileStream, readLine)) {
        IncrLineCount();
        if (readLine.empty()) {
            continue;
        }

        if (std::regex_match(readLine, std::regex("^exit[\\s\\t]*((?=;+);.*|)"))) {
            exitFound = true;
            break;
        }

        if (ValidateLine(readLine)) {
//            if (ProcessCommand(readLine))
            Logger(__FUNCTION__, "line ", std::to_string(lineCount_), " ", readLine, " is VALID.");
        } else {
            throw UnknownInstruction();
        }
    }

    if (!exitFound)
        throw NoExitInstruction();
}


bool AbstractVM::ValidateLine(std::string str) {
    for (std::vector<std::regex>::iterator it = allowedCommands_.begin(); it != allowedCommands_.end(); it++) {
        if (std::regex_match(str, *it)) {
            commands_.push_back(str);
            return true;
        }
    }
    std::cout << "Error on line " << GetLineCount() << std::endl;
    return false;
}

int AbstractVM::GetLineCount() const {
    return lineCount_;
}

void AbstractVM::IncrLineCount() {
    ++lineCount_;
}

const char *AbstractVM::AssemblyErrors::what() const throw() {
        return "Assembly has some ERRORS";
}

const char *AbstractVM::UnknownInstruction::what() const throw() {
        return "Assembly contains an UNKNOWN INSTRUCTION";
}

const char *AbstractVM::ValueOverflow::what() const throw() {
        return "One of the values got OVERFLOWED";
}

const char *AbstractVM::ValueUnderflow::what() const throw() {
        return "One of the values got UNDERFLOWED";
}

const char *AbstractVM::PopOnEmptyStack::what() const throw() {
        return "POP was used on an EMPTY STACK";
}

const char *AbstractVM::DivisionByZero::what() const throw() {
        return "Do not EVER divide by ZERO. Unless you are using a floating point value";
}

const char *AbstractVM::NoExitInstruction::what() const throw() {
        return "Assembly has not EXIT instruction";
}

const char *AbstractVM::AssertIsNotTrue::what() const throw() {
        return "ASSERT is not true";
}

const char *AbstractVM::LessThenTwoValues::what() const throw() {
        return "ARITHMETIC INCTRUTION was used on less than TWO values";
}
