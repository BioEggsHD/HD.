
#include "parser.cpp" // Include the parser

class Interpreter {
public:
    void interpret(const std::unique_ptr<ASTNode>& node) {
        if (auto outputNode = dynamic_cast<OutputNode*>(node.get())) {
            std::cout << outputNode->message << std::endl;
        }
    }
};
