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
 * Verify top value is a boolean
 * Get top value and use to determine what will be run
 * If true, run all if code
 * If false, run all else code
 * Run all Then code regardless
 */

/* ****Assumptions****
 * Int Stack is global
 * Int Stack will handle underflow
 * Function is called after "if" is popped and recognized
 */

void if_then_else(std::stack<std::string> stringStack) {
    // Get top stack value
    // ***************int boolean = intStack.top();
    int boolean = 0;

    //Check that top stack value is a boolean
    if (boolean != 0 || boolean != -1) {
	std::cout << "Top Stack Value is not a boolean" << std::endl;
	return;
    }

    std::string current = stringStack.top();
    stringStack.pop();

    //If true, run all if commands and skip then commands
    if (boolean) {
	//Run all instructions in if clause
	std::stack<std::string> if_string_stack;
	while (current != "else" || current != "then" || stringStack.size() != 0) {
	    if_string_stack.push(current);
	    current = stringStack.top();
	    stringStack.pop();
	}
	std::queue<std::string> if_string_queue = stack_to_queue(if_string_stack);
	token_seperator(if_string_stack, if_string_queue);

	//If else clause is next, skip all its instructions
	if (current == "else") {
	    while (current != "then" || stringStack.size() != 0) {
	        current = stringStack.top();
	        stringStack.pop();
	    }
	}



    //If false, run all else commands, if found
    } else {
	//Skip all if instructions
	while (current != "else" || current != "then" || stringStack.size() != 0) {
	    current = stringStack.top();
	    stringStack.pop();
	}


	//If else clause is next, run all its instructions
	std::stack<std::string> if_string_stack;
	if (current == "else") {
	    while (current != "then" || stringStack.size() != 0) {
		    else_string_stack.push(current);
	        current = stringStack.top();
	        stringStack.pop();
	    }
	    std::queue<std::string> if_string_queue = stack_to_queue(if_string_stack);
	    token_seperator(if_string_stack, if_string_queue);
	}
    }
    //Once then is reached or no instructions are left, return the string stack to token_seperator	
    std::queue<std::string> stringQueue = stack_to_queue(stringStack);
    token_seperator(stringStack, stringQueue);
}

int main(){
    std::stack<std::string> stringStack;
    stringStack.push("dup");
    stringStack.push("else");
    std::string current = stringStack.top();
    stringStack.pop();
    std::cout << current << std::endl;
    current = stringStack.top();
    stringStack.pop();
    std::cout << current << std::endl;
    current = stringStack.top();
    stringStack.pop();
    std::cout << current << std::endl;
    return 0;

}
	    
	

