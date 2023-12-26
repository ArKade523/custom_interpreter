#include "lexer.hpp"
#include "tokens.hpp"

Token Lexer::getNextToken() {
    static std::unordered_map<std::string, TokenType> keywords = {
            {"and", TokenType::AND},
            {"class", TokenType::CLASS},
            {"else", TokenType::ELSE},
            {"false", TokenType::FALSE},
            {"for", TokenType::FOR},
            {"fun", TokenType::FUN},
            {"if", TokenType::IF},
            {"nil", TokenType::NIL},
            {"or", TokenType::OR},
            {"print", TokenType::PRINT},
            {"return", TokenType::RETURN},
            {"super", TokenType::SUPER},
            {"this", TokenType::THIS},
            {"true", TokenType::TRUE},
            {"var", TokenType::VAR},
            {"while", TokenType::WHILE}
    };

    while (this->index < this->input.length()) {
        if (std::isspace(this->input[this->index])) {
            this->index++;
            continue;
        }

        if (std::isdigit(this->input[this->index])) {
            std::string num;
            while (this->index < this->input.length() && std::isdigit(this->input[this->index])) {
                num += this->input[this->index++];
            }

            return Token(TokenType::NUMBER, num);
        }

        if (std::isalpha(this->input[this->index]) || this->input[this->index] == '_') {
            std::string identifier;
            while (this->index < this->input.length() &&
                (std::isalnum(this->input[this->index]) || this->input[this->index] == '_')) {
                identifier += this->input[this->index++];
            }

            auto keyword = keywords.find(identifier);
            if (keyword != keywords.end()) {
                return Token(keyword->second, identifier);
            }

            return Token(TokenType::IDENTIFIER, identifier);
        }

        char c = this->input[this->index++];

        switch(c) {
            case '(': return Token(TokenType::LEFT_PAREN, "(");
            case ')': return Token(TokenType::RIGHT_PAREN, ")");
            case '{': return Token(TokenType::LEFT_BRACE, "{");
            case '}': return Token(TokenType::RIGHT_BRACE, "}");
            case ',': return Token(TokenType::COMMA, ",");
            case '.': return Token(TokenType::DOT, ".");
            case '-': return Token(TokenType::MINUS, "-");
            case '+': return Token(TokenType::PLUS, "+");
            case ';': return Token(TokenType::SEMICOLON, ";");
            case '*': return Token(TokenType::STAR, "*");
            case '!': return Token(TokenType::BANG, "!");
            case '=': return Token(TokenType::EQUAL, "=");
            case '<': return Token(TokenType::LESS, "<");
            case '>': return Token(TokenType::GREATER, ">");
            case '/':
                if (this->input[this->index] == '/') {
                    while (this->index < this->input.length() && this->input[this->index] != '\n') {
                        this->index++;
                    }
                } else {
                    return Token(TokenType::SLASH, "/");
                }
                break;
            case 'v':
                if (this->input[this->index] == 'a' && this->input[this->index + 1] == 'r') {
                    this->index += 2;
                    return Token(TokenType::VAR, "var");
                }
                break;
            default:
                std::cerr << "Unexpected character at index " << this->index - 1 << ": " << c << std::endl;
                continue;
        }
    }

    return Token(TokenType::END_OF_FILE, "");
}