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

    if (argc == 1) {
        StdInput();
    } else if (argc == 2) {
        FileInput(argv[1]);
    }

    Logger(__FUNCTION__, "Started!\n");
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

        try {
            ValidateLine(readLine);
        } catch (const std::exception &e) {
            std::cout << "line " << GetLineCount() << ": " << e.what() << std::endl;
        }
    }

    try {
        if (!exitFound) {
            throw NoExitInstruction();
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
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

        try {
            ValidateLine(readLine);
        } catch (const std::exception &e) {
            std::cout << "line " << GetLineCount() << ": " << e.what() << std::endl;
        }
    }

    try {
        if (!exitFound) {
            throw NoExitInstruction();
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void AbstractVM::ValidateLine(std::string str) {
    for (std::vector<std::regex>::iterator it = allowedCommands_.begin(); it != allowedCommands_.end(); it++) {
        if (std::regex_match(str, *it)) {
            commands_.push_back(str);
            ProcessCommand(str, it - allowedCommands_.begin());
            return ;
        }
    }
    throw UnknownInstruction();
}

void AbstractVM::ProcessCommand(std::string str, int index) {
    std::cout << str << std::endl;
    static void (AbstractVM::*commands[10])(std::string const & str) = {
        &AbstractVM::push,
        &AbstractVM::pop,
        &AbstractVM::dump,
        &AbstractVM::assert,
        &AbstractVM::add,
        &AbstractVM::sub,
        &AbstractVM::mul,
        &AbstractVM::div,
        &AbstractVM::mod,
        &AbstractVM::print,
    };

    (this->*commands[index])(str);
}

void AbstractVM::push(std::string const & str) {
    std::cout << "push command" << std::endl;
}

void AbstractVM::pop(std::string const & str) {
    std::cout << "pop command" << std::endl;
}

void AbstractVM::dump(std::string const & str) {
    std::cout << "dump command" << std::endl;
}

void AbstractVM::assert(std::string const & str) {
    std::cout << "assert command" << std::endl;
}

void AbstractVM::add(std::string const & str) {
    std::cout << "add command" << std::endl;
}

void AbstractVM::sub(std::string const & str) {
    std::cout << "sub command" << std::endl;
}

void AbstractVM::mul(std::string const & str) {
    std::cout << "mul command" << std::endl;
}

void AbstractVM::div(std::string const & str) {
    std::cout << "div command" << std::endl;
}

void AbstractVM::mod(std::string const & str) {
    std::cout << "mod command" << std::endl;
}

void AbstractVM::print(std::string const & str) {
    std::cout << "print command" << std::endl;
}










int AbstractVM::GetLineCount() const {
    return lineCount_;
}

void AbstractVM::IncrLineCount() {
    ++lineCount_;
}

const char *AbstractVM::LexicalOrSyntactical::what() const throw() {
        return "Assembly contains LEXICAL or SYNTACTICAL errors";
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
        return "Assembly has no EXIT instruction";
}

const char *AbstractVM::AssertIsNotTrue::what() const throw() {
        return "ASSERT is not true";
}

const char *AbstractVM::LessThenTwoValues::what() const throw() {
        return "ARITHMETIC INCTRUTION was used on less than TWO values";
}
