//
// Created by Andrew Radiuk on 2019-03-17.
//

#include "ExpertSystem.hpp"

#define LOG

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
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    tokens_ = lexer_.TokeniseFile(fileName);
    parser_.ParseTokens(tokens_);
    validator_.ValidateTokens(tokens_);
    validator_.ValidateRules(parser_.GetRules());
    validator_.ValidateQuery(parser_.GetFacts(), parser_.GetInitialFacts(), parser_.GetQueryFacts());
    facts_ = parser_.GetFacts();
    rules_ = parser_.GetRules();
    queryFacts_ = parser_.GetQueryFacts();

    polishRules_ = TransformRulesToPolish(rules_);
    Evaluate(polishRules_);
    PrintAllTokens(tokens_);
}

std::vector<Rule> ExpertSystem::TransformRulesToPolish(const std::vector<Rule> &rules)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    std::vector<Rule> polishRules;

    for (const auto &rule : rules) {
#ifdef LOGG
        std::cout << "BEFORE" << std::endl;
        for (auto tok : rule.lhs_ ) {
            std::cout << tok.value_ << " ";
        }
        std::cout << rule.operator_.value_ << " ";
        for (auto tok : rule.rhs_ ) {
            std::cout << tok.value_ << " ";
        }
        std::cout << std::endl;
#endif
        Rule newRule;
        newRule.lhs_ = TransformOneSide(rule.lhs_);
        newRule.rhs_ = TransformOneSide(rule.rhs_);
        newRule.operator_ = rule.operator_;
        polishRules.push_back(newRule);
#ifdef LOGG

        std::cout << "AFTER" << std::endl;
          for (auto tok : newRule.lhs_ ) {
              std::cout << tok.value_ << " ";
          }
          std::cout << newRule.operator_.value_ << " ";
          for (auto tok : newRule.rhs_ ) {
              std::cout << tok.value_ << " ";
          }
          std::cout << std::endl;
#endif
    }

    return polishRules;
}

std::vector<Token> ExpertSystem::TransformOneSide(const std::vector<Token> &tokens)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    std::vector<Token> operators;
    std::vector<Token> stack;
    bool haveNot = false;

    for (const auto &token : tokens) {
        if (token.type_ == TokenType::CloseParenthesis) {
#ifdef LOGG

            std::cout << "Close" << std::endl;
            for (auto it : operators)
                std::cout << "op: " << it.value_ << std::endl;
            for (auto it : stack)
                std::cout << "st: " << it.value_ << std::endl;
#endif

            if (operators.empty()) {
                throw "Nothing before ')'";
            }
            if (operators.back().type_ == TokenType::OpenParenthesis) {
                throw "Nothing between parentheses.";
            }
            while (!operators.empty() && operators.back().type_ != TokenType::OpenParenthesis) {
                stack.push_back(operators.back());
                operators.pop_back();
            }
            operators.pop_back();
        } else if (IsOperator(token)) {
#ifdef LOGG

            std::cout << "Operator: " << token.value_ << std::endl;
            for (auto it : operators)
                std::cout << "op: " << it.value_ << std::endl;
            for (auto it : stack)
                std::cout << "st: " << it.value_ << std::endl;
#endif

            while (!operators.empty() && operators.back().type_ < token.type_ && operators.back().type_ != TokenType::OpenParenthesis) {
                stack.push_back(operators.back());
                operators.pop_back();
            }
            operators.push_back(token);
        } else if (token.type_ == TokenType::Not) {
#ifdef LOGG

            std::cout << "Not" << std::endl;
            for (auto it : operators)
                std::cout << "op: " << it.value_ << std::endl;
            for (auto it : stack)
                std::cout << "st: " << it.value_ << std::endl;
#endif

            haveNot = true;
        } else {
#ifdef LOGG

            std::cout << "Else: " << token.value_ << std::endl;
            for (auto it : operators)
                std::cout << "op: " << it.value_ << std::endl;
            for (auto it : stack)
                std::cout << "st: " << it.value_ << std::endl;
#endif

            if (haveNot && token.type_ != TokenType::Fact) {
                throw "Somehow missed '!' before not a fact";
            }
            if (token.type_ == TokenType::OpenParenthesis) {
                operators.push_back(token);
            } else if (token.type_ == TokenType::Fact) {
                Token newToken = token;
                newToken.isNegative_ = haveNot;
                stack.push_back(token);
                haveNot = false;
            } else {
                throw "Should never happen. Unexpected token in transform.";
            }
        }
    }
    while (!operators.empty()) {
        stack.push_back(operators.back());
        operators.pop_back();
    }

    return stack;
}

void ExpertSystem::Evaluate(const std::vector<Rule> &polishRules)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    for (const auto &queryFact : queryFacts_) {
        auto factSearch = facts_.find(queryFact.first);
        if (factSearch == facts_.end()) {
            throw "Query fact wasn't found in all facts.";
        }

        if (factSearch->second == boost::none) {
            factSearch->second = BackwardChaining(factSearch->first);
        }
    }

    for (const auto &queryFact : queryFacts_) {
        auto factSearch = facts_.find(queryFact.first);

        if (factSearch != facts_.end()) {
            std::string status;
            if (factSearch->second == boost::none) {
                status = "Unknown";
            } else if (*(factSearch->second)) {
                status = "True";
            } else if (!*(factSearch->second)) {
                status = "False";
            }
            std::cout << "Requested fact '" << factSearch->first << "' is '" << status << std::endl;
        }
    }
}

boost::optional<bool> ExpertSystem::BackwardChaining(const std::string &name)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    std::vector<bool> multConcl;

    for (auto &rule : polishRules_) {
        UpdateTokensStatus(rule);
        if (rule.rhs_.size() == 1 &&
            rule.rhs_.front().value_ == name &&
            !rule.visited_) {
                rule.visited_ = true;
                multConcl.push_back(CheckNegative(rule.rhs_.front(), Solve(rule)));
        }
    }

    if (!multConcl.empty()) {
        return (std::find(multConcl.begin(), multConcl.end(), true) != multConcl.end());
    }

    for (auto &rule : polishRules_) {
        if (!rule.visited_ &&
            IsFactInSequence(name, rule.lhs_) &&
            IsSequenceSimple(rule.lhs_) &&
            rule.operator_.type_ == TokenType::IfAndOnlyIf &&
            rule.rhs_.size() == 1 &&
            rule.rhs_.front().factStatus_) {
                rule.visited_ = true;
                for (auto &token : rule.lhs_) {
                    if (token.type_ == TokenType::Fact) {
                        token.factStatus_ = CheckNegative(token, true);
                        facts_[token.value_] = token.factStatus_;
                    }
                }
                if (facts_[name] != boost::none) {
                    return *facts_[name];
                }
                return true;
        }

        if (rule.rhs_.size() != 1 &&
            !rule.visited_ &&
            IsFactInSequence(name, rule.rhs_) &&
            IsSequenceSimple(rule.rhs_) &&
            !IsFactInSequence(name, rule.lhs_) &&
            Solve(rule)) {
                rule.visited_ = true;
                for (auto &token : rule.rhs_) {
                    if (token.type_ == TokenType::Fact) {
                        token.factStatus_ = CheckNegative(token, true);
                        facts_[token.value_] = token.factStatus_;
                    }
                }
        }
        if (facts_[name] != boost::none) {
            return *facts_[name];
        }
        return true;
    }

    return false;
}

bool ExpertSystem::Solve(Rule &rule)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    std::vector<Token> stack;

    if (rule.lhs_.size() == 1) {
        Token token = rule.lhs_.front();
        auto &factStatus = facts_[token.value_];
        if (factStatus == boost::none) {
            factStatus = BackwardChaining(token.value_);
        }
        return CheckNegative(token, factStatus);
    }

    for (const auto &token : rule.lhs_) {
        if (validator_.operators_.find(token.type_) != validator_.operators_.end()) {
            if (stack.size() < 2) {
                throw "Operator on a stack with less than two elements.";
            }

            Token secondToken = stack.back();
            stack.pop_back();
            Token firstToken = stack.back();
            stack.pop_back();

            if (secondToken.factStatus_ == boost::none) {
                secondToken.factStatus_ = BackwardChaining(secondToken.value_);
                facts_[secondToken.value_] = secondToken.factStatus_;
            }
            if (firstToken.factStatus_ == boost::none) {
                firstToken.factStatus_ = BackwardChaining(firstToken.value_);
                facts_[firstToken.value_] = firstToken.factStatus_;
            }
            bool result = UseOperator(CheckNegative(firstToken, firstToken.factStatus_),
                                      CheckNegative(secondToken, secondToken.factStatus_),
                                      token.type_);
            Token newToken(TokenType::Invalid, "");
            newToken.factStatus_ = result;
            stack.push_back(newToken);
        } else {
            stack.push_back(token);
        }
    }
    if (stack.size() > 1) {
        throw "Stacks aren't empty.";
    }

    rule.visited_ = true;
    if (stack.back().factStatus_ != boost::none) {
        return *(stack.back().factStatus_);
    } else {
        return false;
    }

}

bool ExpertSystem::CheckNegative(const Token &token, boost::optional<bool> status)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    if (status == boost::none) {
        throw "Couldn't detect a status of the fact.";
    }

    return token.isNegative_ ? !*status : *status;
}

bool ExpertSystem::UseOperator(bool first, bool second, TokenType operatorType)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    if (operatorType == TokenType::And) {
        return first && second;
    } else if (operatorType == TokenType::Or) {
        return first || second;
    } else if (operatorType == TokenType::Xor) {
        return first ^ second;
    }
}

bool ExpertSystem::IsFactInSequence(const std::string &name, const std::vector<Token> &sequence)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    const auto fact = std::find_if(sequence.begin(),
                                    sequence.end(),
                                    [&name](const Token &token) -> bool {
                                        return name == token.value_;
    });
    if (fact != sequence.end()) {
        return true;
    } else {
        return false;
    }
}

void ExpertSystem::UpdateTokensStatus(Rule &rule)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    for (auto token : rule.lhs_) {
        token.factStatus_ = facts_[token.value_];
    }
    for (auto token : rule.rhs_) {
        token.factStatus_ = facts_[token.value_];
    }
}

bool ExpertSystem::IsSequenceSimple(const std::vector<Token> &sequence)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    for (const auto &token : sequence) {
        if (token.type_ != TokenType::Fact &&
            token.type_ != TokenType::And) {
                return false;
        }
    }

    for (const auto &token : sequence) {
        if (token.type_ == TokenType::Fact &&
            ((token.isNegative_ && token.factStatus_ == true) ||
            (!token.isNegative_ && token.factStatus_ == false))) {
                return false;
        }
    }

    return true;
}
