#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include "Logger.hpp"

#include <iostream>
#include <vector>


class AbstractVM {
    private:
        std::vector<std::string> commands;
        std::vector<std::string> values; // not a vector of strings but instead a bector of IOperands

    public:
        AbstractVM();
        ~AbstractVM();
        AbstractVM(const AbstractVM& obj);
        AbstractVM& operator=(const AbstractVM& obj);
        void start(int argc, char **argv);
        void stdInput();
        void fileInput(std::string filename);



        struct AssemblyErrors : public std::exception {
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



#endif /* ABSTRACTVM_HPP */
