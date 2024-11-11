#include <string>
#include <vector>
#include <cctype>
#include <iostream>

enum TokenType {
    TOKEN_OUTPUT,      // "output"
    TOKEN_STR,         // "str"
    TOKEN_BOOL,        // "bool"
    TOKEN_INT,         // "int"
    TOKEN_IDENTIFIER,  // Variable names
    TOKEN_STRING,      // String literals
    TOKEN_ASSIGN,      // "="
    TOKEN_LPAREN,      // "("
    TOKEN_RPAREN,      // ")"
    TOKEN_BOOL_LITERAL,// "true" or "false"
    TOKEN_INT_LITERAL, // Integer literals (e.g., 58)
    TOKEN_EOF          // End of file/input
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input) : input(input), pos(0) {}

    Token getNextToken() {
        while (pos < input.size()) {
            if (isspace(input[pos])) {
                pos++;
                continue;
            }

            // Keywords: output, str, bool, int
            if (input.substr(pos, 6) == "output" && isDelimiter(pos + 6)) {
                pos += 6;
                return Token{TOKEN_OUTPUT, "output"};
            }
            if (input.substr(pos, 3) == "str" && isDelimiter(pos + 3)) {
                pos += 3;
                return Token{TOKEN_STR, "str"};
            }
            if (input.substr(pos, 4) == "bool" && isDelimiter(pos + 4)) {
                pos += 4;
                return Token{TOKEN_BOOL, "bool"};
            }
            if (input.substr(pos, 3) == "int" && isDelimiter(pos + 3)) {
                pos += 3;
                return Token{TOKEN_INT, "int"};
            }

            // Boolean literals: true, false
            if (input.substr(pos, 4) == "true" && isDelimiter(pos + 4)) {
                pos += 4;
                return Token{TOKEN_BOOL_LITERAL, "true"};
            }
            if (input.substr(pos, 5) == "false" && isDelimiter(pos + 5)) {
                pos += 5;
                return Token{TOKEN_BOOL_LITERAL, "false"};
            }

            // Symbols: (, ), =
            if (input[pos] == '(') {
                pos++;
                return Token{TOKEN_LPAREN, "("};
            }
            if (input[pos] == ')') {
                pos++;
                return Token{TOKEN_RPAREN, ")"};
            }
            if (input[pos] == '=') {
                pos++;
                return Token{TOKEN_ASSIGN, "="};
            }

            // String literals: "text here"
            if (input[pos] == '"') {
                return getStringLiteral();
            }

            // Identifiers (variables) or integers
            if (isalpha(input[pos])) {
                return getIdentifier();
            }
            if (isdigit(input[pos])) {
                return getIntLiteral();
            }
        }
        return Token{TOKEN_EOF, ""};
    }

private:
    // Helper to check if the next character is a delimiter (non-alphanumeric or end of input)
    bool isDelimiter(size_t nextPos) {
        return nextPos >= input.size() || !isalnum(input[nextPos]);
    }

    Token getStringLiteral() {
        pos++; // Skip the opening quote
        std::string str;
        while (pos < input.size() && input[pos] != '"') {
            str += input[pos++];
        }
        pos++; // Skip the closing quote
        return Token{TOKEN_STRING, str};
    }

    Token getIdentifier() {
        std::string identifier;
        while (pos < input.size() && (isalnum(input[pos]) || input[pos] == '_')) {
            identifier += input[pos++];
        }
        return Token{TOKEN_IDENTIFIER, identifier};
    }

    Token getIntLiteral() {
        std::string number;
        while (pos < input.size() && isdigit(input[pos])) {
            number += input[pos++];
        }
        return Token{TOKEN_INT_LITERAL, number};
    }

    std::string input;
    size_t pos;
};
