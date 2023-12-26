#ifndef PARSER_HPP
#define PARSER_HPP
#include "tokens.hpp"
#include <vector>

class Parser {
    private:
        std::vector<Token> tokens;
        size_t index = 0;

    public:
        explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

        void parse();
};

#endif // PARSER_HPP