//
// Created by aradiuk on 8/18/2018.
//

#ifndef ABSTRACTVM_PARSER_HPP
#define ABSTRACTVM_PARSER_HPP

#include <iostream>
#include <vector>
#include <regex>
#include "OperandFactory.hpp"
#include "IOperand.hpp"

class Parser {
    private:
        std::vector<IOperand const *> stack_;
        std::map<std::string, eOperandType> strToEnum_ = {
            {"int8", Int8},
            {"int16", Int16},
            {"int32", Int32},
            {"float", Float},
            {"double", Double}
        };
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
        Parser();
        ~Parser();
        Parser(const Parser & obj);
        Parser & operator=(const Parser & obj);
        void ReadData(std::vector<std::string> commands);
        void ValidateLine(std::string str);
        void ProcessCommand(std::string str, int index);

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

        std::vector<IOperand const *> getStack() const;
};

#endif //ABSTRACTVM_PARSER_HPP
