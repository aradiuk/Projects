#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include <cstdint>
#include <sstream>
#include <IOperand.hpp>
#include "Exception.hpp"

class OperandFactory {
    public:
        OperandFactory();
        ~OperandFactory();
        OperandFactory(const OperandFactory &obj);
        OperandFactory & operator=(const OperandFactory &obj);
        IOperand const * createOperand(eOperandType type, std::string const & value);
        static OperandFactory *getInstance();


    private:
        static  OperandFactory *instance;
        IOperand const * createInt8(std::string const & value) const;
        IOperand const * createInt16(std::string const & value) const;
        IOperand const * createInt32(std::string const & value) const;
        IOperand const * createFloat(std::string const & value) const;
        IOperand const * createDouble(std::string const & value) const;
};

#endif // OPERANDFACTORY_HPP
