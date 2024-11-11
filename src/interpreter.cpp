#include "parser.cpp" // Include the parser and lexer
#include <unordered_map>
#include <iostream>
#include <string>
#include <memory>
#include <variant>

// Type alias for variable values: a variant to hold string, boolean, or integer values
using VarValue = std::variant<std::string, bool, int>;

class Interpreter {
public:
    void interpret(const std::unique_ptr<ASTNode>& node) {
        // Check the type of node and handle accordingly
        if (auto outputNode = dynamic_cast<OutputNode*>(node.get())) {
            executeOutput(outputNode);
        } 
        else if (auto varAssignNode = dynamic_cast<VarAssignNode*>(node.get())) {
            executeVarAssignment(varAssignNode);
        }
    }

    // Method to retrieve and print a variable's value (for testing purposes)
    void printVariable(const std::string& varName) const {
        auto it = symbolTable.find(varName);
        if (it != symbolTable.end()) {
            std::visit([](const auto& val) { std::cout << val << std::endl; }, it->second);
        } else {
            std::cout << "Variable '" << varName << "' is undefined." << std::endl;
        }
    }

private:
    // Symbol table to store variable names and their values
    std::unordered_map<std::string, VarValue> symbolTable;

    // Execute an output statement
    void executeOutput(OutputNode* outputNode) {
    // If it's a variable, resolve it from the symbol table
    if (symbolTable.find(outputNode->message) != symbolTable.end()) {
        // Retrieve the value from the symbol table
        std::visit([](const auto& val) { std::cout << val << std::endl; }, symbolTable[outputNode->message]);
    } else {
        // Otherwise, treat it as a string literal and print it
        std::cout << outputNode->message << std::endl;
    }
}


    // Execute a variable assignment, storing the variable in the symbol table
    void executeVarAssignment(VarAssignNode* varAssignNode) {
        // Determine the type and store the value accordingly
        if (varAssignNode->varType == "str") {
            symbolTable[varAssignNode->varName] = varAssignNode->value;
        } 
        else if (varAssignNode->varType == "bool") {
            // Convert "true" and "false" strings to boolean values
            symbolTable[varAssignNode->varName] = (varAssignNode->value == "true");
        } 
        else if (varAssignNode->varType == "int") {
            // Convert string to integer
            symbolTable[varAssignNode->varName] = std::stoi(varAssignNode->value);
        }
    }
};
