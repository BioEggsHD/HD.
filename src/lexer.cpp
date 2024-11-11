// Add function-related tokens to the token enumeration
enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_FUNCTION,
    TOKEN_INT,
    TOKEN_STR,
    TOKEN_BOOL,
    TOKEN_ASSIGN,
    TOKEN_STRING,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_RETURN,
    TOKEN_PASS,
    TOKEN_INT_LITERAL,
    TOKEN_BOOL_LITERAL,
    TOKEN_EOF,
    TOKEN_COMMENT,
    TOKEN_ARGS,
    TOKEN_TYPE,
    // More tokens as needed...
};

// Lexer to handle function definition syntax
class Lexer {
public:
    Lexer(const std::string& input) : input(input), index(0) {}

    Token getNextToken() {
        // Skip comments
        if (input.substr(index, 2) == "**") {
            while (index < input.size() && input[index] != '\n') {
                index++;
            }
            return getNextToken();  // Skip the comment line and get the next token
        }

        // Handle function declaration "function blabla: <int, args: {int num1, int num2}>"
        if (input.substr(index, 8) == "function") {
            index += 8;
            skipWhitespace();
            return {TOKEN_FUNCTION, "function"};
        }

        // Handle return type (e.g., <int, args: {int num1, int num2}>)
        if (input[index] == '<') {
            index++;
            skipWhitespace();
            return {TOKEN_TYPE, "type"}; // Placeholder for handling specific types like int, str, etc.
        }

        // Handle arguments inside curly braces {int num1, int num2}
        if (input[index] == '{') {
            index++;
            skipWhitespace();
            return {TOKEN_ARGS, "args"};
        }

        // Handle function name (identifier)
        if (isalpha(input[index])) {
            size_t start = index;
            while (isalnum(input[index])) index++;
            return {TOKEN_IDENTIFIER, input.substr(start, index - start)};
        }

        // Handle literals, operators, etc.
        if (isdigit(input[index])) {
            size_t start = index;
            while (isdigit(input[index])) index++;
            return {TOKEN_INT_LITERAL, input.substr(start, index - start)};
        }

        if (input[index] == '(') {
            index++;
            return {TOKEN_LPAREN, "("};
        }

        if (input[index] == ')') {
            index++;
            return {TOKEN_RPAREN, ")"};
        }

        if (input[index] == ':') {
            index++;
            return {TOKEN_COLON, ":"};
        }

        if (input[index] == ',') {
            index++;
            return {TOKEN_COMMA, ","};
        }

        if (input.substr(index, 4) == "pass") {
            index += 4;
            skipWhitespace();
            return {TOKEN_PASS, "pass"};
        }

        if (input[index] == '\0') {
            return {TOKEN_EOF, ""}; // End of input
        }

        // Skip any unrecognized characters for now
        index++;
        return getNextToken();
    }

private:
    std::string input;
    size_t index;

    void skipWhitespace() {
        while (index < input.size() && isspace(input[index])) {
            index++;
        }
    }
};
