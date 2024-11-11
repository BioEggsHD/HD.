
#include "lexer.cpp"  // Include the lexer
#include <memory>

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct OutputNode : public ASTNode {
    std::string message;
    OutputNode(const std::string& msg) : message(msg) {}
};

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer) {}

    std::unique_ptr<ASTNode> parse() {
        Token token = lexer.getNextToken();
        if (token.type == TOKEN_OUTPUT) {
            if (lexer.getNextToken().type == TOKEN_LPAREN) {
                Token stringToken = lexer.getNextToken();
                if (stringToken.type == TOKEN_STRING) {
                    if (lexer.getNextToken().type == TOKEN_RPAREN) {
                        return std::make_unique<OutputNode>(stringToken.value);
                    }
                }
            }
        }
        return nullptr; // Return null if parsing fails
    }

private:
    Lexer& lexer;
};
