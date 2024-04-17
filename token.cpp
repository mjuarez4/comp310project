#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <cctype>
#include <sstream>
#include <queue>
#include <optional>
#include "int_stack.h"
#include "token.hpp"

std::map<std::string, token_type_t> create_type_map(){
    std::map<std::string, token_type_t> map;
    //operator
    map["+"] = token_type_t::OPERATOR;
    map["-"] = token_type_t::OPERATOR;
    map["*"] = token_type_t::OPERATOR;
    map["/"] = token_type_t::OPERATOR;
    map["."] = token_type_t::OPERATOR;
    map["dup"] = token_type_t::OPERATOR;
    map["swap"] = token_type_t::OPERATOR;
    map["over"] = token_type_t::OPERATOR;
    map["rot"] = token_type_t::OPERATOR;
    map["2swap"] = token_type_t::OPERATOR;
    map["2dup"] = token_type_t::OPERATOR;
    map["2over"] = token_type_t::OPERATOR;
    map["mod"] = token_type_t::OPERATOR;
    map["/mod"] = token_type_t::OPERATOR;

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

    //word
    map["variable"] = token_type_t::WORD;
    map["@"] = token_type_t::WORD;
    map["!"] = token_type_t::WORD;

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


std::map<std::string, int> variable_map;

void make_variable(std::stack<std::string>& str_stack) {
    while (!str_stack.empty()) {
        std::string val1 = str_stack.top();
        str_stack.pop();
        variable_map[val1] = 0;
    }

    //std::cout<<variable_map["bean"]<<std::endl;

}

std::map<std::string, std::function<void(std::stack<int>&)>> create_func_map_int() {
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
    funcMap["/mod"] = div_mod;
    //funcMap["@"] = address;
    //funcMap["variable"] = variable;

    return funcMap;
}

std::map<std::string, std::function<void(std::stack<std::string>&)>> create_func_map_str() {
    std::map<std::string, std::function<void(std::stack<std::string>&)>> func_str_map;
    func_str_map["variable"] = make_variable;
    return func_str_map;
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


void token_separator(std::stack<std::string> stringStack, std::queue<std::string> stringQueue){
    std::map<std::string, token_type_t> typeMap = create_type_map();
    std::map<std::string, std::function<void(std::stack<int>&)>> funcMap = create_func_map_int();
    std::map<std::string, std::function<void(std::stack<std::string>&)>> func_str_map = create_func_map_str();
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
            } else if (typeMap[current] == token_type_t::WORD){
                std::cout<< "hello" <<std::endl;
                if (stringQueue.back() == "!"){
                    std::cout << "uhoh" << std::endl;
                }

                //checks for instance of "variable", if so create variable
                if (func_str_map.find(current) != func_str_map.end()){
                    std::cout << "Calling function for: " << current << std::endl;
                    func_str_map[current](stringStack);
                    
                }

                if (stringQueue.back() == "@") {
                    std::string var1 = stringQueue.front();
                    stringQueue.pop();

                    auto it = variable_map.find(var1);
                    if (it != variable_map.end()){
                        const std::string* key_address = &(it->first);
                        std::cout<<key_address<<std::endl;
                    }

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

/*
int main(){ 

    std::string input = "variable bean";
    std::queue<std::string> test_queue;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        test_queue.push(token);
    }

    std::stack<std::string> final_stack = queue_to_stack(test_queue);
    token_separator(final_stack, test_queue);

    std::string input2 = "bean @";
    std::queue<std::string> test_queue2;
    test_queue2.push("bean");
    test_queue2.push("@");
    //std::cout<<test_queue2.back()<<std::endl;
    std::stack<std::string> final_stack2 = queue_to_stack(test_queue2);
    token_separator(final_stack2, test_queue2);
    return 0;
}
*/





