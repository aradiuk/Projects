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
        std::map<std::string, eOperandType> strToEnum_ = {
                {"int8", Int8},
                {"int16", Int16},
                {"int32", Int32},
                {"float", Float},
                {"double", Double}
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

        void Push(std::string const & str);
        void Pop(std::string const & str);
        void Dump(std::string const & str);
        void Assert(std::string const & str);
        void Add(std::string const & str);
        void Sub(std::string const & str);
        void Mul(std::string const & str);
        void Div(std::string const & str);
        void Mod(std::string const & str);
        void Print(std::string const & str);
        void Parse(std::string const & str);

};



#endif /* ABSTRACTVM_HPP */
