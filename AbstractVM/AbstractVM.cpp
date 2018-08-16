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
            throw Exceptions::NoExitInstruction();
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
            throw Exceptions::NoExitInstruction();
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void AbstractVM::ValidateLine(std::string str) {
    for (std::vector<std::regex>::iterator it = allowedCommands_.begin(); it != allowedCommands_.end(); it++) {
        if (std::regex_match(str, *it)) {
            if ((it - allowedCommands_.begin()) == 10)
                return ;
            commands_.push_back(str);
            ProcessCommand(str, it - allowedCommands_.begin());
            return ;
        }
    }
    throw Exceptions::UnknownInstruction();
}

void AbstractVM::ProcessCommand(std::string str, int index) {
    static void (AbstractVM::*commands[10])(std::string const & str) = {
        &AbstractVM::Push,
        &AbstractVM::Pop,
        &AbstractVM::Dump,
        &AbstractVM::Assert,
        &AbstractVM::Add,
        &AbstractVM::Sub,
        &AbstractVM::Mul,
        &AbstractVM::Div,
        &AbstractVM::Mod,
        &AbstractVM::Print,
    };

    (this->*commands[index])(str);
}

void AbstractVM::Push(std::string const & str) {
    std::istringstream iss(str);
    std::string type;
    std::string value;
    std::getline(iss, type, ' ');
    std::getline(iss, type, '(');
    std::getline(iss, value, ')');
    std::cout << type << "|" << value << std::endl;
    IOperand const * operand = operandFactory_.createOperand(strToEnum_[type], value);
    stack_.push_back(operand);
    std::cout << "push command" << std::endl;
}

void AbstractVM::Pop(std::string const & str) {
    if (stack_.empty()) {
        throw Exceptions::PopOnEmptyStack();
    }
    IOperand const *lastElement = stack_.back();
    stack_.pop_back();
    delete lastElement;
    std::cout << "pop command, size: " << stack_.size() << std::endl;
}

void AbstractVM::Dump(std::string const & str) {
    std::cout << "dump command" << std::endl;
    for (std::vector<IOperand const *>::reverse_iterator it = stack_.rbegin(); it != stack_.rend(); ++it) {
        std::cout << (*it)->toString()  << std::endl;
    }
}

void AbstractVM::Assert(std::string const & str) {
    if (stack_.empty()) {
        throw Exceptions::AssertOnEmptyStack();
    }
    std::istringstream iss(str);
    std::string type;
    std::string value;
    std::getline(iss, type, ' ');
    std::getline(iss, type, '(');
    std::getline(iss, value, ')');
    std::cout << type << "|" << value << std::endl;
    if (strToEnum_[type] != stack_.back()->getType()) {
        throw Exceptions::AssertDifferentTypes();
    }
    if (value != stack_.back()->toString()) {
        throw Exceptions::AssertDifferentValues();
    }
    std::cout << "assert command" << std::endl;
}

void AbstractVM::Add(std::string const & str) {
    if (stack_.size() < 2) {
        throw Exceptions::LessThenTwoValues();
    }
    IOperand const *v1 = stack_.back();
    IOperand const *v2 = stack_.rbegin()[1];
    std::cout << "add command. " << v2->toString() << " + " << v1->toString() << std::endl;
    IOperand const *result = *v2 + *v1;
    Pop("");
    Pop("");
    stack_.push_back(result);
    std::cout << "result: " << result->toString();
}

void AbstractVM::Sub(std::string const & str) {
    if (stack_.size() < 2) {
        throw Exceptions::LessThenTwoValues();
    }
    IOperand const *v1 = stack_.back();
    IOperand const *v2 = stack_.rbegin()[1];
    std::cout << "sub command. " << v2->toString() << " - " << v1->toString() << std::endl;
    IOperand const *result = *v2 - *v1;
    Pop("");
    Pop("");
    stack_.push_back(result);
}

void AbstractVM::Mul(std::string const & str) {
    if (stack_.size() < 2) {
        throw Exceptions::LessThenTwoValues();
    }
    IOperand const *v1 = stack_.back();
    IOperand const *v2 = stack_.rbegin()[1];
    std::cout << "mul command. " << v2->toString() << " * " << v1->toString() << std::endl;
    IOperand const *result = *v2 * *v1;
    Pop("");
    Pop("");
    stack_.push_back(result);
}

void AbstractVM::Div(std::string const & str) {
    if (stack_.size() < 2) {
        throw Exceptions::LessThenTwoValues();
    }
    IOperand const *v1 = stack_.back();
    IOperand const *v2 = stack_.rbegin()[1];
    std::cout << "div command. " << v2->toString() << " / " << v1->toString() << std::endl;
    IOperand const *result = *v2 / *v1;
    Pop("");
    Pop("");
    stack_.push_back(result);
}

void AbstractVM::Mod(std::string const & str) {
    if (stack_.size() < 2) {
        throw Exceptions::LessThenTwoValues();
    }
    IOperand const *v1 = stack_.back();
    IOperand const *v2 = stack_.rbegin()[1];
    std::cout << "mod command. " << v2->toString() << " % " << v1->toString() << std::endl;
    IOperand const *result = *v2 % *v1;
    Pop("");
    Pop("");
    stack_.push_back(result);
}

void AbstractVM::Print(std::string const & str) {
    std::cout << "print command" << std::endl;
}












int AbstractVM::GetLineCount() const {
    return lineCount_;
}

void AbstractVM::IncrLineCount() {
    ++lineCount_;
}
