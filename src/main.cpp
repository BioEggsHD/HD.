#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.cpp"
#include "parser.cpp"
#include "interpreter.cpp"

int main() {
    // Example HD-Script code as a string
    std::string code = R"(
        output("Hello, World!")
        output(42)
    )";

    // Initialize lexer and tokenize the code
    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();

    // Initialize parser and parse the tokens
    Parser parser(tokens);
    parser.parse();

    // Initialize interpreter and interpret the parsed tokens
    Interpreter interpreter(tokens);
    interpreter.interpret();

    return 0;
}
