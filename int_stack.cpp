#include "int_stack.h"
#include <stack>
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <cctype>
#include <sstream>
#include <queue>


std::stack<int> myStack;

std::stack<int> addition(std::stack<int>& intStack){
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = val2 + val1;
    intStack.push(val3);
    return intStack;
}

std::stack<int> subtraction(std::stack<int>& intStack){
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = val2 - val1;
    intStack.push(val3);
    return intStack;
}

std::stack<int> multiplication(std::stack<int>& intStack){
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = val2 * val1;
    intStack.push(val3);
    return intStack;
}

std::stack<int> division (std::stack<int>& intStack){
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = val2 / val1;
    intStack.push(val3);
    return intStack;
}

std::stack<int> pop_item(std::stack<int>& intStack){
    intStack.pop();
    return intStack;
}

std::stack<int> dup(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    intStack.push(val1);
    intStack.push(val1);
    return intStack;
}

std::stack<int> swap(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();

    intStack.push(val1);
    intStack.push(val2);
    return intStack;
}


std::stack<int> over(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }

    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();

    intStack.push(val2);
    intStack.push(val1);
    intStack.push(val2);
    return intStack;
}

std::stack<int> rot(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = intStack.top();
    intStack.pop();

    intStack.push(val2);
    intStack.push(val1);
    intStack.push(val3);
    return intStack;
}

std::stack<int> two_swap(std::stack<int>& intStack){
    if (intStack.size() < 4){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = intStack.top();
    intStack.pop();
    int val4 = intStack.top();
    intStack.pop();

    intStack.push(val2);
    intStack.push(val1);
    intStack.push(val4);
    intStack.push(val3);
    return intStack;
}

std::stack<int> two_over(std::stack<int>& intStack){
    if (intStack.size() < 4){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();
    int val3 = intStack.top();
    intStack.pop();
    int val4 = intStack.top();
    intStack.pop();

    intStack.push(val4);
    intStack.push(val3);
    intStack.push(val2);
    intStack.push(val1);
    intStack.push(val4);
    intStack.push(val3);
    return intStack;
}

std::stack<int> two_dup(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();

    intStack.push(val2);
    intStack.push(val1);
    intStack.push(val2);
    intStack.push(val1);
    return intStack;
}

std::stack<int> mod(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();

    int mod = val2 % val1;
    intStack.push(mod);
    return intStack;
}


std::stack<int> div_mod(std::stack<int>& intStack){
    if (intStack.size() < 2){
        throw std::runtime_error("Need at least two elements in the stack to swap.");
    }

    std::cout << intStack.top() << std::endl;
    int val1 = intStack.top();
    intStack.pop();
    int val2 = intStack.top();
    intStack.pop();

    int rem = val2 % val1;
    int quot = val1 / val2;
    intStack.push(rem);
    intStack.push(quot);
    return intStack;
}

