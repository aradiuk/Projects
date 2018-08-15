#include "Exception.hpp"

const char *Exceptions::LexicalOrSyntactical::what() const throw() {
        return "Assembly contains LEXICAL or SYNTACTICAL errors.";
}

const char *Exceptions::UnknownInstruction::what() const throw() {
        return "Assembly contains an UNKNOWN INSTRUCTION.";
}

const char *Exceptions::ValueOverflow::what() const throw() {
        return "One of the values got OVERFLOWED.";
}

const char *Exceptions::ValueUnderflow::what() const throw() {
        return "One of the values got UNDERFLOWED.";
}

const char *Exceptions::PopOnEmptyStack::what() const throw() {
        return "POP was used on an EMPTY STACK.";
}

const char *Exceptions::AssertOnEmptyStack::what() const throw() {
        return "ASSERT was used on an EMPTY STACK.";
}

const char *Exceptions::DivisionByZero::what() const throw() {
        return "Division or module by 0";
}

const char *Exceptions::NoExitInstruction::what() const throw() {
        return "Assembly has no EXIT instruction.";
}

const char *Exceptions::AssertDifferentTypes::what() const throw() {
        return "Asserting values with different types.";
}

const char *Exceptions::AssertDifferentValues::what() const throw() {
        return "Asserting values with different values.";
}

const char *Exceptions::LessThenTwoValues::what() const throw() {
        return "ARITHMETIC INSTRUCTION was used on less than TWO values.";
}

const char *Exceptions::DifferentOperandTypes::what() const throw() {
        return "Operands have DIFFERENT TYPES.";
}
