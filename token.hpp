#ifndef TOKEN_H
#define TOKEN_H

#include <stack>
#include <iostream>
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

extern std::map<std::string, int> variable_map;

std::map<std::string, token_type_t> create_type_map();
bool checkDigits(std::string test);
void make_variable(std::stack<std::string>& str_stack);
std::map<std::string, std::function<void(std::stack<int>&)>> create_func_map_int();
std::map<std::string, std::function<void(std::stack<std::string>&)>> create_func_map_str();
void printStack(std::stack<int>& int_stack);
void token_separator(std::stack<std::string> stringStack, std::queue<std::string> stringQueue);
std::stack<std::string> queue_to_stack(std::queue<std::string> test_queue);


#endif
