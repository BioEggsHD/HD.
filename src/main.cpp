#include "interpreter.cpp" // Include the interpreter

int main() {
    std::string input = R"(output("Hello, World!"))";
    Lexer lexer(input);
    Parser parser(lexer);
    auto ast = parser.parse();

    if (ast) {
        Interpreter interpreter;
        interpreter.interpret(ast);
    } else {
        std::cerr << "Syntax error!" << std::endl;
    }

    return 0;
}

