#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <map>

// Enum for different token types
enum class TokenType {
    Keyword,
    Type,
    Identifier,
    Delimiter,
    Invalid,
    EndOfFile
};

// Token structure to hold each token's type and value
struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    // Constructor that takes source code
    Lexer(const std::string &source) : source(source), currentPos(0) {}

    // Tokenizer function
    std::vector<Token> tokenize() {
        std::vector<Token> tokens;

        while (currentPos < source.size()) {
            char currentChar = source[currentPos];

            // Skip whitespace
            if (isspace(currentChar)) {
                currentPos++;
                continue;
            }

            // Handle string literals
            if (currentChar == '"') {
                std::string strValue = readString();
                tokens.push_back({TokenType::Type, strValue});  // Treat as a string type for now
                continue;
            }

            // Handle integers
            if (isdigit(currentChar)) {
                std::string intValue = readNumber();
                tokens.push_back({TokenType::Type, intValue});  // Treat as an integer type for now
                continue;
            }

            // Handle the keyword "output()"
            if (currentChar == 'o' && match("output")) {
                tokens.push_back({TokenType::Keyword, "output"});
                continue;
            }

            // Handle delimiters (e.g., parentheses)
            if (currentChar == '(' || currentChar == ')') {
                tokens.push_back({TokenType::Delimiter, std::string(1, currentChar)});
                currentPos++;
                continue;
            }

            // If we reach here, the character is invalid
            tokens.push_back({TokenType::Invalid, std::string(1, currentChar)});
            currentPos++;
        }

        // Add End of File token
        tokens.push_back({TokenType::EndOfFile, ""});
        return tokens;
    }

private:
    std::string source;
    size_t currentPos;

    // Function to read a string literal
    std::string readString() {
        size_t startPos = currentPos;
        currentPos++;  // Skip the initial quote
        while (currentPos < source.size() && source[currentPos] != '"') {
            currentPos++;
        }
        currentPos++;  // Skip the closing quote
        return source.substr(startPos, currentPos - startPos);
    }

    // Function to read a number (int)
    std::string readNumber() {
        size_t startPos = currentPos;
        while (currentPos < source.size() && isdigit(source[currentPos])) {
            currentPos++;
        }
        return source.substr(startPos, currentPos - startPos);
    }

    // Function to match a string (e.g., "output")
    bool match(const std::string &str) {
        if (currentPos + str.size() <= source.size()) {
            return source.substr(currentPos, str.size()) == str;
        }
        return false;
    }
};

int main() {
    // Example HD-Script input code
    std::string code = R"(
        output("Hello, World!")
        output(42)
    )";

    // Initialize lexer and tokenize input code
    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();

    // Print tokens for debugging
    for (const Token &token : tokens) {
        std::string tokenType;
        switch (token.type) {
            case TokenType::Keyword:
                tokenType = "Keyword";
                break;
            case TokenType::Type:
                tokenType = "Type";
                break;
            case TokenType::Identifier:
                tokenType = "Identifier";
                break;
            case TokenType::Delimiter:
                tokenType = "Delimiter";
                break;
            case TokenType::Invalid:
                tokenType = "Invalid";
                break;
            case TokenType::EndOfFile:
                tokenType = "EndOfFile";
                break;
        }
        std::cout << tokenType << ": " << token.value << std::endl;
    }

    return 0;
}
