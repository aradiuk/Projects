#include "OperandFactory.hpp"
#include <iostream>

IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & value) {
    IOperand const * (OperandFactory::* createOperands[5])(std::string const & value) const = {
            &OperandFactory::createInt8,
            &OperandFactory::createInt16,
            &OperandFactory::createInt32,
            &OperandFactory::createFloat,
            &OperandFactory::createDouble
    };

    return (this->*createOperands[type])(value);
}

IOperand const * OperandFactory::createInt8(std::string const & value) const {
    std::cout << "Created Int8 operand" << std::endl;
}

IOperand const * OperandFactory::createInt16(std::string const & value) const {
    std::cout << "Created Int16 operand" << std::endl;
}

IOperand const * OperandFactory::createInt32(std::string const & value) const {
    std::cout << "Created Int32 operand" << std::endl;
}

IOperand const * OperandFactory::createFloat(std::string const & value) const {
    std::cout << "Created Float operand" << std::endl;
}

IOperand const * OperandFactory::createDouble(std::string const & value) const {
    std::cout << "Created Double operand" << std::endl;
}
