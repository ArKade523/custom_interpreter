#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <unordered_map>
#include "tokens.hpp"

class Lexer {
    private:
        std::string input;
        size_t index = 0;

    public:
        explicit Lexer(std::string input) : input(std::move(input)) {}

        Token getNextToken();

};


#endif // LEXER_HPP
