#include <iostream>
#include <vector>
#include <string>

class Parser {
public:
    Parser(std::vector<Token> tokens) : tokens(tokens), currentTokenIndex(0) {}

    void parse() {
        while (currentTokenIndex < tokens.size()) {
            Token currentToken = tokens[currentTokenIndex];

            if (currentToken.type == TokenType::Keyword && currentToken.value == "function") {
                parseFunction();
            } else if (currentToken.type == TokenType::Keyword && currentToken.value == "output") {
                parseOutput();
            } else {
                currentTokenIndex++;
            }
        }
    }

private:
    std::vector<Token> tokens;
    size_t currentTokenIndex;

    void parseFunction() {
        std::cout << "Parsing function..." << std::endl;
        currentTokenIndex++;  // Skip "function" keyword
        Token nameToken = tokens[currentTokenIndex++];
        std::cout << "Function name: " << nameToken.value << std::endl;
        
        // Further parsing logic would go here...
    }

    void parseOutput() {
        std::cout << "Parsing output..." << std::endl;
        currentTokenIndex++;  // Skip "output" keyword

        // Parse the expression to output
        Token exprToken = tokens[currentTokenIndex++];
        std::cout << "Output expression: " << exprToken.value << std::endl;
    }
};

