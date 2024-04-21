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

    int getValue() const { return value; } 

    void evaluate() override {
        //std::cout << "Evaluating PrintNode with value: " << value << std::endl;
        std::cout << value << std::endl;
        std::cout.flush(); 
    }
};


class PrintStringNode : public Node {
    std::string value;
public:
    PrintStringNode(const std::string& value) : value(value) {}

    const std::string& getValue() const { return value; } 

    void evaluate() override {
        //std::cout << "Evaluating PrintStringNode with string: " << value << std::endl;
        std::cout << value << std::endl;
        std::cout.flush();  
    }
};


class LoopNode : public Node {
    int start, end;
    std::vector<std::unique_ptr<Node>> body;
public:
    LoopNode(int start, int end) : start(start), end(end) {}

    void addNode(std::unique_ptr<Node> node) {
        //std::cout << "Attempting to add node of type: " << typeid(*node).name() << std::endl;
        // Check if the type is exactly LoopNode and disallow if it's the same as this
        if (node.get() == this) {
            //std::cerr << "Attempt to add LoopNode to itself blocked." << std::endl;
        } else {
            //std::cout << "LoopNode address in addNode: " << this << std::endl;
            body.push_back(std::move(node));
            //std::cout << "Node added. Current body size: " << body.size() << std::endl;
        }
    }



    void evaluate() override {
        //std::cout << "LoopNode address in evaluate: " << this << std::endl;
        std::cout << "Starting loop evaluation from " << start << " to " << end << std::endl;
        if (body.empty()) {
            std::cout << "Warning: No nodes to evaluate in loop body." << std::endl;
        }
        for (int i = start; i < end; ++i) {
            //std::cout << "Loop iteration: " << i << std::endl;
            for (auto& node : body) {
                node->evaluate();
           }
        }
        std::cout << "Ending loop evaluation from " << start << " to " << end << std::endl;
    }

    void transferNodesFrom(std::unique_ptr<LoopNode>& source) {
        while (!source->body.empty()) {
            addNode(std::move(source->body.back()));
            source->body.pop_back();
        }
    }

};

std::vector<Token> getTokens(const std::string& input) {
    std::vector<Token> tokens;
    std::string currentToken;
    bool inString = false;

    for (char ch : input) {
        if (ch == '\"') {
            inString = !inString;
            if (!inString) {
                tokens.push_back({TokenType::String, currentToken});
                currentToken.clear();
            }
            continue;
        }

        if (inString) {
            currentToken += ch;
        } else if (std::isspace(ch) || ch == ';' || ch == ':') {
            if (!currentToken.empty()) {
                TokenType type = std::isdigit(currentToken[0]) ? TokenType::Number : TokenType::Identifier;
                tokens.push_back({type, currentToken});
                currentToken.clear();
            }
            if (ch == ';' || ch == ':') {
                tokens.push_back({TokenType::Symbol, std::string(1, ch)});
            }
        } else if (std::isalnum(ch) || ch == '-') {
            currentToken += ch;
        } else {
            if (!currentToken.empty()) {
                TokenType type = std::isdigit(currentToken[0]) ? TokenType::Number : TokenType::Identifier;
                tokens.push_back({type, currentToken});
                currentToken.clear();
            }
            tokens.push_back({TokenType::Symbol, std::string(1, ch)});
        }
    }

    if (!currentToken.empty()) {
        TokenType type = std::isdigit(currentToken[0]) ? TokenType::Number : TokenType::Identifier;
        tokens.push_back({type, currentToken});
    }
    tokens.push_back({TokenType::End, ""});
    return tokens;
}


int safeStoi(const std::string& str) {
    try {
        if (str.empty() || !std::all_of(str.begin(), str.end(), [](char c) { return std::isdigit(c) || c == '-'; })) {
            throw std::invalid_argument("Invalid input for stoi: " + str);
        }
        return std::stoi(str);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument for stoi with input '" << str << "': " << e.what() << std::endl;
        throw;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range error for stoi with input '" << str << "': " << e.what() << std::endl;
        throw;
    }
}

std::unique_ptr<LoopNode> parseLoop(const std::vector<Token>& tokens, size_t& current_position, int start, int end) {
    auto loopNode = std::make_unique<LoopNode>(start, end);
    //std::cout << "Parsing loop body from position " << current_position << " with new LoopNode at: " << loopNode.get() << std::endl;

    while (current_position < tokens.size() && tokens[current_position].value != "loop") {
        const auto& token = tokens[current_position];

        if (token.type == TokenType::Number) {
            int value = safeStoi(token.value);
            //std::cout << "Adding print node with number value: " << value << std::endl;
            loopNode->addNode(std::make_unique<PrintNode>(value));
        } else if (token.type == TokenType::String) {
            //std::cout << "Adding print node with string value: " << token.value << std::endl;
            loopNode->addNode(std::make_unique<PrintStringNode>(token.value));
        }
        current_position++;
    }

    if (current_position >= tokens.size() || tokens[current_position].value != "loop") {
        //std::cerr << "Error: Loop not properly terminated with 'loop' keyword at position " << current_position << std::endl;
        throw std::runtime_error("Missing 'loop' keyword to close loop construct.");
    }
    current_position++; // Move past the 'loop' token

    //std::cout << "Ending loop body parsing at position " << current_position << std::endl;
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
    auto nestedLoopNode = parseLoop(tokens, current_position, startIndex, endIndex);

    functionNode->transferNodesFrom(nestedLoopNode);

    if (tokens[current_position].value != ";") {
        throw std::runtime_error("Function definition not properly closed with ';'");
    }
    current_position++;
    return functionNode;
}

void testNodes() {
    // Test each node type
    PrintNode pn(5);
    PrintStringNode psn("Hello there");
    pn.evaluate(); // Should print "Printing value: 5"
    psn.evaluate(); // Should print "Printing string: Hello"
}

int main() {
    testNodes();
    std::string input = ": test 10 0 do \"This is a string in the body of the loop\" loop ;";
    //std::string input = ": test 10 0 do 52 34 68 loop ;";

    auto tokens = getTokens(input);

    // Display each token and its type
    for (const auto& token : tokens) {
        std::cout << "Token: \"" << token.value << "\" Type: " << static_cast<int>(token.type) << std::endl;
    }

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


/*
int main() {
    LoopNode testLoop(0, 12);  // Simple loop with twelve iterations
    testLoop.addNode(std::make_unique<PrintStringNode>("Hello World"));
    testLoop.evaluate();
    return 0;
}
*/


