#include <iostream>
#include <string>
#include <vector>
#include <cctype>

enum class TokenType {
    Keyword, Type, Identifier, Operator, Number, String, Delimiter, EndOfFile, Invalid
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string &source) : source(source), currentPos(0) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;

        while (currentPos < source.size()) {
            char currentChar = source[currentPos];

            if (isspace(currentChar)) {
                currentPos++;
                continue;
            }

            if (isalpha(currentChar)) {
                std::string identifier = readIdentifier();
                tokens.push_back({TokenType::Identifier, identifier});
            }
            else if (isdigit(currentChar)) {
                std::string number = readNumber();
                tokens.push_back({TokenType::Number, number});
            }
            else if (currentChar == '+') {
                tokens.push_back({TokenType::Operator, "+"});
                currentPos++;
            }
            else if (currentChar == '-') {
                tokens.push_back({TokenType::Operator, "-"});
                currentPos++;
            }
            else if (currentChar == '=') {
                tokens.push_back({TokenType::Operator, "="});
                currentPos++;
            }
            else if (currentChar == '(' || currentChar == ')') {
                tokens.push_back({TokenType::Delimiter, std::string(1, currentChar)});
                currentPos++;
            } 
            else {
                tokens.push_back({TokenType::Invalid, std::string(1, currentChar)});
                currentPos++;
            }
        }

        tokens.push_back({TokenType::EndOfFile, ""});
        return tokens;
    }

private:
    std::string source;
    size_t currentPos;

    std::string readIdentifier() {
        size_t startPos = currentPos;
        while (currentPos < source.size() && isalnum(source[currentPos])) {
            currentPos++;
        }
        return source.substr(startPos, currentPos - startPos);
    }

    std::string readNumber() {
        size_t startPos = currentPos;
        while (currentPos < source.size() && isdigit(source[currentPos])) {
            currentPos++;
        }
        return source.substr(startPos, currentPos - startPos);
    }
};

