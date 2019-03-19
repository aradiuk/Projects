/*
 * Validator.hpp
 *
 *  Created on: Mar 18, 2019
 *      Author: aradiuk
 */

#ifndef VALIDATOR_HPP_
#define VALIDATOR_HPP_

#include "Lexer.hpp"
#include "Parser.hpp"

class Validator {

    public:
        Validator();
        ~Validator();
        Validator(const Validator &obj);
        Validator &operator=(const Validator &obj);

        void ValidateTokens(const std::vector<std::vector<Token>> &tokens);
        void ValidateTokensQuantity(int rules, int initialFacts, int queries);
        void ValidateRules(const std::vector<Rule> &rules);
        void ValidateOneSide(const std::vector<Token> &tokens);

};

#endif /* VALIDATOR_HPP_ */
