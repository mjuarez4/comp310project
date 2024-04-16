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
    map["variable"] = token_type_t::OPERATOR;
    map["dup"] = token_type_t::OPERATOR;
    map["swap"] = token_type_t::OPERATOR;
    map["over"] = token_type_t::OPERATOR;
    map["rot"] = token_type_t::OPERATOR;
    map["2swap"] = token_type_t::OPERATOR;
    map["2dup"] = token_type_t::OPERATOR;
    map["2over"] = token_type_t::OPERATOR;
    map["mod"] = token_type_t::OPERATOR;
    map["divmod"] = token_type_t::OPERATOR;

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
    int val3 = val2 + val1;
    intStack.push(val3);
    return intStack;
}

std::stack<int> subtraction(std::stack<int>& intStack){
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = val2 - val1;
    intStack.push(val3);
    return intStack;
}

std::stack<int> multiplication(std::stack<int>& intStack){
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = val2 * val1;
    intStack.push(val3);
    return intStack;
}

std::stack<int> division (std::stack<int>& intStack){
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = val2 / val1;
    intStack.push(val3);
    return intStack;
}

std::stack<int> pop_item(std::stack<int>& intStack){
    intStack.pop();
    return intStack;
}

std::stack<int> dup(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    intStack.push(val1);
    intStack.push(val1);
    return intStack;
}

std::stack<int> swap(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();

    intStack.push(val1);
    intStack.push(val2);
    return intStack;
}

std::stack<int> over(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }

    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();

    intStack.push(val2);
    intStack.push(val1);
    intStack.push(val2);
    return intStack;
}

std::stack<int> rot(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = intStack.top();
    intStack.pop();

    intStack.push(val2);
    intStack.push(val1);
    intStack.push(val3);
    return intStack;
}

std::stack<int> two_swap(std::stack<int>& intStack){
    if (intStack.size() < 4){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = intStack.top();
    intStack.pop();
    int val4 = intStack.top();
    intStack.pop();

    intStack.push(val2);
    intStack.push(val1);
    intStack.push(val4);
    intStack.push(val3);
    return intStack;
}

std::stack<int> two_over(std::stack<int>& intStack){
    if (intStack.size() < 4){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = intStack.top();
    intStack.pop();
    int val4 = intStack.top();
    intStack.pop();

    intStack.push(val4);
    intStack.push(val3);
    intStack.push(val2);
    intStack.push(val1);
    intStack.push(val4);
    intStack.push(val3);
    return intStack;
}

std::stack<int> two_dup(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();

    intStack.push(val2);
    intStack.push(val1);
    intStack.push(val2);
    intStack.push(val1);
    return intStack;
}

std::stack<int> mod(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();

    int mod = val2 % val1;
    intStack.push(mod);
    return intStack;
}


std::stack<int> div_mod(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }

    std::cout << intStack.top() << std::endl;
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();

    int rem = val2 % val1;
    int quot = val1 / val2;
    intStack.push(rem);
    intStack.push(quot);
    return intStack;
}



std::map<std::string, std::function<void(std::stack<int>&)>> create_func_map() {
    std::map<std::string, std::function<void(std::stack<int>&)>> funcMap;
    funcMap["+"] = addition;
    funcMap["-"] = subtraction;
    funcMap["*"] = multiplication;
    funcMap["/"] = division;
    funcMap["."] = pop_item;
    funcMap["dup"] = dup;
    funcMap["swap"] = swap;
    funcMap["over"] = over;
    funcMap["rot"] = rot;
    funcMap["2swap"] = two_swap;
    funcMap["2dup"] = two_dup;
    funcMap["2over"] = two_over;
    funcMap["mod"] = mod;
    funcMap["divmod"] = div_mod;

    return funcMap;
}

void printStack(std::stack<int>& int_stack) {
    std::stack<int> stack1;
    while (!int_stack.empty()){
        stack1.push(int_stack.top());
        int_stack.pop();
    }

    while (!stack1.empty()) {
        std::cout << stack1.top() << " ";  
        stack1.pop();
    }
    std::cout << std::endl;  
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

    std::string input = "10 20 divmod";
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



