#include "Exception.hpp"

const char *Exceptions::LexicalOrSyntactical::what() const throw() {
        return "Assembly contains LEXICAL or SYNTACTICAL errors";
}

const char *Exceptions::UnknownInstruction::what() const throw() {
        return "Assembly contains an UNKNOWN INSTRUCTION";
}

const char *Exceptions::ValueOverflow::what() const throw() {
        return "One of the values got OVERFLOWED";
}

const char *Exceptions::ValueUnderflow::what() const throw() {
        return "One of the values got UNDERFLOWED";
}

const char *Exceptions::PopOnEmptyStack::what() const throw() {
        return "POP was used on an EMPTY STACK";
}

const char *Exceptions::DivisionByZero::what() const throw() {
        return "Do not EVER divide by ZERO. Unless you are using a floating point value";
}

const char *Exceptions::NoExitInstruction::what() const throw() {
        return "Assembly has no EXIT instruction";
}

const char *Exceptions::AssertIsNotTrue::what() const throw() {
        return "ASSERT is not true";
}

const char *Exceptions::LessThenTwoValues::what() const throw() {
        return "ARITHMETIC INCTRUTION was used on less than TWO values";
}
