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
    return (this->*createOperands[type])(value);
}

IOperand const * OperandFactory::createInt8(std::string const & val) const {
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
    try {
        int value = std::stoi(val);
        if (value < std::numeric_limits<short>::min()) {
            throw Exceptions::ValueUnderflow();
        } else if (value > std::numeric_limits<short>::max()) {
            throw Exceptions::ValueOverflow();
        } else {
            std::cout << "Creating int16 operand with value: " << value << std::endl;
//            return (new Operand<Int16>(value));
        }
    } catch (const Exceptions::ValueOverflow& e) {
        throw Exceptions::ValueOverflow();
    } catch (const Exceptions::ValueUnderflow& e) {
        throw Exceptions::ValueUnderflow();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

IOperand const * OperandFactory::createInt32(std::string const & val) const {
    try {
        long value = std::stol(val);
        if (value < std::numeric_limits<int>::min()) {
            throw Exceptions::ValueUnderflow();
        } else if (value > std::numeric_limits<int>::max()) {
            throw Exceptions::ValueOverflow();
        } else {
            std::cout << "Creating int32 operand with value: " << value << std::endl;
//            return (new Operand<Int32>(value));
        }
    } catch (const Exceptions::ValueOverflow& e) {
        throw Exceptions::ValueOverflow();
    } catch (const Exceptions::ValueUnderflow& e) {
        throw Exceptions::ValueUnderflow();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

IOperand const * OperandFactory::createFloat(std::string const & val) const {
    try {
        double value = std::stod(val);
        if (value < std::numeric_limits<float>::min()) {
            throw Exceptions::ValueUnderflow();
        } else if (value > std::numeric_limits<float>::max()) {
            throw Exceptions::ValueOverflow();
        } else {
            std::cout << "Creating float operand with value: " << value << std::endl;
//            return (new Operand<Float>(value));
        }
    } catch (const Exceptions::ValueOverflow& e) {
        throw Exceptions::ValueOverflow();
    } catch (const Exceptions::ValueUnderflow& e) {
        throw Exceptions::ValueUnderflow();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

IOperand const * OperandFactory::createDouble(std::string const & val) const {
    try {
        long double value = std::stold(val);
        if (value < std::numeric_limits<double>::min()) {
            throw Exceptions::ValueUnderflow();
        } else if (value > std::numeric_limits<double>::max()) {
            throw Exceptions::ValueOverflow();
        } else {
            std::cout << "Creating double operand with value: " << value << std::endl;
//            return (new Operand<Double>(value));
        }
    } catch (const Exceptions::ValueOverflow& e) {
        throw Exceptions::ValueOverflow();
    } catch (const Exceptions::ValueUnderflow& e) {
        throw Exceptions::ValueUnderflow();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "Created Double operand" << std::endl;
}
