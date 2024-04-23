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

std::stack<int> intStack;

void do_loop(std::stack<std::string> stringStack){
    // 10 0 do i . loop ;

    //i . loop ;
    std::queue<std::string> looped_queue;
    std::string current = stringStack.top();
    while(current != "loop"){
        current = stringStack.top();
        stringStack.pop();
        looped_queue.push(current);
    }

    int start = intStack.top();
    intStack.pop();

    int end = intStack.top();
    intStack.pop();

    std::string final_val = "";

    if (looped_queue.front() == "i"){
            //pop i
            looped_queue.pop();
            // pop .
            looped_queue.pop();

            std::string luke = looped_queue.front();

            while(!looped_queue.empty()){
                std::string extra = looped_queue.front();
                looped_queue.pop();
                if (extra != "loop" && extra != ";"){
                    final_val += extra;
                }
                
            }

            for (int i = start; i < end; i++) {
                std::cout << i << " " << final_val << std::endl;
            }
    } else{


        for (int i = start; i < end; i++) {
                std::cout << i << std::endl;
        }
    }

   
}

int main(){
    intStack.push(10);
    intStack.push(0);

    std::stack<std::string> string_stack;


    //funcMap["do"] = do_loop;

    // i . 5 loop ;

    //0 5
    //1 5
    string_stack.push(";");
    string_stack.push("loop");
    string_stack.push("5");
    string_stack.push(".");
    string_stack.push("i");

    do_loop(string_stack);



}