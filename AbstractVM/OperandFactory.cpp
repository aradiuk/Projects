#include <limits>
#include "OperandFactory.hpp"

IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & value) {
    IOperand const * (OperandFactory::* createOperands[5])(std::string const & value) const = {
            &OperandFactory::createInt8,
            &OperandFactory::createInt16,
            &OperandFactory::createInt32,
            &OperandFactory::createFloat,
            &OperandFactory::createDouble
    };
    std::cout << __FUNCTION__ << ": " << type << " - " << value << std::endl;
    return (this->*createOperands[type])(value);
}

IOperand const * OperandFactory::createInt8(std::string const & val) const {
    std::cout << "Created Int8 operand" << std::endl;
    try {
        int value = std::stoi(val);
        if (value < std::numeric_limits<signed char>::min()) {
            throw Exceptions::ValueUnderflow();
        } else if (value > std::numeric_limits<signed char>::max()) {
            throw Exceptions::ValueOverflow();
        } else {
            std::cout << "Creating int8 operand with value: " << value << std::endl;
//            return (new Operand<Int8>(value));
        }
    } catch (const Exceptions::ValueOverflow& e) {
        throw Exceptions::ValueOverflow();
    } catch (const Exceptions::ValueUnderflow& e) {
        throw Exceptions::ValueUnderflow();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

IOperand const * OperandFactory::createInt16(std::string const & val) const {
    int value = 16;
    std::cout << "Created Int16 operand" << std::endl;
}

IOperand const * OperandFactory::createInt32(std::string const & val) const {
    long value = 32;
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
