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
extern std::map<std::string, int> constant_map;
extern std::map<std::string, std::stack<std::string>> word_definition_map;
extern std::stack<int> intStack;

std::map<std::string, token_type_t> create_type_map();
bool checkDigits(std::string test);
void make_variable(std::stack<std::string>& str_stack);
std::map<std::string, std::function<void(std::stack<int>&)>> create_func_map_int();
std::map<std::string, std::function<void(std::stack<std::string>&)>> create_func_map_str();
std::map<std::string, std::function<void(std::stack<std::string>&)>> create_word_map();
void printStack(std::stack<int>& int_stack);
void token_separator(std::stack<std::string> stringStack, std::queue<std::string> stringQueue);
std::stack<std::string> queue_to_stack(std::queue<std::string> test_queue);
void make_constant(std::stack<std::string>& str_stack);
void make_word_definition(std::stack<std::string>& str_stack);
void print_word(std::stack<std::string>& str_stack);
std::queue<std::string> stack_to_queue(std::stack<std::string> stringStack);
void do_loop(std::stack<std::string> stringStack);
void parse_word_definition(std::stack<std::string> word_def_stack);


#endif
