#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"

template<class T>
class Operand : public IOperand {
    public:
        int getPrecision( void ) ;
        eOperandType getType( void );

        IOperand const * operator+( IOperand const & rhs );
        IOperand const * operator-( IOperand const & rhs );
        IOperand const * operator*( IOperand const & rhs );
        IOperand const * operator/( IOperand const & rhs );
        IOperand const * operator%( IOperand const & rhs );

        std::string const & toString( void );

        virtual ~Operand();
};

#endif // OPERAND_HPP
