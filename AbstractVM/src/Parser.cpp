//
// Created by aradiuk on 8/18/2018.
//

#include "Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {
    for (std::vector<IOperand const *>::iterator it = stack_.begin(); it != stack_.end(); ++it) {
        delete *it;
        *it = nullptr;
    }
    stack_.clear();
}

Parser::Parser(const Parser &obj) {
    std::vector<IOperand const *> objStack = obj.getStack();
    for (std::vector<IOperand const *>::iterator it = objStack.begin(); it != objStack.end(); ++it) {
        IOperand const * operand = OperandFactory::getInstance()->createOperand((*it)->getType(), (*it)->toString());
        stack_.push_back(operand);
    }
}

Parser& Parser::operator=(const Parser &obj) {
    if (this != &obj) {
        for (std::vector<IOperand const *>::iterator it = stack_.begin(); it != stack_.end(); ++it) {
            delete *it;
            *it = nullptr;
        }
        stack_.clear();
        std::vector<IOperand const *> objStack = obj.getStack();
        for (std::vector<IOperand const *>::iterator it = objStack.begin(); it != objStack.end(); ++it) {
            IOperand const * operand = OperandFactory::getInstance()->createOperand((*it)->getType(), (*it)->toString());
            stack_.push_back(operand);
        }
    }
    return (*this);
}

void Parser::ReadData(std::vector<std::string> commands) {
    std::string readLine;
    int lineNumber = 0;
    bool exitFound = false;

    for (std::vector<std::string>::iterator it = commands.begin(); it != commands.end(); ++it) {
        ++lineNumber;
        if (it->empty()) {
            continue;
        }

        if (std::regex_match(*it, std::regex("^exit[\\s\\t]*((?=;+);.*|)"))) {
            exitFound = true;
            break;
        }

        try {
            ValidateLine(*it);
        } catch (const std::exception &e) {
            std::cout << "line " << lineNumber << ": " << e.what() << std::endl;
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

void Parser::ValidateLine(std::string str) {
    for (std::vector<std::regex>::iterator it = allowedCommands_.begin(); it != allowedCommands_.end(); it++) {
        if (std::regex_match(str, *it)) {
            if ((it - allowedCommands_.begin()) == 10)
                return ;
            Parser::ProcessCommand(str, it - allowedCommands_.begin());
            return ;
        }
    }
    throw Exceptions::UnknownInstruction();
}

void Parser::ProcessCommand(std::string str, int index) {
    static void (Parser::*commands[10])(std::string const & str) = {
            &Parser::Push,
            &Parser::Pop,
            &Parser::Dump,
            &Parser::Assert,
            &Parser::Add,
            &Parser::Sub,
            &Parser::Mul,
            &Parser::Div,
            &Parser::Mod,
            &Parser::Print,
    };

    (this->*commands[index])(str);
}

void Parser::Push(std::string const & str) {
    std::istringstream iss(str);
    std::string type;
    std::string value;
    std::getline(iss, type, ' ');
    std::getline(iss, type, '(');
    std::getline(iss, value, ')');
    IOperand const * operand = OperandFactory::getInstance()->createOperand(strToEnum_[type], value);
    stack_.push_back(operand);
}

void Parser::Pop(std::string const & str) {
    std::string tmp = str;
    if (stack_.empty()) {
        throw Exceptions::PopOnEmptyStack();
    }
    IOperand const *lastElement = stack_.back();
    stack_.pop_back();
    delete lastElement;
}

void Parser::Dump(std::string const & str) {
    std::string tmp = str;
    for (std::vector<IOperand const *>::reverse_iterator it = stack_.rbegin(); it != stack_.rend(); ++it) {
        std::cout << (*it)->toString()  << std::endl;
    }
}

void Parser::Assert(std::string const & str) {
    if (stack_.empty()) {
        throw Exceptions::AssertOnEmptyStack();
    }
    std::istringstream iss(str);
    std::string type;
    std::string value;
    std::getline(iss, type, ' ');
    std::getline(iss, type, '(');
    std::getline(iss, value, ')');
    if (strToEnum_[type] != stack_.back()->getType()) {
        throw Exceptions::AssertDifferentTypes();
    }
    if (value != stack_.back()->toString()) {
        throw Exceptions::AssertDifferentValues();
    }
}

void Parser::Add(std::string const & str) {
    std::string tmp = str;
    if (stack_.size() < 2) {
        throw Exceptions::LessThenTwoValues();
    }
    IOperand const *v1 = stack_.back();
    IOperand const *v2 = stack_.rbegin()[1];
    IOperand const *result = *v2 + *v1;
    Pop("");
    Pop("");
    stack_.push_back(result);
}

void Parser::Sub(std::string const & str) {
    std::string tmp = str;
    if (stack_.size() < 2) {
        throw Exceptions::LessThenTwoValues();
    }
    IOperand const *v1 = stack_.back();
    IOperand const *v2 = stack_.rbegin()[1];
    IOperand const *result = *v2 - *v1;
    Pop("");
    Pop("");
    stack_.push_back(result);
}

void Parser::Mul(std::string const & str) {
    std::string tmp = str;
    if (stack_.size() < 2) {
        throw Exceptions::LessThenTwoValues();
    }
    IOperand const *v1 = stack_.back();
    IOperand const *v2 = stack_.rbegin()[1];
    IOperand const *result = *v2 * *v1;
    Pop("");
    Pop("");
    stack_.push_back(result);
}

void Parser::Div(std::string const & str) {
    std::string tmp = str;
    if (stack_.size() < 2) {
        throw Exceptions::LessThenTwoValues();
    }
    IOperand const *v1 = stack_.back();
    IOperand const *v2 = stack_.rbegin()[1];
    IOperand const *result = *v2 / *v1;
    Pop("");
    Pop("");
    stack_.push_back(result);
}

void Parser::Mod(std::string const & str) {
    std::string tmp = str;
    if (stack_.size() < 2) {
        throw Exceptions::LessThenTwoValues();
    }
    IOperand const *v1 = stack_.back();
    IOperand const *v2 = stack_.rbegin()[1];
    IOperand const *result = *v2 % *v1;
    Pop("");
    Pop("");
    stack_.push_back(result);
}

void Parser::Print(std::string const & str) {
    std::string tmp = str;
    if (stack_.empty()) {
        throw Exceptions::AssertOnEmptyStack();
    }
    if (stack_.back()->getType() != Int8) {
        throw Exceptions::AssertDifferentTypes();
    }
    int val;
    std::stringstream ss(stack_.back()->toString());
    ss >> val;
    std::cout << static_cast<signed char>(val) << std::endl;
}

std::vector<IOperand const *> Parser::getStack() const {
    return stack_;
}
