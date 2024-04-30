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
    map["@"] = token_type_t::WORD;
    map["!"] = token_type_t::WORD;
    map["?"] = token_type_t::WORD;
    map["+!"] = token_type_t::WORD;
    map["constant"] = token_type_t::WORD;

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

void make_constant(std::stack<std::string>& str_stack) {
    while (!str_stack.empty()) {
        //int val1 = std::stoi(str_stack.top());
        //get name of constant
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



void print_word(std::stack<std::string>& str_stack){
    // Hello there!" ;
 
    std::string final = "";
    std::queue<std::string> new_queue;
    while(str_stack.size()>1){

        // there!" ;
        //std::cout<<str_stack.top()<<std::endl;
        if (str_stack.top() != "loop"){
            new_queue.push(str_stack.top());
            str_stack.pop();
        } else {
            str_stack.pop();
        }
    }

    while(new_queue.size() > 1){
            //std::cout<<new_queue.front()<<std::endl;
            final += new_queue.front() + " ";
            new_queue.pop();
            //std::cout<<"florida"<<std::endl;
    }

    //::cout<<"huh"<<std::endl;
    std::string last_string = new_queue.front();
    last_string.pop_back();

    final += last_string;
    
       

    std::cout<<final<<std::endl;
    
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
    // 10 0 do i . loop ;

    //i . loop ;


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
    /*

    while(current != "loop"){
        current = stringStack.top();
        stringStack.pop();
        looped_queue.push(current);
    }
    */

    //std::cout<<looped_queue.front()<<std::endl;
    int start = intStack.top();
    intStack.pop();

    int end = intStack.top();
    intStack.pop();

    std::string final_val = "";

    if (looped_queue.front() == "i"){
            //pop i
            looped_queue.pop();

            //std::cout<<looped_queue.front()<<std::endl;
            //stringStack.pop();
            // pop .
            
            if (looped_queue.front() == "."){
                intStack.push(0);
                //looped_queue.pop();
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
    //std::cout << "Better make it here" << std::endl;
    // Get front stack value and remove it from the int stack
    int boolean = intStack.top();
    intStack.pop();

    //Check that front stack value is a boolean
    if (boolean != 0 && boolean != -1) {
        std::cout << "Top Stack Value is not a boolean.\nIf Statement Not Ran." << std::endl;
        return;
    }

    std::string current = stringStack.top();
    stringStack.pop();

    //std::cout << "Worked like its supposed to (get first value and store in current)" << std::endl;

    //If true, run all if commands and skip then commands
    if (boolean) {
        //std::cout << "Apparently True" << std::endl;
        //Run all instructions in if clause
        std::stack<std::string> if_string_stack;
        while (current != "else" && current != "then" && stringStack.size() != 0) {
            if_string_stack.push(current);
            current = stringStack.top();
            stringStack.pop();
        }
        std::queue<std::string> if_string_queue = stack_to_queue(if_string_stack);
        token_separator(if_string_stack, if_string_queue);
        /*std::string if_instructions = "";
        while(!if_string_queue.empty()) {
            if_instructions += " " + if_string_queue.front();
            if_string_queue.pop();
        }*/
        //std::cout << "Executing if instructions: " << if_instructions << std::endl;
        


        //If else clause is next, skip all its instructions
        if (current == "else") {
            //std::cout << "Found else" << std::endl;
            current = stringStack.top();
            stringStack.pop();
            while (current != "then" &&  stringStack.size() != 0) {
                current = stringStack.top();
                stringStack.pop();
            }
        }

    //If false, run all else commands, if found
    } else {
        //std::cout << "Apparently False" << std::endl;
        //Skip all if instructions
        while (current != "else" && current != "then" && stringStack.size() != 0) {
            current = stringStack.top();
            stringStack.pop();
            //std::cout << "Got a token from if block: " << current << std::endl;
        }

        //If else clause is next, run all its instructions
        if (current == "else") {
            current = stringStack.top();
            stringStack.pop();
            std::stack<std::string> else_string_stack;
            while (current != "then" && stringStack.size() != 0) {
                else_string_stack.push(current);
                current = stringStack.top();
                stringStack.pop();
                //std::cout << "Got a token from else block: " << current << std::endl;
            }
            std::queue<std::string> else_string_queue = stack_to_queue(else_string_stack);
            token_separator(else_string_stack, else_string_queue);
            /*std::string else_instructions = "";
            while(!else_string_queue.empty()) {
                else_instructions += " " + else_string_queue.front();
                else_string_queue.pop();
            }*/
            //std::cout << "Executing else instructions: " << else_instructions << std::endl;
        }
    }

    //Once then is reached or no instructions are left, return the string stack to token_separator
    /*std::queue<std::string> stringQueue = stack_to_queue(stringStack);/////////////////
    //std::cout<<"Sending rest to token separator"<<std::endl;
    token_separator(stringStack, stringQueue);
    std::string rest_instructions = "";
    while(!stringQueue.empty()) {
        rest_instructions += " " + stringQueue.front();
        stringQueue.pop();
    }*/
    //std::cout << "Executing rest of instructions: " << rest_instructions << std::endl;
    //Remove then if it remains

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
        //std::cout<<"HUH"<<std::endl;
        std::cout<<"Running: "<<current<<std::endl;
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
                    //printStack(intStack);
                   
                }
            } else if (typeMap[current] == token_type_t::WORD){
                
                //this is to add value to variable
                if (stringQueue.back() == "!"){
                    
                    int value = intStack.top();

                    
                    //std::string string1 = stringQueue.front();
                    //std::cout<<string1<<std::endl;
                    intStack.pop();
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
                //prints out variable value
                } else if (stringQueue.back() == "?"){
                    std::string var1 = stringQueue.front();
                    stringQueue.pop();
                    int var_value = variable_map[var1];
                    std::cout<<var_value<<std::endl;

                    
                //updates variable value
                } else if (stringQueue.back() == "+!"){

                    //intStack.pop();
                    int increase = intStack.top();
                    intStack.pop();

                    //std::cout<<stringQueue.front()<<std::endl;
                    //stringQueue.pop();
                    //variable name
                    int current_val = variable_map[stringQueue.front()];
                    variable_map[stringQueue.front()] = current_val + increase;
                    stringQueue.pop();
                    stringQueue.pop();
                }
                
                
            } 
        } else if (checkDigits(current)){
                int num = std::stoi(current);
                intStack.push(num);
                stringQueue.pop();
                //std::cout<<"even more confusde"<<std::endl;
                //std::cout<<stringQueue.front()<<std::endl;
                
        } else if (stringStack.size() == 0){

            //handles calls of just variable address
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
          //handles calls of just constant
        } else if (constant_map.find(current) != constant_map.end()){
            int value = constant_map[current];
            intStack.push(value);
        } else if (word_definition_map.find(current) != word_definition_map.end()){
              stringQueue.pop();
              parse_word_definition(word_definition_map[current]);
        } else if (word_func.find(current) != word_func.end()){
            word_func[current](stringStack);
        }

        


        //do i . loop ;
        /*
        if (word_func.find(current) != word_func.end()){
            word_func[current](stringStack);
        }
        */

    }

    std::string current = stringQueue.front();

    //this is the variable/function map
    if (word_definition_map.find(current) != word_definition_map.end()){
              stringQueue.pop();
            
              parse_word_definition(word_definition_map[current]);
    }

   
    printStack(intStack);
    
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
        items.push_back(top_element);  
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






