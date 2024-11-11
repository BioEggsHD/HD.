#include <iostream>
#include <string>
#include <map>

class Interpreter {
public:
    void execute(std::vector<Token> tokens) {
        for (Token token : tokens) {
            if (token.type == TokenType::Keyword && token.value == "output") {
                // For simplicity, just output the next token (expression)
                std::cout << token.value << std::endl;
            }
        }
    }
};
