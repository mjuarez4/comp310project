#include <iostream>
#include <string>
#include <stack>
#include <queue>


/* ****If/Then/Else Breakdown****
 *
 * Condition First
 * If
 * Instructions If True
 * Else
 * Instructions If False
 * Then
 * Instruction That Are Ran Regardless
 *
 * Example:
 * : is-it-zero?  0 = if ." Yes!" else ." No!" then ;
 */

/* ****Tasks****
 * Handle stack underflows for the int stack
 * Verify front value is a boolean
 * Get front value and use to determine what will be run
 * If true, run all if code
 * If false, run all else code
 * Run all Then code regardless
 */

/* ****Assumptions****
 * Int Stack is global
 * Int Stack will handle underflow
 * Function is called after "if" is popped and recognized
 */

std::stack<int> intStack;

void if_then_else(std::stack<std::string> stringStack) {
    std::cout << "Better make it here" << std::endl;
    // Get front stack value and remove it from the int stack
    int boolean = intStack.top();
    intStack.pop();

    //Check that front stack value is a boolean
    if (boolean != 0 && boolean != -1) {
        std::cout << "Top Stack Value is not a boolean" << std::endl;
        return;
    }

    std::string current = stringStack.top();
    stringStack.pop();

    std::cout << "Worked like its supposed to (get first value and store in current)" << std::endl;

    //If true, run all if commands and skip then commands
    if (boolean) {
	std::cout << "Apparently True" << std::endl;
        //Run all instructions in if clause
        std::stack<std::string> if_string_stack;
        while (current != "else" && current != "then" && stringStack.size() != 0) {
            if_string_stack.push(current);
            current = stringStack.top();
            stringStack.pop();
        }
        /*std::queue<std::string> if_string_queue = stack_to_queue(if_string_stack);
        /////////////token_seperator(if_string_stack, if_string_queue);
	std::string if_instructions = "";
	while(!if_string_queue.empty()) {
	    if_instructions += " " + if_string_queue.front();
	    if_string_queue.pop();
	}
	std::cout << "Executing if instructions: " << if_instructions << std::endl;*/
	std::string if_instructions = "";
	while(!if_string_stack.empty()) {
	    if_instructions += " " + if_string_stack.top();
	    if_string_stack.pop();
	}
	std::cout << "Executing if instructions: " << if_instructions << std::endl;
	
	

        //If else clause is next, skip all its instructions
        if (current == "else") {
	    std::cout << "Found else" << std::endl;
            current = stringStack.top();
            stringStack.pop();
            while (current != "then" &&  stringStack.size() != 0) {
                current = stringStack.top();
                stringStack.pop();
            }
        }

    //If false, run all else commands, if found
    } else {
	std::cout << "Apparently False" << std::endl;
        //Skip all if instructions
        while (current != "else" && current != "then" && stringStack.size() != 0) {
            current = stringStack.top();
            stringStack.pop();
	    std::cout << "Got a token from if block: " << current << std::endl;
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
	        std::cout << "Got a token from else block: " << current << std::endl;
            }
            /*std::queue<std::string> else_string_queue = stack_to_queue(else_string_stack);
            ////////////token_seperator(else_string_stack, else_string_queue);
	    std::string else_instructions = "";
	    while(!else_string_queue.empty()) {
	        else_instructions += " " + else_string_queue.front();
	        else_string_queue.pop();
	    }
	    std::cout << "Executing else instructions: " << else_instructions << std::endl;*/
	    std::string else_instructions = "";
	    while(!else_string_stack.empty()){
	        else_instructions += " " + else_string_stack.top();
	        else_string_stack.pop();
	    }
	    std::cout << "Executing else instructions: " << else_instructions << std::endl;
        }
    }

    //Once then is reached or no instructions are left, return the string stack to token_seperator
    /*std::queue<std::string> stringQueue = stack_to_queue(stringStack);
    ////////////////////token_seperator(stringStack, stringQueue);
    std::string rest_instructions = "";
    while(!stringQueue.empty()) {
        rest_instructions += " " + stringQueue.front();
	stringQueue.pop();
    }
    std::cout << "Executing rest of instructions: " << rest_instructions << std::endl;*/
    //Remove then if it remains
    if(current == "then") {
	stringStack.pop();
    }
    std::string rest_instructions = "";
    while(!stringStack.empty()){
        rest_instructions += " " + stringStack.top();
        stringStack.pop();
    }
    std::cout << "Executing rest instructions: " << rest_instructions << std::endl;

}

int main() {

    intStack.push(-1); //pushes false onto the stack
    
    std::stack<std::string> stringStack;

/*    stringStack.push("4");

    stringStack.push("2dup");

    stringStack.push("then");

    stringStack.push("over");

    stringStack.push("else");

    stringStack.push("dup");

    stringStack.push("3");

    stringStack.push("if");
*/

    stringStack.push("4");

    stringStack.push("2dup");

    stringStack.push("then");

    stringStack.push("over");

    stringStack.push("else");

    stringStack.push("5");

    stringStack.push("3");

    stringStack.push("if");

    



    std::cout << "Obviously making it here" << std::endl;
    if_then_else(stringStack);
    
    return 0;

}
