#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <cctype>
#include <sstream>
#include <queue>

enum class token_type_t {
    NUMBER,
    OPERATOR,
    SYMBOL,
    WORD,
    BOOLEAN,
    ILLEGAL
};

std::map<std::string, token_type_t> create_type_map(){
    std::map<std::string, token_type_t> map;
    //operator
    map["+"] = token_type_t::OPERATOR;
    map["-"] = token_type_t::OPERATOR;
    map["*"] = token_type_t::OPERATOR;
    map["/"] = token_type_t::OPERATOR;
    map["."] = token_type_t::OPERATOR;
    map["@"] = token_type_t::OPERATOR;
    map["!"] = token_type_t::OPERATOR;

    //symbol
    map[";"] = token_type_t::SYMBOL;
    map[":"] = token_type_t::SYMBOL;

    //boolean
    map["="] = token_type_t::BOOLEAN;
    map["<"] = token_type_t::BOOLEAN;
    map[">"] = token_type_t::BOOLEAN;
    map["and"] = token_type_t::BOOLEAN;
    map["or"] = token_type_t::BOOLEAN;
    map["invert"] = token_type_t::BOOLEAN;


    return map;
    
}

bool checkDigits(std::string test){
    for (char ch: test){
        if (!isdigit(ch)){
            return false;
        }
    }
    return true;
}

std::stack<int> addition(std::stack<int>& intStack){
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = val1 + val2;
    intStack.push(val3);
    return intStack;
}

std::map<std::string, std::function<void(std::stack<int>&)>> create_func_map() {
    std::map<std::string, std::function<void(std::stack<int>&)>> funcMap;
    funcMap["+"] = addition;
    return funcMap;
}

void printStack(std::stack<int>& int_stack){
    while (!int_stack.empty()){
        std::cout << int_stack.top() << std::endl;
        int_stack.pop();
    }
}


void token_separator(std::stack<std::string> stringStack){
    std::map<std::string, token_type_t> typeMap = create_type_map();
    std::map<std::string, std::function<void(std::stack<int>&)>> funcMap = create_func_map();
    std::stack<int> intStack;
    while (!stringStack.empty()){
        std::string current = stringStack.top();
        stringStack.pop();
        if (typeMap.find(current) != typeMap.end()){
            token_type_t val = typeMap[current];
            if (val == token_type_t::SYMBOL){
                std::cout << "SYMBOL!\n";
            } else if (val == token_type_t::BOOLEAN){
                std::cout << "BOOLEAN!\n";
            } else if (val == token_type_t::OPERATOR){
                std::cout << "OPERATOR\n";
                if (funcMap.find(current) != funcMap.end()){
                    funcMap[current](intStack);
                    //std::cout << "OPERATOR\n";
                    printStack(intStack);
                    
                }
            } 
        } else if (checkDigits(current)){
                int num = std::stoi(current);
                intStack.push(num);
        }
    }
    
}

std::stack<std::string> queue_to_stack(std::queue<std::string> test_queue){
    std::stack<std::string> stack1;
    std::stack<std::string> stack2;
    while(!test_queue.empty()){
        std::string val = test_queue.front();
        stack1.push(val);
        test_queue.pop();
    }

    while (!stack1.empty()){
        stack2.push(stack1.top());
        stack1.pop();
    }
    
    return stack2;


}

int main(){

    std::string input = "10 20 +";
    std::queue<std::string> test_queue;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        test_queue.push(token);
    }

    std::stack<std::string> final_stack = queue_to_stack(test_queue);
    token_separator(final_stack);
    return 0;
}

/*

stack<int> push(int value, stack<int> my_stack){
    my_stack.push(value);
    return my_stack
}

stack<int> pop(int value, stack<int> my_stack){
    my_stack.push(value);
    return my_stack
}

stack<int> add(stack<int> my_stack){
    int num1 = my_stack.pop();
    int num2 = my_stack.pop();
    my_stack.push(num1 + num2);
    return my_stack
}

stack<int> subtract(stack<int> my_stack){
    int num1 = my_stack.pop();
    int num2 = my_stack.pop();
    my_stack.push(num1 - num2);
    return my_stack
}
*/



