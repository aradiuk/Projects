#include <limits>
#include "OperandFactory.hpp"
#include "Operand.hpp"

OperandFactory *OperandFactory::instance;

OperandFactory* OperandFactory::getInstance() {
    if (instance == nullptr) {
        instance = new OperandFactory();
    }
    return (instance);
}

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
            return (new Operand<signed char>(Int8, value, val));
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
            return (new Operand<short>(Int16, value, val));
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
            return (new Operand<int>(Int32, value, val));
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
        long double value = std::stold(val);
        if (value < std::numeric_limits<float>::lowest()) {
            throw Exceptions::ValueUnderflow();
        } else if (value > std::numeric_limits<float>::max()) {
            throw Exceptions::ValueOverflow();
        } else {
            return (new Operand<float>(Float, value, val));
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
        if (value < std::numeric_limits<double>::lowest()) {
            throw Exceptions::ValueUnderflow();
        } else if (value > std::numeric_limits<double>::max()) {
            throw Exceptions::ValueOverflow();
        } else {
            return (new Operand<double>(Double, value, val));
        }
    } catch (const Exceptions::ValueOverflow& e) {
        throw Exceptions::ValueOverflow();
    } catch (const Exceptions::ValueUnderflow& e) {
        throw Exceptions::ValueUnderflow();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

OperandFactory::OperandFactory() = default;

OperandFactory::OperandFactory(const OperandFactory &obj) = default;

OperandFactory& OperandFactory::operator=(const OperandFactory &obj) = default;

OperandFactory::~OperandFactory() = default;