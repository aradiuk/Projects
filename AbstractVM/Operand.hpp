#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "Exception.hpp"

template<class T>
class Operand : public IOperand {
    public:
        int getPrecision( void ) ;
        eOperandType getType( void );
        T value_;

        Operand(eOperandType type = Int8, T val = 0);
        Operand(const Operand& obj);
        Operand& operator=(const Operand& obj);
        IOperand const * operator+( IOperand const & rhs );
        IOperand const * operator-( IOperand const & rhs );
        IOperand const * operator*( IOperand const & rhs );
        IOperand const * operator/( IOperand const & rhs );
        IOperand const * operator%( IOperand const & rhs );

        std::string const & toString( void );

        virtual ~Operand();
};

#endif // OPERAND_HPP
