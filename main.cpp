#include <string>
#include <sstream>
#include <fstream>
#include "lexer.hpp"
#include "tokens.hpp"

std::string readFileContents(const std::string& filePath) {
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}

void writeStringstreamToFile(const std::stringstream& ss, const std::string& filePath) {
    std::ofstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    fileStream << ss.str();
}

std::string convertTokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::MINUS: return "MINUS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::SLASH: return "SLASH";
        case TokenType::STAR: return "STAR";
        case TokenType::BANG: return "BANG";
        case TokenType::BANG_EQUAL: return "BANG_EQUAL";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::AND: return "AND";
        case TokenType::CLASS: return "CLASS";
        case TokenType::ELSE: return "ELSE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::FUN: return "FUN";
        case TokenType::FOR: return "FOR";
        case TokenType::IF: return "IF";
        case TokenType::NIL: return "NIL";
        case TokenType::OR: return "OR";
        case TokenType::PRINT: return "PRINT";
        case TokenType::RETURN: return "RETURN";
        case TokenType::SUPER: return "SUPER";
        case TokenType::THIS: return "THIS";
        case TokenType::TRUE: return "TRUE";
        case TokenType::VAR: return "VAR";
        case TokenType::WHILE: return "WHILE";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
    }

    return "";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.calc> <output.txt>\n";
        return EXIT_FAILURE;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::string input = readFileContents(inputFile);


    Lexer lexer(input);

    Token token = lexer.getNextToken();
    std::stringstream lexeroutput; 
    while (token.type != TokenType::END_OF_FILE) {
        lexeroutput << convertTokenTypeToString(token.type) << " ";
        token = lexer.getNextToken();
    }

    writeStringstreamToFile(lexeroutput, outputFile);

    return EXIT_SUCCESS;
}