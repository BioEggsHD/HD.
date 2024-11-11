#include <iostream>
#include <vector>
#include <string>

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

class Interpreter {
public:
    // Constructor that accepts the parsed tokens
    Interpreter(std::vector<Token> tokens) : tokens(tokens), currentTokenIndex(0) {}

    // Main function to start interpreting the tokens
    void interpret() {
        while (currentTokenIndex < tokens.size()) {
            Token currentToken = tokens[currentTokenIndex];

            if (currentToken.type == TokenType::Keyword && currentToken.value == "output") {
                interpretOutput();
            } else {
                currentTokenIndex++;
            }
        }
    }

private:
    std::vector<Token> tokens;
    size_t currentTokenIndex;

    // Function to interpret the output command
    void interpretOutput() {
        currentTokenIndex++;  // Skip the "output" keyword

        // Expect an opening parenthesis after output()
        if (tokens[currentTokenIndex].value != "(") {
            std::cerr << "Error: Expected '(' after output, but got " << tokens[currentTokenIndex].value << std::endl;
            return;
        }

        currentTokenIndex++;  // Skip the "("

        // Get the argument for the output
        Token argToken = tokens[currentTokenIndex];

        // Handle different types of arguments
        if (argToken.type == TokenType::Type) {
            if (isString(argToken)) {
                std::cout << argToken.value << std::endl;  // Output string
            } else if (isInt(argToken)) {
                std::cout << argToken.value << std::endl;  // Output integer
            } else {
                std::cerr << "Error: Invalid argument type in output: " << argToken.value << std::endl;
            }
        } else {
            std::cerr << "Error: Invalid argument in output: " << argToken.value << std::endl;
        }

        currentTokenIndex++;  // Skip the argument token

        // Expect a closing parenthesis after the argument
        if (tokens[currentTokenIndex].value != ")") {
            std::cerr << "Error: Expected ')' after output argument, but got " << tokens[currentTokenIndex].value << std::endl;
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
