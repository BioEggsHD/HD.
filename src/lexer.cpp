
#include <string>
#include <vector>
#include <cctype>
#include <iostream>

enum TokenType { TOKEN_OUTPUT, TOKEN_STRING, TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_EOF };

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input) : input(input), pos(0) {}

    Token getNextToken() {
        while (pos < input.size()) {
            if (input[pos] == ' ' || input[pos] == '\n') {
                pos++;
                continue;
            }

            if (input.substr(pos, 6) == "output") {
                pos += 6;
                return Token{TOKEN_OUTPUT, "output"};
            }
            if (input[pos] == '(') {
                pos++;
                return Token{TOKEN_LPAREN, "("};
            }
            if (input[pos] == ')') {
                pos++;
                return Token{TOKEN_RPAREN, ")"};
            }
            if (input[pos] == '"') {
                return getStringLiteral();
            }
        }
        return Token{TOKEN_EOF, ""};
    }

private:
    Token getStringLiteral() {
        pos++; // skip the opening quote
        std::string str;
        while (pos < input.size() && input[pos] != '"') {
            str += input[pos++];
        }
        pos++; // skip the closing quote
        return Token{TOKEN_STRING, str};
    }

    std::string input;
    size_t pos;
};
