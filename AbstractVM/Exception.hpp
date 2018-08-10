#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>

class Exceptions {
public:
    struct LexicalOrSyntactical: public std::exception {
        virtual const char * what() const throw();
    };
    struct UnknownInstruction: public std::exception {
        virtual const char * what() const throw();
    };
    struct ValueOverflow: public std::exception {
        virtual const char * what() const throw();
    };
    struct ValueUnderflow: public std::exception {
        virtual const char * what() const throw();
    };
    struct PopOnEmptyStack: public std::exception {
        virtual const char * what() const throw();
    };
    struct DivisionByZero: public std::exception {
        virtual const char * what() const throw();
    };
    struct NoExitInstruction: public std::exception {
        virtual const char * what() const throw();
    };
    struct AssertIsNotTrue: public std::exception {
        virtual const char * what() const throw();
    };
    struct LessThenTwoValues: public std::exception {
        virtual const char * what() const throw();
    };
};

#endif
