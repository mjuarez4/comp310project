#include <stack>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>

void print_word(std::stack<std::string>& str_stack){
    // Hello there!" ;
    std::string final = "";
    while(!str_stack.empty()){
        //std::cout<<str_stack.top()<<std::endl;
        final += str_stack.top();
        str_stack.pop();

        // there!" ;
        std::queue<std::string> new_queue;
        while(str_stack.top() != ";" && !str_stack.empty()){
            new_queue.push(str_stack.top());
            str_stack.pop();
        }

        //pop ;
        str_stack.pop();


        //there!"
        while(new_queue.size() > 1){
            std::cout<<new_queue.front()<<std::endl;
            new_queue.pop();
        }

        std::string last_string = new_queue.front();
        last_string.pop_back();

        final += " " + last_string;
    }

    std::cout<<final<<std::endl;
}


std::queue<std::string> make_into_queue(std::string line){
    std::istringstream iss(line);
    std::string token;
    std::queue<std::string> tokens;
    while (iss >> token) {
        tokens.push(token);
    }
    return tokens;

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

int main() {
    std::string testing = "Hello there!\" ;";
    std::istringstream iss(testing);
    std::string token;
    std::stack<std::string> tokens;

    
    while (iss >> token) {
        tokens.push(token);
    }

    std::queue<std::string> queue1 = make_into_queue(testing);
    std::stack<std::string> stack1 = queue_to_stack(queue1);

    print_word(stack1);

    return 0;
}
