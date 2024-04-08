#include <iostream>
#include <stack>
#include <string>

using namespace std;

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

        //separate_token(myStack, line, stringList, intList);
        //print_forth(myStack);
    }

    return 0;
}