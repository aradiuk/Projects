#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include "Operand.hpp"
#include <cstdint>
#include <sstream>

class OperandFactory {
    public:
        IOperand const * createOperand(eOperandType type, std::string const & value);

    private:
        IOperand const * createInt8(std::string const & value) const;
        IOperand const * createInt16(std::string const & value) const;
        IOperand const * createInt32(std::string const & value) const;
        IOperand const * createFloat(std::string const & value) const;
        IOperand const * createDouble(std::string const & value) const;
};

#endif // OPERANDFACTORY_HPP
