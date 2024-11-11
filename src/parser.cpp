#include "lexer.cpp"  // Include the lexer
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>

// Abstract Syntax Tree Node Base Class
struct ASTNode {
    virtual ~ASTNode() = default;
};

// AST Node for output statements like output("Hello, World!")
struct OutputNode : public ASTNode {
    std::string message;
    OutputNode(const std::string& msg) : message(msg) {}
};

// AST Node for variable assignment, handles str, bool, and int assignments
struct VarAssignNode : public ASTNode {
    std::string varType;
    std::string varName;
    std::string value;
    
    VarAssignNode(const std::string& type, const std::string& name, const std::string& val)
        : varType(type), varName(name), value(val) {}
};

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer) {}

    std::unique_ptr<ASTNode> parse() {
        Token token = lexer.getNextToken();
        if (token.type == TOKEN_OUTPUT) {
            return parseOutput();
        }
        else if (token.type == TOKEN_STR || token.type == TOKEN_BOOL || token.type == TOKEN_INT) {
            return parseVarAssignment(token);
        }
        return nullptr; // Return null if parsing fails
    }

private:
    Lexer& lexer;

    // Parse output statement, e.g., output("Hello, World!")
    // Parse output statement, e.g., output(var)
std::unique_ptr<ASTNode> parseOutput() {
    if (lexer.getNextToken().type == TOKEN_LPAREN) {
        Token token = lexer.getNextToken();
        if (token.type == TOKEN_IDENTIFIER) {  // Check if it's a variable (identifier)
            return std::make_unique<OutputNode>(token.value);  // Store variable name
        } else if (token.type == TOKEN_STRING) {  // If it's a string literal
            return std::make_unique<OutputNode>(token.value);  // Store string value
        }
    }
    return nullptr;
}


    // Parse variable assignment, e.g., str myVar = "abc", bool myVar2 = false, int myVar3 = 58
    std::unique_ptr<ASTNode> parseVarAssignment(const Token& typeToken) {
        Token identifier = lexer.getNextToken();
        if (identifier.type == TOKEN_IDENTIFIER) {
            Token assign = lexer.getNextToken();
            if (assign.type == TOKEN_ASSIGN) {
                Token valueToken = lexer.getNextToken();
                
                // Validate based on variable type (str, bool, int)
                if ((typeToken.type == TOKEN_STR && valueToken.type == TOKEN_STRING) ||
                    (typeToken.type == TOKEN_BOOL && valueToken.type == TOKEN_BOOL_LITERAL) ||
                    (typeToken.type == TOKEN_INT && valueToken.type == TOKEN_INT_LITERAL)) {
                    
                    return std::make_unique<VarAssignNode>(typeToken.value, identifier.value, valueToken.value);
                }
            }
        }
        return nullptr;
    }
};
