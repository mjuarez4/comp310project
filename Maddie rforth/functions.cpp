#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <queue>
//#include <exception>



/* General Outline for Implementation
 *
 * Functions will begin as one big string:
 *   - First word is the function name
 *   - All other tokens are the function definition
 *
 * ***Tasks***
 * Separate function name and function notation
 * Run function definition based on function reference
 *
 *
 * Have a name (string) : function (string) map that stores funciton
 * definitions and their name as the key.
 *
 * Functions need to be runable in forth based on reference
 *
 * 
 *
 * 
 *
 * Parse the function to verify it is valid and would work when called (last)
 *
 * Problems:
 * - Functions, variables, constants cannot share names
 * - GForth allows for empty functions: could be changed, but not important
 *
 */

std::map<std::string, std::string> func_map;

std::vector<std::string> parse_function(std::stack<std::string> stringStack, std::queue<std::string> stringQueue, std::string symbol) {
    /* Get the position of the first space
    size_t pos = function_string.find_first_of(" ");

    // Get the first word using the space position
    std::string function_name = function_string.substr(0, pos);

    // The rest of the string is the function definition
    std::string function_definition = function_string.substr(pos+1);

    // Create a vector to store the name and definition of the function
    std::vector<std::string> function_name_and_def = {function_name, function_definition};

    */
    //Declare strings for function name and definition
    std::string function_name, function_definition;
    //Declare the function name and definition vector
    std::vector<std::string> name_and_def;

    //Get rid of found semicolon in the stack (Assuming function is valid for now)
    //Verify semicolon
    if(symbol == ";"){
        //Pop values from stack until a colon is found
	current = stringStack.pop();
	while(current != ":") {
	    //Check to make sure there are tokens remaining
	    if(stringStack.size == 0) {
		std::cout << "No matching colon found" << std::endl;
		name_and_def = {"NADA", "NADA"};
		return name_and_def;
	    }
	    //Add current token to front of function definition string
	    if (function_definition = NULL) {
		function_definition = current;
	    } else {
		function_definition = current + " " + function_definition;
	    }
	    //Get the next token from the stack
	    current = stringStack.pop();
        }
	//Once colon is found, the first token is name and rest is the definition
	//Remove the first token and set the values in the name and def vector
	if (pos != std::string::npos) {
	    size_t pos = function_definition.find(' ');
	    function_name = function_definition.substr(0,pos);
	    function_definition.erase(0, pos+1);
	    name_and_def = {function_name, function_defitition};
	} else {
	    std::cout << "Only function name given with no definition" << std::endl;
	    std::cout << "Function's definition will be empty" << std::endl;
	    name_and_def = {function_definition, ""};
	    return name_and_def;
	}
    //If not a semicolon, throw a hissy fit
    } else {
	std::cout << "Why no semicolon?" << std::endl;
    }
    return name_and_def;
}




    



    std::vector<std::string> function_name_and_def = 
    // Return the resulting vector
    return function_name_and_def;
}

void insert_into_function_map(std::string function_name_and_def, std::map<std::string, std::string> func_map) {
   func_map[function_name_and_def[0]] = function_name_and_def[1];
}

std::string get_function_def(std::string function_name, std::map<std::string, std::string> func_map>) {
    std::string function_definition;
    auto itr = func_map.find(function_name);
    if (itr != func_map.end()){
	function_definition = itr->second;
	std::cout << "Found function definition for " << function_name << ": " << function_definition << std::endl
    } else {
	std::cout << "No function definition for " << function_name << std::endl;
	//Figure out how to handle finding no definition for a function name
	return "INVALID";
    }
    return function_definition;
}

void process_function(std::stack<std::string> stringStack, std::queue<std::string> stringQueue


int main() {

    return 0;
}
