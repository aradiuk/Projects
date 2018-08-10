#include "OperandFactory.hpp"

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

IOperand const * OperandFactory::createInt8(std::string const & val) const {
    std::cout << "Created Int8 operand" << std::endl;
    try {
        std::stringstream ss(val);
        int16_t value = 0;
        ss >> value;
        std::cout << "value: " << value << std::endl;
    } catch (const std::out_of_range & e) {
        std::cout << e.what();
    }
}

IOperand const * OperandFactory::createInt16(std::string const & val) const {
    int32_t value = 16;
    std::cout << "Created Int16 operand" << std::endl;
}

IOperand const * OperandFactory::createInt32(std::string const & val) const {
    int64_t value = 32;
    std::cout << "Created Int32 operand" << std::endl;
}

IOperand const * OperandFactory::createFloat(std::string const & val) const {
    long double value = 111;
    std::cout << "Created Float operand" << std::endl;
}

IOperand const * OperandFactory::createDouble(std::string const & val) const {
    long double value = 222;
    std::cout << "Created Double operand" << std::endl;
}
