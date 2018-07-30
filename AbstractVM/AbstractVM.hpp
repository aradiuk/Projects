#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include "Logger.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <regex>

#include "OperandFactory.hpp"

class AbstractVM {
    private:
        std::vector<std::string> commands_;
        std::vector<IOperand *> stack_;
        int lineCount_;
        std::vector<std::regex> allowedCommands_ = {
                std::regex("^push\\s(((int8|int16|int32)\\([-]?\\d+\\))|((float|double)\\([-]?\\d+\\.\\d+\\)))[\\s\\t]*((?=;+);.*|)"),
                std::regex("^pop[\\s\\t]*((?=;+);.*|)"),
                std::regex("^dump[\\s\\t]*((?=;+);.*|)"),
                std::regex("^assert\\s(((int8|int16|int32)\\([-]?\\d+\\))|((float|double)\\([-]?\\d+\\.\\d+\\)))[\\s\\t]*((?=;+);.*|)"),
                std::regex("^add[\\s\\t]*((?=;+);.*|)"),
                std::regex("^sub[\\s\\t]*((?=;+);.*|)"),
                std::regex("^mul[\\s\\t]*((?=;+);.*|)"),
                std::regex("^div[\\s\\t]*((?=;+);.*|)"),
                std::regex("^mod[\\s\\t]*((?=;+);.*|)"),
                std::regex("^print[\\s\\t]*((?=;+);.*|)"),
                std::regex("^;.*")
        };

    public:
        OperandFactory operandFactory_;

        AbstractVM();
        ~AbstractVM();
        AbstractVM(const AbstractVM& obj);
        AbstractVM& operator=(const AbstractVM& obj);
        void Start(int argc, char **argv);
        void StdInput();
        void FileInput(std::string filename);
        void ValidateLine(std::string str);
        void ProcessCommand(std::string str, int index);

        int GetLineCount() const;
        void IncrLineCount();

        void push(std::string const & str);
        void pop(std::string const & str);
        void dump(std::string const & str);
        void assert(std::string const & str);
        void add(std::string const & str);
        void sub(std::string const & str);
        void mul(std::string const & str);
        void div(std::string const & str);
        void mod(std::string const & str);
        void print(std::string const & str);

        struct LexicalOrSyntactical : public std::exception {
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
