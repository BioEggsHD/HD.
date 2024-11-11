#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

enum class TokenType {
    Keyword,
    Type,
    Identifier,
    Delimiter,
    Invalid,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;
};

class Parser {
public:
    Parser(std::vector<Token> tokens) : tokens(tokens), currentTokenIndex(0) {}

    // Main parsing function
    void parse() {
        while (currentTokenIndex < tokens.size()) {
            Token currentToken = tokens[currentTokenIndex];
            
            if (currentToken.type == TokenType::Keyword && currentToken.value == "output") {
                parseOutput();
            }
            else {
                currentTokenIndex++;
            }
        }
    }

private:
    std::vector<Token> tokens;
    size_t currentTokenIndex;

    // Parse an output command
    void parseOutput() {
        currentTokenIndex++;  // Skip the "output" keyword

        // Expect an opening parenthesis after output()
        if (tokens[currentTokenIndex].value != "(") {
            std::cerr << "Expected '(' after output, but got " << tokens[currentTokenIndex].value << std::endl;
            return;
        }

        currentTokenIndex++;  // Skip the "("

        // Get the argument for the output
        Token argToken = tokens[currentTokenIndex];

        // Check if it's a valid argument (either a string or an integer)
        if (argToken.type == TokenType::Type) {
            if (isString(argToken)) {
                std::cout << "Output (String): " << argToken.value << std::endl;
            } 
            else if (isInt(argToken)) {
                std::cout << "Output (Int): " << argToken.value << std::endl;
            }
            else {
                std::cerr << "Invalid argument type in output: " << argToken.value << std::endl;
            }
        } 
        else {
            std::cerr << "Invalid argument in output: " << argToken.value << std::endl;
        }

        currentTokenIndex++;  // Skip the argument token

        // Expect a closing parenthesis after the argument
        if (tokens[currentTokenIndex].value != ")") {
            std::cerr << "Expected ')' after output argument, but got " << tokens[currentTokenIndex].value << std::endl;
        }
        currentTokenIndex++;  // Skip the ")"
    }

    // Check if the token represents a string
    bool isString(const Token& token) {
        return token.value.front() == '"' && token.value.back() == '"';
    }

    // Check if the token represents an integer
    bool isInt(const Token& token) {
        for (char c : token.value) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }
};
