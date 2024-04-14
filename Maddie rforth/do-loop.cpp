#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <cctype>
#include <algorithm>

enum class TokenType { Keyword, Number, Identifier, Symbol, String, End };

struct Token {
    TokenType type;
    std::string value;
};

class Node {
public:
    virtual ~Node() {}
    virtual void evaluate() = 0;
};

class PrintNode : public Node {
    int value;
public:
    PrintNode(int value) : value(value) {}
    void evaluate() override {
        std::cout << "Printing value: " << value << std::endl;
    }
};

class PrintStringNode : public Node {
    std::string value;
public:
    PrintStringNode(const std::string& value) : value(value) {}
    void evaluate() override {
        std::cout << "Printing string: " << value << std::endl;
    }
};

class LoopNode : public Node {
    int start, end;
    std::vector<std::unique_ptr<Node>> body;
public:
    LoopNode(int start, int end) : start(start), end(end) {}

    void addNode(std::unique_ptr<Node> node) {
    	std::cout << "Adding node to loop body, type: " << typeid(*node).name() << std::endl;
    	if (typeid(*node) == typeid(LoopNode)) {
        	std::cerr << "Attempting to add LoopNode to another LoopNode, which is not allowed." << std::endl;
        	return; 
    	}
    	body.push_back(std::move(node));
    }


    void evaluate() override {
        std::cout << "Starting loop evaluation from " << start << " to " << end << std::endl;
        std::cout << "Nodes in loop body:" << std::endl;
        for (const auto& node : body) {
            std::cout << "Node type: " << typeid(*node).name() << " about to evaluate." << std::endl;
        }

        for (int i = start; i < end; ++i) {
            std::cout << "Loop iteration: " << i << std::endl;
            for (auto& node : body) {
                std::cout << "Evaluating node: " << typeid(*node).name() << "..." << std::endl;
                node->evaluate();
            }
        }
        std::cout << "Ending loop evaluation from " << start << " to " << end << std::endl;
    }
};


std::unique_ptr<LoopNode> parseLoop(const std::vector<Token>& tokens, size_t& current_position, int start, int end);


std::vector<Token> getTokens(const std::string& input) {
    std::vector<Token> tokens;
    std::string currentToken;
    bool inString = false;

    for (char ch : input) {
        if (ch == '\"') { // Handle string literals
            inString = !inString;
            if (!inString) { // Closing quote
                tokens.push_back({TokenType::String, currentToken});
                currentToken.clear();
            }
            continue;
        }

        if (inString) {
            currentToken += ch;
        } else if (std::isspace(ch)) {
            if (!currentToken.empty()) {
                if (std::isdigit(currentToken[0]) || (currentToken.size() > 1 && currentToken[0] == '-' && std::isdigit(currentToken[1]))) {
                    tokens.push_back({TokenType::Number, currentToken});
                } else {
                    tokens.push_back({TokenType::Identifier, currentToken});
                }
                currentToken.clear();
            }
        } else if (std::isalnum(ch) || ch == '-') {
            currentToken += ch;
        } else {
            if (!currentToken.empty()) {
                if (std::isdigit(currentToken[0]) || (currentToken.size() > 1 && currentToken[0] == '-' && std::isdigit(currentToken[1]))) {
                    tokens.push_back({TokenType::Number, currentToken});
                } else {
                    tokens.push_back({TokenType::Identifier, currentToken});
                }
                currentToken.clear();
            }
            tokens.push_back({TokenType::Symbol, std::string(1, ch)});
        }
    }
    if (!currentToken.empty()) {
        if (std::isdigit(currentToken[0]) || (currentToken.size() > 1 && currentToken[0] == '-' && std::isdigit(currentToken[1]))) {
            tokens.push_back({TokenType::Number, currentToken});
        } else {
            tokens.push_back({TokenType::Identifier, currentToken});
        }
    }
    tokens.push_back({TokenType::End, ""});
    return tokens;
}


int safeStoi(const std::string& str) {
    if (str.empty() || !std::all_of(str.begin(), str.end(), [&str](char c) {
        return std::isdigit(c) || (c == '-' && &c == &str.front()); 
    })) {
        throw std::invalid_argument("Invalid input for stoi: " + str);
    }
    return std::stoi(str);
}


std::unique_ptr<LoopNode> parseLoop(const std::vector<Token>& tokens, size_t& current_position, int start, int end) {
    auto loopNode = std::make_unique<LoopNode>(start, end);
    std::cout << "Parsing loop body..." << std::endl;

    while (current_position < tokens.size() && tokens[current_position].value != "loop") {
        if (tokens[current_position].type == TokenType::Number) {
            int value = safeStoi(tokens[current_position].value);
            std::cout << "Adding print node with number value: " << value << std::endl;
            loopNode->addNode(std::make_unique<PrintNode>(value));
            current_position++;
        } else if (tokens[current_position].type == TokenType::String) {
            std::cout << "Adding print node with string value: " << tokens[current_position].value << std::endl;
            loopNode->addNode(std::make_unique<PrintStringNode>(tokens[current_position].value));
            current_position++;
        } else {
            current_position++; // Increment to skip unrecognized or unparsed tokens
        }
    }

    if (current_position >= tokens.size() || tokens[current_position].value != "loop") {
        throw std::runtime_error("Missing 'loop' keyword to close loop construct.");
    }
    current_position++; // Move past "loop"
    return loopNode;
}


std::unique_ptr<Node> parseFunction(const std::vector<Token>& tokens, size_t& current_position) {
    if (tokens[current_position].type != TokenType::Symbol || tokens[current_position].value != ":") {
        throw std::runtime_error("Expected ':' at the start of a function definition");
    }
    current_position++; 
    
    if (tokens[current_position].type != TokenType::Identifier) {
        throw std::runtime_error("Expected function name after ':'");
    }
    std::string functionName = tokens[current_position++].value;

    if (tokens[current_position].type != TokenType::Number) {
        throw std::runtime_error("Expected numeric end index for the loop");
    }
    int endIndex = std::stoi(tokens[current_position++].value);

    if (tokens[current_position].type != TokenType::Number) {
        throw std::runtime_error("Expected numeric start index for the loop");
    }
    int startIndex = std::stoi(tokens[current_position++].value);

    if (tokens[current_position].value != "do") {
        throw std::runtime_error("Expected 'do' keyword for starting a loop");
    }
    current_position++; 

    auto functionNode = std::make_unique<LoopNode>(startIndex, endIndex);
    functionNode->addNode(parseLoop(tokens, current_position, startIndex, endIndex));

    if (tokens[current_position].value != ";") {
        throw std::runtime_error("Function definition not properly closed with ';'");
    }
    current_position++; 
    return functionNode;
}

/*
int main() {
    std::string input = ": test 12 0 do 5 loop ;";
    //std::string input = ": test 12 0 do \"Hello\" loop ;";
    auto tokens = getTokens(input);
    size_t position = 0;
    try {
        auto ast = parseFunction(tokens, position);
        ast->evaluate();
        std::cout << "ok" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error parsing input: " << e.what() << std::endl;
    }

    return 0;
}
*/

int main() {
    LoopNode testLoop(0, 12);  // Simple loop with twelve iterations
    testLoop.addNode(std::make_unique<PrintStringNode>("Hello World"));
    testLoop.evaluate();
    return 0;
}

