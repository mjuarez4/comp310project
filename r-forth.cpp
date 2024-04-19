#include <iostream>
#include <stack>
#include <string>
#include <queue>


#include "token.hpp"

using namespace std;


std::queue<std::string> make_into_queue(std::string line){
    std::istringstream iss(line);
    std::string token;
    std::queue<std::string> tokens;
    while (iss >> token) {
        tokens.push(token);
    }
    return tokens;

}

int main(){
    //declaration of an int stack
    //std::stack<int> myStack;

    //string stack
    //std::stack<std::string> stringList;
    
    cout << "Type 'bye' to exit\n";
    std::string line;  // Declaration of 'line' as a std::string
    std::stack<std::string> myStack, stringList;
    std::stack<int> intList;

    while (std::getline(std::cin, line)) {
        if (!line.empty() && line.back() == '\n') {
            line.pop_back();  
        }

        if (line == "bye") {
            break;
        }

        std::queue<std::string> queue1 = make_into_queue(line);
        std::stack<std::string> stack1 = queue_to_stack(queue1);
        token_separator(stack1, queue1);

        //separate_token(myStack, line, stringList, intList);
        //print_forth(myStack);
    }

    return 0;
}