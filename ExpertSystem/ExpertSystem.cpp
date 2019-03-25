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
    facts_ = parser_.GetFacts();
    validator_.ValidateQuery(facts_, parser_.GetInitialFacts(), parser_.GetQueryFacts());
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
            std::cout << "Requested fact '" << factSearch->first << "' is '" << status << std::endl;
        }
    }
}

Fact ExpertSystem::BackwardChaining(const std::string &name)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    std::vector<bool> conclusions;

    for (auto &rule : polishRules_) {
        UpdateTokensStatus(rule.lhs_);
        UpdateTokensStatus(rule.rhs_);
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
        return it != conclusions.end();
    }

}

bool ExpertSystem::Solve(Rule &rule, const std::string &name)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    bool factStatus = false;
    rule.visited_ = true;
    if (IsFactOnThisSide(name, rule.rhs_)) {
        factStatus = FindFactStatus(name, rule.rhs_, GetStatusOfSide(rule.lhs_), rule.operator_);
    } else if (IsFactOnThisSide(name, rule.lhs_)) {
        factStatus = FindFactStatus(name, rule.lhs_, GetStatusOfSide(rule.rhs_), rule.operator_);
    }
//    rule.visited_ = false;
    return factStatus;
}

bool ExpertSystem::FindFactStatus(const std::string &name, const std::vector<Token> &tokens, bool sideStatus, const Token &operatorToken)
{
    if (operatorToken.type_ == TokenType::IfAndOnlyIf ||
        operatorToken.type_ == TokenType::Implies) {
        std::vector<Token> withTrueFact;
        std::vector<Token> withFalseFact;
        for (const auto &token : tokens) {
            withTrueFact.emplace_back(token);
            withFalseFact.emplace_back(token);
            if (token.value_ == name) {
                withTrueFact.back().factStatus_ = Fact(true);
                withFalseFact.back().factStatus_ = Fact(false);
            }
        }
        std::pair<bool, bool> statusForTrueAndFalse = std::make_pair(
                                                      GetStatusOfSide(withTrueFact),
                                                      GetStatusOfSide(withFalseFact));
        if (sideStatus) {
            if (statusForTrueAndFalse.first) {
                return true;
            } else if (statusForTrueAndFalse.second) {
                return false;
            } else {
                throw "Rule seems to be wrong.";
            }
        } else if (operatorToken.type_ == TokenType::IfAndOnlyIf) {
            if (!statusForTrueAndFalse.first) {
                return true;
            } else if (!statusForTrueAndFalse.second) {
                return false;
            } else {
                throw "Rule seems to be wrong.";
            }
        } else {
            return false;
        }
    } else {
        throw "How did this thing get here?! Thing: " + operatorToken.value_;
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
                UpdateTokensStatus(tokens);
            }
            if (!first.factStatus_.IsInitialised()) {
                first.factStatus_ = BackwardChaining(first.value_);
                facts_[first.value_] = first.factStatus_;
                UpdateTokensStatus(tokens);
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
        return false;
    } else {
        return stack.front().factStatus_.status_;
    }
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


void ExpertSystem::UpdateTokensStatus(std::vector<Token> &tokens)
{
#ifdef LOG
    std::cout << __FUNCTION__  << std::endl;
#endif

    for (auto &token : tokens) {
        if (token.type_ == TokenType::Fact) {
            token.factStatus_ = facts_.at(token.value_);
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
