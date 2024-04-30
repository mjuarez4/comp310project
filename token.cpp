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
    map["drop"] = token_type_t::OPERATOR;

    //symbol
    map[";"] = token_type_t::SYMBOL;
    map[":"] = token_type_t::SYMBOL;

    //boolean operators
    map["="] = token_type_t::OPERATOR;
    map["<"] = token_type_t::OPERATOR;
    map[">"] = token_type_t::OPERATOR;
    map["and"] = token_type_t::OPERATOR;
    map["or"] = token_type_t::OPERATOR;
    map["invert"] = token_type_t::OPERATOR;

    //word
    map["variable"] = token_type_t::WORD;
    map["array"] = token_type_t::WORD;
    map["@"] = token_type_t::WORD;
    map["!"] = token_type_t::WORD;
    map["?"] = token_type_t::WORD;
    map["+!"] = token_type_t::WORD;
    map["constant"] = token_type_t::WORD;
    map["cells"] = token_type_t::WORD;

    return map;
    
}

bool checkDigits(std::string test) {
    if (test.empty()) return false;  
    
    int start = 0;
    if (test[0] == '-') {  
        if (test.size() == 1) return false;  
        start = 1;  
    }

    for (int i = start; i < test.size(); i++) {
        if (!isdigit(test[i])) {
            return false;
        }
    }
    return true;
}


std::map<std::string, std::vector<int>> variable_array_map;
std::map<std::string, int> variable_map;
std::map<std::string, int> constant_map;
std::map<std::string, std::stack<std::string>> word_definition_map;
std::stack<int> intStack;

void make_variable(std::stack<std::string>& str_stack) {
    
    while (!str_stack.empty()) {
        std::string val1 = str_stack.top();
        str_stack.pop();
        variable_map[val1] = 0;
    }


}

void make_array(int size, std::string variable_name) {
    std::vector<int> new_array(size, 0);
    variable_array_map[variable_name] = new_array;
    std::cout << "Array: " << new_array.size() << std::endl;
}

void make_array_name(std::stack<std::string>& str_stack){
    std::vector<int> empty_array(1, 0);
    while (!str_stack.empty()) {
        std::string val1 = str_stack.top();
        str_stack.pop();
        variable_array_map[val1] = empty_array;
    }
}

void make_constant(std::stack<std::string>& str_stack) {
    while (!str_stack.empty()) {
        int const_val = intStack.top();
        intStack.pop();

        std::string str_val = str_stack.top();
        str_stack.pop();
        constant_map[str_val] = const_val;

    }

}

void make_word_definition(std::stack<std::string>& str_stack) {
    std::string word_name = str_stack.top();
    str_stack.pop();

    word_definition_map[word_name] = str_stack;
}

void print_word(std::stack<std::string>& str_stack) {
    std::string final = "";

    // Directly build the string from the stack, respecting order from top to bottom
    while (!str_stack.empty()) {
        std::string word = str_stack.top();
        str_stack.pop();

        // Check for unwanted keywords
        if (word != "loop" && word != "else" && word != ";" && word != "thens" && word != ".") {
            // Handle the specific case for the topmost word
            if (word.back() == '"') {
                word.pop_back();  // Remove the trailing quote
            }
            final += (final.empty() ? "" : " ") + word;  // Append word with spacing
        }
    }

    std::cout << final << std::endl;
}



std::queue<std::string> stack_to_queue(std::stack<std::string> stringStack){
    std::stack<std::string> tempStack;
    std::queue<std::string> outputQueue;

    while (!stringStack.empty()) {
        tempStack.push(stringStack.top());
        stringStack.pop();
    }

    while (!tempStack.empty()) {
        outputQueue.push(tempStack.top());
        tempStack.pop();
    }

    return outputQueue;
}


void do_loop(std::stack<std::string> stringStack){
    
    std::queue<std::string> looped_queue;
    

    while (!stringStack.empty()){
        std::string current = stringStack.top();
        if (current != "loop" && current != ";"){
            current = stringStack.top();
            stringStack.pop();
            looped_queue.push(current);
        } else {
            stringStack.pop();
        }
    }

    int start = 0;
    int end = 0;
    if (intStack.size() >= 2) {
        start = intStack.top();
        intStack.pop();

        end = intStack.top();
        intStack.pop();
    }

    

    std::string final_val = "";

    if (looped_queue.front() == "i"){
            looped_queue.pop();
            if (looped_queue.front() == "."){
                intStack.push(0);
                for (int i = start; i < end; i++) {
                    final_val += std::to_string(i) + " ";
                }
                final_val.pop_back();
                std::cout <<final_val<< std::endl;
            } else {
                for (int i = start; i < end; i++){
                    std::string str = std::to_string(i);
                    std::stack<std::string> stack1;
                    stack1.push(str);
                    std::queue<std::string> queue1 = stack_to_queue(stack1);
                    token_separator(stack1, queue1);
                }
            }
            
            
            
    } else{
          std::stack<std::string> stack1 = queue_to_stack(looped_queue);
          
          for (int i = start; i < end - 1; i++){
              token_separator(stack1, looped_queue);
            
          }

    }
   
}

void if_then_else(std::stack<std::string>& stringStack) {
    int boolean = intStack.top();
    intStack.pop();

    if (boolean != 0 && boolean != -1) {
        std::cout << "Top Stack Value is not a boolean.\nIf Statement Not Ran." << std::endl;
        return;
    }


    std::string current = stringStack.top();
    stringStack.pop();
    
    if (boolean) {
        std::stack<std::string> if_string_stack;
        std::stack<std::string> if_string_stack_new;
        
        while (current != "else" && stringStack.size() != 0) {
            if_string_stack.push(current);
            current = stringStack.top();
            stringStack.pop();
        }

        
        while (!if_string_stack.empty()){
            if_string_stack_new.push(if_string_stack.top());
            if_string_stack.pop();
        }

        std::queue<std::string> if_string_queue = stack_to_queue(if_string_stack_new);
        std::stack<std::string> if_temp = queue_to_stack(if_string_queue);
        std::queue<std::string> if_final = stack_to_queue(if_temp);

        token_separator(if_string_stack_new, if_final);

        if (current == "else") {
            
            stringStack.pop();
            while (stringStack.size() != 0) {
                current = stringStack.top();
                stringStack.pop();
            }
            
            
        }
        

        


    } else {
        
        stringStack.push(current);
        while (current != "else" && current != "then" && stringStack.size() != 0) {
            current = stringStack.top();
            stringStack.pop();
           
        }

        
        if (current == "else") {
            current = stringStack.top();
            stringStack.pop();
            std::stack<std::string> else_string_stack;
            while (current != "then" && stringStack.size() != 0) {
                else_string_stack.push(current);
                current = stringStack.top();
                stringStack.pop();
                
            }

            
            std::stack<std::string> else_string_stack_new;

            while (!else_string_stack.empty()){
                else_string_stack_new.push(else_string_stack.top());
                else_string_stack.pop();
            }

            std::queue<std::string> else_string_queue = stack_to_queue(else_string_stack_new);
            std::stack<std::string> else_temp = queue_to_stack(else_string_queue);
            std::queue<std::string> else_final = stack_to_queue(else_temp);

            token_separator(else_string_stack_new, else_final);



        }
    }

}

std::map<std::string, std::function<void(std::stack<int>&)>> create_func_map_int() {
    std::map<std::string, std::function<void(std::stack<int>&)>> funcMap;
    funcMap["+"] = addition;
    funcMap["-"] = subtraction;
    funcMap["*"] = multiplication;
    funcMap["/"] = division;
    funcMap["drop"] = pop_item;
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
    funcMap["="] = equality;
    funcMap["<"] = less;
    funcMap[">"] = greater;
    funcMap["and"] = and_comp;
    funcMap["or"] = or_comp;
    funcMap["invert"] = invert;

    return funcMap;
}

std::map<std::string, std::function<void(std::stack<std::string>&)>> create_func_map_str() {
    std::map<std::string, std::function<void(std::stack<std::string>&)>> func_str_map;
    func_str_map["variable"] = make_variable;
    func_str_map["constant"] = make_constant;
    func_str_map["array"] = make_array_name;
    func_str_map[":"] = make_word_definition;
    return func_str_map;
}

std::map<std::string, std::function<void(std::stack<std::string>&)>> create_word_map() {
    std::map<std::string, std::function<void(std::stack<std::string>&)>> word_def_map;
    word_def_map[".\""] = print_word; 
    word_def_map["do"] = do_loop;
    word_def_map["if"] = if_then_else;
    //word_def_map["."] = print_num;

    return word_def_map;
}



void parse_word_definition(std::stack<std::string> word_def_stack){
    std::map<std::string, std::function<void(std::stack<std::string>&)>> word_func = create_word_map();

    
    while (!word_def_stack.empty()){
        std::string current = word_def_stack.top();

   
        word_def_stack.pop();
        if (word_func.find(current) != word_func.end()){
            word_func[current](word_def_stack);
        } else {

            word_def_stack.push(current);
            std::queue<std::string> word_def_queue = stack_to_queue(word_def_stack);
            token_separator(word_def_stack, word_def_queue);
            break;
        }
    }


}

void token_separator(std::stack<std::string> stringStack, std::queue<std::string> stringQueue){
    std::map<std::string, token_type_t> typeMap = create_type_map();
    std::map<std::string, std::function<void(std::stack<int>&)>> funcMap = create_func_map_int();
    std::map<std::string, std::function<void(std::stack<std::string>&)>> func_str_map = create_func_map_str();
    std::map<std::string, std::function<void(std::stack<std::string>&)>> word_func = create_word_map();
    while (!stringStack.empty()){
        std::string current = stringStack.top();
       
        stringStack.pop();
        if (typeMap.find(current) != typeMap.end()){
            token_type_t val = typeMap[current];
            if (val == token_type_t::SYMBOL){
             
                if (func_str_map.find(current) != func_str_map.end()){
                    func_str_map[current](stringStack);
                }

                break;
            } else if (val == token_type_t::OPERATOR){
                if (funcMap.find(current) != funcMap.end()){
                    funcMap[current](intStack);
                   
                }
            } else if (typeMap[current] == token_type_t::WORD){
                if (stringQueue.back() == "!"){

                    int value = intStack.top();

                    intStack.pop();
                    variable_map[stringQueue.front()] = value;
                    stringQueue.pop();
                    stringQueue.pop();
                    
                    
                }
                
                
                if (func_str_map.find(current) != func_str_map.end()){
                    
                    func_str_map[current](stringStack);
                    
                }


         
		

		        if (current == "cells" && stringStack.top() == "allot" && !intStack.empty()) {
			        int cell_count = intStack.top();
			        intStack.pop();
			        stringStack.pop();
			        std::string variable_name = stringStack.top();
		                if (variable_array_map.find(variable_name) != variable_array_map.end()) {
			            make_array(cell_count, variable_name);
			        }
		        }
			    	
			
                if (stringQueue.back() == "@") {
                    std::string variable_name = stringQueue.front();
                    stringQueue.pop();
                    
                    if (variable_map.find(variable_name) != variable_map.end()){
                         int var_value = variable_map[variable_name];
                         intStack.push(var_value);
                    } else if (variable_array_map.find(variable_name) != variable_array_map.end()){

                        int index_val = 0;

                        if (intStack.size() > 0){
                            index_val = intStack.top();
                            intStack.pop();
                        }
    
                        std::vector<int> get_array = variable_array_map[variable_name];
                        int value_at_index = get_array[index_val];

                        intStack.push(value_at_index);

                        stringQueue.pop();
                        //pop @
                       
                        //pop +!
                    }
                    
                } else if (stringQueue.back() == "?"){
                    std::string variable_name = stringQueue.front();
                    stringQueue.pop();
                    
                    if (variable_map.find(variable_name) != variable_map.end()){
                         int var_value = variable_map[variable_name];
                         
                         std::cout<<var_value<<std::endl;
                    } else if (variable_array_map.find(variable_name) != variable_array_map.end()){
                        
                        int index_val = intStack.top();
                        intStack.pop();
                        
                        std::vector<int> get_array = variable_array_map[variable_name];
                        int value_at_index = get_array[index_val];

                        std::cout<<value_at_index<<std::endl;

                        stringQueue.pop();
                       
                    }
                    

                } else if (stringQueue.back() == "+!"){
                    std::string variable_name = stringQueue.front();
                    stringQueue.pop();


                    if (variable_map.find(variable_name) != variable_map.end()){
                            
                        int increase = intStack.top();
                        intStack.pop();

                        int current_val = variable_map[variable_name];
                        variable_map[variable_name] = current_val + increase;
                        
                        stringQueue.pop();
                    } else if (variable_array_map.find(variable_name) != variable_array_map.end()){
                        int index_val = 0;
                        int val_replace = 0;
                        if (intStack.size() >= 2) {                         
                            index_val = intStack.top();
                            intStack.pop();

                            val_replace = intStack.top();
                            intStack.pop();
                        }


                        std::vector<int> get_array = variable_array_map[variable_name];
                        get_array[index_val] = val_replace;
                       

                        variable_array_map[variable_name] = get_array;
                        

                        std::string string1 = stringQueue.front();
                        stringQueue.pop();
                       
                        
                    }
                    
                }
                
                
            } 
        } else if (checkDigits(current)){
                int num = std::stoi(current);
                intStack.push(num);
                stringQueue.pop();
                
                
        } else if (stringStack.size() == 0){

            if (variable_map.find(current) != variable_map.end()){
                auto it = variable_map.find(current);
                if (it != variable_map.end()){
                    const std::string* key_address = &(it->first);
                    uintptr_t numeric_address = reinterpret_cast<uintptr_t>(key_address);
        
                    
                    int address_as_int = static_cast<int>(numeric_address);

                    intStack.push(address_as_int);
                    
                }   
            }
          
        } else if (constant_map.find(current) != constant_map.end()){
            int value = constant_map[current];
            intStack.push(value);
        } else if (word_definition_map.find(current) != word_definition_map.end()){
              stringQueue.pop();
              parse_word_definition(word_definition_map[current]);
        } else if (word_func.find(current) != word_func.end()){
            word_func[current](stringStack);
        } 

    }

    std::string current = stringQueue.front();
    if (word_definition_map.find(current) != word_definition_map.end()){
              stringQueue.pop();
            
              parse_word_definition(word_definition_map[current]);
    }

   
    printStack(intStack);
    
}

void printStack(std::stack<int>& int_stack) {
    std::stack<int> temp_stack;
    std::vector<int> items;

    while (!int_stack.empty()) {
        temp_stack.push(int_stack.top());
        int_stack.pop();
    }

    
    while (!temp_stack.empty()) {
        int top_element = temp_stack.top();
        items.push_back(top_element);  
        int_stack.push(top_element);
        temp_stack.pop();
    }

   
    std::cout << "Stack: [";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << items[i];
    }
    std::cout << "] <- Top" << std::endl;
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







