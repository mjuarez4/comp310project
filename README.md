# comp310project

Group Name: GPT-5

project members:
Maddie Juarez
Luke Niemeyer
Nick Zappia

Project objective:
To use C++ to reconstruct our foundational construction of forth interpretation in C. We want to explore using C++ to add onto our project and handle functions, if-else then statements, loops, and potentially explore supporting datastructures such as arraylists, trees, queues, etc.


Updates:

How to run with C-11 compiler:
 g++ -std=c++11 -o token int_stack.cpp token.cpp r-forth.cpp
 ./token


Functionality: Maddie 4/17
-- testing with main() in token.cpp (don't worry, this will be removed in the final submission, i just made it easier
to test input instead of compiling the user interface every time)
-- added a mapping from token to function
    --done by token type
-- added a mapping from token to token type
    -- planning on controlling input by checking first if token is a : or ; -> if so, push everything onto a stack and handle
    in custom function (to be built by Nick/Luke)
-- take input as string stack, convert to queue (so that you can see the front/back of input at all times)
-- added compatability for variables and constants
-- re-added interactivity on command line

Completed:
-- basic operations (+, -, dup, swap, etc.)
-- variable declaration and operation (!, @, +!)
-- add booleans (<, >, and, etc.)

To do:

-- clean up 'WORD' code into functions
-- begin adding array implementation