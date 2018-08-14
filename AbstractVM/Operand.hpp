#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "Exception.hpp"
#include <sstream>

template<class T>
class Operand : public IOperand {
private:
        T value_;
        eOperandType type_;
        std::string strValue_;

public:
        Operand(eOperandType type = Int8, T val = 0, std::string str ="") : type_(type), value_(val), strValue_(str) {};
        Operand(const Operand& obj) {
            if (type_ != obj.getType()) {
                throw Exceptions::DifferentOperandTypes();
            }

            std::stringstream ss;
            type_ = obj.getType();
            strValue_ = obj.toString();
            ss << strValue_;
            ss >> value_;
        };
        Operand& operator=(const Operand& obj) {
            if (this == &obj)
                return (*this);

            if (type_ != obj.getType()) {
                throw Exceptions::DifferentOperandTypes();
            }

            std::stringstream ss;
            type_ = obj.getType();
            strValue_ = obj.toString();
            ss << strValue_;
            ss >> value_;
            return (*this);
        };

        IOperand const * operator+( IOperand const & rha ) const {
            eOperandType resType = std::max(type_, rha.getType());
            std::stringstream ss(rha.toString());
            long double rightValue;
            ss >> rightValue;
            long double resValue = value_ + rightValue;
            // Create new operand
        };

        IOperand const * operator-( IOperand const & rha ) const {
            eOperandType resType = std::max(type_, rha.getType());
            std::stringstream ss(rha.toString());
            long double rightValue;
            ss >> rightValue;
            long double resValue = value_ - rightValue;
            // Create new operand
        };

        IOperand const * operator*( IOperand const & rha ) const {
            eOperandType resType = std::max(type_, rha.getType());
            std::stringstream ss(rha.toString());
            long double rightValue;
            ss >> rightValue;
            long double resValue = value_ * rightValue;
            // Create new operand
        };

        IOperand const * operator/( IOperand const & rha ) const {
            eOperandType resType = std::max(type_, rha.getType());
            std::stringstream ss(rha.toString());
            long double rightValue;
            ss >> rightValue;
            long double resValue = value_ + rightValue;
            // Add exception about division by zero
            // Create new operand
        };

        IOperand const * operator%( IOperand const & rha ) const {
            eOperandType resType = std::max(type_, rha.getType());
            std::stringstream ss(rha.toString());
            long double rightValue;
            ss >> rightValue;
            long double resValue = value_ + rightValue;
            // Add exception about division by zero
            // Create new operand
        };

        int getPrecision( void ) const {
            return type_;
        };

        eOperandType getType( void ) const {
            return type_;
        };

        std::string const & toString( void ) const {
            return strValue_;
        }

        virtual ~Operand() {};
};

#endif // OPERAND_HPP
