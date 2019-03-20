//
// Created by Andrew Radiuk on 2019-03-17.
//

#include "ExpertSystem.hpp"

ExpertSystem::ExpertSystem()
{}

ExpertSystem::~ExpertSystem()
{}

ExpertSystem::ExpertSystem(const ExpertSystem &obj)
{}

ExpertSystem& ExpertSystem::operator=(const ExpertSystem &obj)
{
	return *this;
}

void PrintAllTokens(const std::vector<std::vector<Token>> &tokens) {
    for (const auto &it : tokens) {
        for (const auto &itt : it) {
            std::cout << itt.type_ << ": " << itt.value_ << ", ";
        }
        std::cout << std::endl;
    }
}


void ExpertSystem::StartEngine(const std::string &fileName)
{
    tokens_ = lexer_.TokeniseFile(fileName);
    parser_.ParseTokens(tokens_);
    validator_.ValidateTokens(tokens_);
    validator_.ValidateRules(parser_.GetRules());

    std::vector<Rule> polishRules = TransformToPolish(parser_.GetRules());
    PrintAllTokens(tokens_);
}

std::vector<Rule> ExpertSystem::TransformToPolish(const std::vector<Rule> &rules)
{

}
