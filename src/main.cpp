#include <iostream>
#include <fstream>
#include <string>
#include "lexer.cpp"
#include "parser.cpp"
#include "interpreter.cpp"

int main() {
    // Read the HD-Script source code
    std::ifstream file("example.hds");
    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Create lexer to tokenize the input code
    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();

    // Parse the tokens
    Parser parser(tokens);
    parser.parse();

    // Interpret and execute the code
    Interpreter interpreter;
    interpreter.execute(tokens);

    return 0;
}
