//
// Created by Andrew Radiuk on 2019-03-17.
//

#include "ExpertSystem.hpp"

//#define LOG

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

void ExpertSystem::PrintRequestedFact(const std::string &name, const std::string &status)
{
    std::cout << "-------------------" << std::endl;
    if (status == "True") {
        std::cout << "|" << "\033[1;42m   " << name << "   \033[0m" << "|  ";
        std::cout << "\033[1;32m" << status << "\033[0m" << "   |" << std::endl;
    } else {
        std::cout << "|" << "\033[1;41m   " << name << "   \033[0m" << "|  ";
        std::cout << "\033[1;31m" << status << "\033[0m" << "  |" << std::endl;
    }

//    std::cout << "----------------" << std::endl;
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
    facts_ = parser_.GetFacts();
    validator_.ValidateQuery(facts_, parser_.GetInitialFacts(), parser_.GetQueryFacts());
    rules_ = parser_.GetRules();
    queryFacts_ = parser_.GetQueryFacts();

    polishRules_ = TransformRulesToPolish(rules_);
    PrintAllTokens(tokens_);
    Evaluate(polishRules_);
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
            while (!operators.empty() && operators.back().type_ < token.type_ && operators.back().type_ != TokenType::OpenParenthesis) {
                stack.push_back(operators.back());
                operators.pop_back();
            }
            operators.push_back(token);
        } else if (token.type_ == TokenType::Not) {
            haveNot = true;
        } else {
            if (haveNot && token.type_ != TokenType::Fact) {
                throw "Somehow missed '!' before not a fact";
            }
            if (token.type_ == TokenType::OpenParenthesis) {
                operators.push_back(token);
            } else if (token.type_ == TokenType::Fact) {
                Token newToken = token;
                newToken.isNegative_ = haveNot;
                stack.push_back(newToken);
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

        if (!factSearch->second.IsInitialised()) {
            factSearch->second = BackwardChaining(factSearch->first);
        }
    }

    for (const auto &queryFact : queryFacts_) {
        auto factSearch = facts_.find(queryFact.first);

        if (factSearch != facts_.end()) {
            std::string status;
            if (!factSearch->second.IsInitialised()) {
                status = "Unknown";
            } else if (factSearch->second.status_) {
                status = "True";
            } else if (!factSearch->second.status_) {
                status = "False";
            }
            PrintRequestedFact(factSearch->first, status);
        }
    }
    std::cout << "-------------------" << std::endl;
}

Fact ExpertSystem::BackwardChaining(const std::string &name)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    std::vector<bool> conclusions;

    for (auto &rule : polishRules_) {
        UpdateTokensStatus();
        if ((IsFactOnThisSide(name, rule.rhs_) ||
            IsFactOnThisSide(name, rule.lhs_)) &&
            !rule.visited_) {
            conclusions.push_back(Solve(rule, name));
        }
    }

    if (conclusions.empty()) {
        return Fact(false);
    } else {
        const auto it = std::find(conclusions.begin(), conclusions.end(), true);
        if (it != conclusions.end()) {
            return Fact(true);
        } else {
            return Fact(false);
        }
    }

}

bool ExpertSystem::Solve(Rule &rule, const std::string &name)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    Token result;
    result.factStatus_ = Fact(false);
    rule.visited_ = true;
    if (IsFactOnThisSide(name, rule.rhs_)) {
        result = RevertIfNegative(FindFactStatus(name, rule.rhs_, GetStatusOfSide(rule.lhs_), rule.operator_, true));
    } else if (IsFactOnThisSide(name, rule.lhs_)) {
        result = RevertIfNegative(FindFactStatus(name, rule.lhs_, GetStatusOfSide(rule.rhs_), rule.operator_, false));
    }
    rule.visited_ = false;
    return result.factStatus_.status_;
}

Token ExpertSystem::FindFactStatus(const std::string &name, std::vector<Token> &tokens, bool sideStatus, const Token &operatorToken, bool isFactInConclusion)
{
    Token result;
    result.factStatus_ = Fact(false);

    if (operatorToken.type_ == TokenType::IfAndOnlyIf ||
        operatorToken.type_ == TokenType::Implies) {
        if (tokens.size() == 1) {
            result.factStatus_.status_ = DeduceStatus(tokens, operatorToken, sideStatus, isFactInConclusion);
            return result;
        } else if (OnlyAndInTokens(tokens)) {
            if (sideStatus) {
                for (auto &token : tokens) {
                    if (token.type_ == TokenType::Fact) {
                        token.factStatus_ = Fact(true);
                    }
                }
                result.factStatus_.status_ = true;
            } else if (AllExceptUnknown(name, tokens, true)) {
                result.factStatus_.status_ = false;
            }
        } else if (OnlyOrInTokens(tokens)) {
            if (!sideStatus) {
                for (auto &token : tokens) {
                    if (token.type_ == TokenType::Fact) {
                        token.factStatus_ = Fact(false);
                    }
                }
                result.factStatus_.status_ = false;
            } else if (AllExceptUnknown(name, tokens, false)) {
                result.factStatus_.status_ = true;
            }
        }
    } else {
        throw "How did this thing get here?! Thing: " + operatorToken.value_;
    }

    return result;
}

bool ExpertSystem::AllExceptUnknown(const std::string &name, const std::vector<Token> &tokens, bool trueOrFalse)
{
    for (const auto &token : tokens) {
        if (token.value_ == name) {
            continue;
        } else if (token.factStatus_.status_ != trueOrFalse) {
            return false;
        }
    }
    return true;
}

bool ExpertSystem::OnlyAndInTokens(const std::vector<Token> &tokens)
{
    for (const auto &token : tokens) {
        if (token.type_ != TokenType::Fact &&
            token.type_ != TokenType::And) {
            return false;
        }
    }
    return true;
}

bool ExpertSystem::OnlyOrInTokens(const std::vector<Token> &tokens)
{
    for (const auto &token : tokens) {
        if (token.type_ != TokenType::Fact &&
            token.type_ != TokenType::Or) {
            return false;
        }
    }
    return true;
}

bool ExpertSystem::DeduceStatus(const std::vector<Token> &tokens, const Token &operatorToken, bool sideStatus, bool isFactInConclusion)
{
    if (operatorToken.type_ == TokenType::IfAndOnlyIf) {
        if (sideStatus) {
            return true;
        } else {
            return false;
        }
    } else if (operatorToken.type_ == TokenType::Implies) {
        if (isFactInConclusion && sideStatus) {
            return true;
        } else if (!isFactInConclusion && !sideStatus) {
            return false;
        }
    } else {
        throw "One of the rules is wrong.";
    }
}


bool ExpertSystem::GetStatusOfSide(std::vector<Token> &tokens)
{
    std::vector<Token> stack;
    for (auto &token : tokens) {
        if (validator_.operators_.find(token.type_) != validator_.operators_.end()) {
            if (stack.size() < 2) {
                throw "Operation on a stack with less than two elements.";
            }

            Token second = stack.back();
            stack.pop_back();
            Token first = stack.back();
            stack.pop_back();
            if (!second.factStatus_.IsInitialised()) {
                second.factStatus_ = BackwardChaining(second.value_);
                facts_[second.value_] = second.factStatus_;
                UpdateTokensStatus();
            }
            if (!first.factStatus_.IsInitialised()) {
                first.factStatus_ = BackwardChaining(first.value_);
                facts_[first.value_] = first.factStatus_;
                UpdateTokensStatus();
            }

            Token newToken;
            newToken.factStatus_ = Fact(UseOperator(RevertIfNegative(first),
                                                    RevertIfNegative(second),
                                                    token));
            stack.push_back(newToken);
        } else {
            stack.push_back(token);
        }
    }
    if (stack.size() != 1) {
        throw "Stack size after solving isn't equal to 1.";
    }
    if (!stack.front().factStatus_.IsInitialised()) {
        stack.front().factStatus_ = BackwardChaining(stack.front().value_);
        facts_[stack.front().value_] = stack.front().factStatus_;
        UpdateTokensStatus();
    }
    return stack.front().factStatus_.status_;
}

Token ExpertSystem::RevertIfNegative(const Token &token)
{
   Token newToken {token};

   if (token.isNegative_) {
       newToken.factStatus_.status_ = !token.factStatus_.status_;
   } else {
       newToken.factStatus_.status_ = token.factStatus_.status_;
   }

   return newToken;
}

bool ExpertSystem::UseOperator(const Token &first, const Token &second, const Token &operatorToken)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    if (operatorToken.type_ == TokenType::And) {
        return first.factStatus_.status_ && second.factStatus_.status_;
    } else if (operatorToken.type_ == TokenType::Or) {
        return first.factStatus_.status_ || second.factStatus_.status_;
    } else if (operatorToken.type_ == TokenType::Xor) {
        return first.factStatus_.status_ ^ second.factStatus_.status_;
    } else {
        throw "There shouldn't be any other operator, but here is is: " + operatorToken.value_;
    }
}


void ExpertSystem::UpdateTokensStatus()
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    for (auto &rule : polishRules_) {
        for (auto &token : rule.lhs_) {
            if (token.type_ == TokenType::Fact) {
                token.factStatus_ = facts_.at(token.value_);
            }
        }
        for (auto &token : rule.rhs_) {
            if (token.type_ == TokenType::Fact) {
                token.factStatus_ = facts_.at(token.value_);
            }
        }
    }

}

bool ExpertSystem::IsFactOnThisSide(const std::string &name, const std::vector<Token> &tokens)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    const auto fact = std::find_if(tokens.begin(), tokens.end(), [&name](const Token &token) -> bool {
        return token.value_ == name;
    });

    return fact != tokens.end();
}
