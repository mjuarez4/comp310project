#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <cctype>
#include <sstream>
#include <queue>
#include <optional>
#include <vector>
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
std::stack<int> intStack;

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
    std::stack<int> temp_stack;
    std::vector<int> items;

    // Transfer elements from the original stack to a temporary stack
    while (!int_stack.empty()) {
        temp_stack.push(int_stack.top());
        int_stack.pop();
    }

    // Transfer elements back to the original stack and collect them for output
    while (!temp_stack.empty()) {
        int top_element = temp_stack.top();
        items.push_back(top_element);  // Collect elements in reverse order
        int_stack.push(top_element);
        temp_stack.pop();
    }

    // Print the collected elements in the desired format
    std::cout << "Stack: [";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << items[i];
    }
    std::cout << "] <- Top" << std::endl;
}


void token_separator(std::stack<std::string> stringStack, std::queue<std::string> stringQueue){
    std::map<std::string, token_type_t> typeMap = create_type_map();
    std::map<std::string, std::function<void(std::stack<int>&)>> funcMap = create_func_map_int();
    std::map<std::string, std::function<void(std::stack<std::string>&)>> func_str_map = create_func_map_str();
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
                    //printStack(intStack);
                    
                }
            } else if (typeMap[current] == token_type_t::WORD){
                //std::cout<< "hello" <<std::endl;
                //this is to add value to variable
                if (stringQueue.back() == "!"){
                    intStack.pop();
                    int value = std::stoi(stringQueue.front());
                    stringQueue.pop();
                    variable_map[stringQueue.front()] = value;
                    stringQueue.pop();
                    stringQueue.pop();
                    //std::cout << "uhoh" << std::endl;
                }

                //checks for instance of "variable", if so create variable
                if (func_str_map.find(current) != func_str_map.end()){
                    //std::cout << "Calling function for: " << current << std::endl;
                    func_str_map[current](stringStack);
                    
                }

            
                
                //this is to retrieve variable value
               
                if (stringQueue.back() == "@") {
                    std::string var1 = stringQueue.front();
                    stringQueue.pop();
                    int var_value = variable_map[var1];
                    intStack.push(var_value);

                }
                
                
            } 
        } else if (checkDigits(current)){
                int num = std::stoi(current);
                intStack.push(num);
        } else if (stringStack.size() == 0){
            if (variable_map.find(current) != variable_map.end()){
                auto it = variable_map.find(current);
                if (it != variable_map.end()){
                    const std::string* key_address = &(it->first);
                    uintptr_t numeric_address = reinterpret_cast<uintptr_t>(key_address);
        
                    
                    int address_as_int = static_cast<int>(numeric_address);

                    intStack.push(address_as_int);
                    //std::cout<<key_address<<std::endl;
                    //intStack.push(std::stoi(key_address);
                }   
            }
        }

    }
    printStack(intStack);
    //(intStack);
    
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





