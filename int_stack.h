#ifndef INT_STACK_H
#define INT_STACK_H

#include <stack>
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <cctype>
#include <sstream> 
#include <queue>


extern std::stack<int> myStack;

std::stack<int> addition(std::stack<int>& intStack);
std::stack<int> subtraction(std::stack<int>& intStack);
std::stack<int> multiplication(std::stack<int>& intStack);
std::stack<int> division(std::stack<int>& intStack);
std::stack<int> pop_item(std::stack<int>& intStack);
std::stack<int> dup(std::stack<int>& intStack);
std::stack<int> swap(std::stack<int>& intStack);
std::stack<int> over(std::stack<int>& intStack);
std::stack<int> rot(std::stack<int>& intStack);
std::stack<int> two_swap(std::stack<int>& intStack);
std::stack<int> two_over(std::stack<int>& intStack);
std::stack<int> two_dup(std::stack<int>& intStack);
std::stack<int> mod(std::stack<int>& intStack);
std::stack<int> div_mod(std::stack<int>& intStack);
#endif