#include "interpreter.cpp" // Include the interpreter, which includes the parser and lexer

int main() {
    // Example input for testing: includes variable assignments and an output statement
    std::string input = R"(
        str myVar = "Hello, Interpreter!"
        bool myVar2 = true
        int myVar3 = 42
        output("Execution successful!")
    )";

    // Initialize lexer, parser, and interpreter
    Lexer lexer(input);
    Parser parser(lexer);
    Interpreter interpreter;

    // Parse and interpret each statement in the input
    while (true) {
        auto astNode = parser.parse();
        if (!astNode) break; // Stop if there is nothing left to parse
        interpreter.interpret(astNode);
    }

    // Test by printing variable values (these will be retrieved from the symbol table)
    std::cout << "Value of myVar: ";
    interpreter.printVariable("myVar");

    std::cout << "Value of myVar2: ";
    interpreter.printVariable("myVar2");

    std::cout << "Value of myVar3: ";
    interpreter.printVariable("myVar3");

    return 0;
}

