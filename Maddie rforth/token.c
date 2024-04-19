#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include <ctype.h>
#include <string.h>
#include "int_stack.h"

token_t* intialize_token(token_type_t type, const char* text){
    token_t* newToken = (token_t*)malloc(sizeof(token_t));
    if (newToken == NULL) {
        
        return NULL;
    }
}

token_type_t get_token_type(const char* token){
    if (*token == '+' || *token == '-' || *token == '*' || *token == '/' || *token == '.') {
        return OPERATOR;
    } else if (*token == ';' || *token == ':'){
        return SYMBOL;
    } else if (*token == '=' || *token == '<' || *token == '>' || strcmp(token, "and") == 0 || strcmp(token, "or")==0 || strcmp(token, "invert")==0){
        return BOOLEAN;
    }else if (isdigit((unsigned char)*token) || *token=='@' || *token == '!'){
        if (strcmp(token, "@")==0){
            return WORD;
        }
        const char* p = token + 1; 
        while (*p) {
            if (!isdigit((unsigned char)*p)) {
                
                return WORD;
            }
            p++;
        }
        return NUMBER;
    } else {
        return WORD;
    }
}

const char* token_type_to_string(token_type_t type) {
    switch (type) {
        case OPERATOR:
            return "OPERATOR";
        case NUMBER:
            return "NUMBER";
        case SYMBOL:
            return "SYMBOL";
        case WORD:
            return "WORD";
        case BOOLEAN:
            return "BOOLEAN";
        default:
            return "ILLEGAL";
    }
}

void print_forth(int_stack_t *stk){
    int_entry_t *entry;
    int elements[stk->size]; 
    int i = 0;
    int pos = 0;
    if (stk->size == 0) {
        //printf("empty stack\n");
    }

    SLIST_FOREACH(entry, &stk->head, entries) {
        if (i < stk->size) { 
            elements[i++] = entry->value;
        }
    }

    
    printf("Stack: ");
    for (i = stk->size - 1; i >= 0; i--) {
        printf("%d ", elements[i]);
    }
    printf("<- Top\n");
}



void separate_token(int_stack_t *stk, char *text, char* stringList[], int *intList) {
    string m = ": fizz?  3 mod 0 = dup if ." Fizz" then ;"
    if token == ":":
        stack<string> = rest




    const char *space = " ";
    char *token;
    char *rest = text;

    while ((token = strtok_r(rest, space, &rest))) {
        token_type_t type = get_token_type(token);
        
        //printf("Token: %s, Type: %s\n", token, token_type_to_string(type));
        if (type == NUMBER) {
            int_stack_push(stk, atoi(token));
        } else if (type == OPERATOR) {
            int top_value;
            if (stk->size > 1){     
                if (strcmp(token, "+") == 0) {        
                    int_stack_add(stk);
                } else if (strcmp(token, "-") == 0) {
                    int_stack_subtract(stk);
                } else if (strcmp(token, "*") == 0){
                    int_stack_mult(stk);
                } else if (strcmp(token, "/mod")==0){
                    int_stack_divmod(stk);
                } else if (strcmp(token, ".")==0){
                    int_stack_pop(stk, &top_value);
                } else {
                    int_stack_div(stk);
                } 
            } else {
                int_stack_pop(stk, &top_value);
                printf("Stack underflow\n");
                
                //exit(EXIT_FAILURE);
            } 
        } else if (type == WORD){
            int top_value;
            if (strcmp(token, "over")==0){
                int_stack_over(stk);
            } else if (strcmp(token, "drop")==0){
                int_stack_pop(stk, &top_value);
            } else if (strcmp(token, "rot")==0){
                int_stack_rot(stk);
            } else if (strcmp(token, "dup")==0){
                int_stack_dup(stk);
            } else if (strcmp(token, "swap")==0){
                int_stack_swap(stk);
            } else if (strcmp(token, "2swap")==0){
                int_stack_2swap(stk);
            } else if (strcmp(token, "2dup")==0){
                int_stack_2dup(stk);
            } else if (strcmp(token, "2over")==0){
                int_stack_2over(stk);
            } else if (strcmp(token, "2drop")==0){
                int_stack_pop(stk, &top_value);
                int_stack_pop(stk, &top_value);
            } else if (strcmp(token, "mod")==0){
                int_stack_mod(stk);
            } else if (strcmp(token, "variable")==0){
                token = strtok_r(NULL, space, &rest); 
                if (token != NULL) { 
                    for (int i = 0; i < 100; i++) {
                        if (stringList[i] == NULL) {
                            stringList[i] = strdup(token);
                            break; 
                        }
                    }
                }
            } else {
                char* text;
                for (int i = 0; i < 100; i++){
                    if (stringList[i] != NULL && strcmp(token, stringList[i]) == 0) {
                        uintptr_t addr = (uintptr_t)stringList[i];
                        text = token;
                        //printf("%s\n", text);
                        int_stack_push(stk, addr);  
                        
                    }
                }
                
                token = strtok_r(NULL, space, &rest);
                if (token == NULL){
                    break;
                }
                if (strcmp(token, "@")==0){
                   for (int i = 0; i < 100; i++){
                       //printf("%d: %s\n", i, intList[i]);
                       if (stringList[i] != NULL && strcmp(text, stringList[i]) == 0) {
                           int s1, s2;
                           int_stack_pop(stk, &s1);
                           s2 = intList[i];
                           //printf("%d\n", s3);
                           int_stack_push(stk, s2);
                       }
                   }
                } else if (strcmp(token, "!")==0){
                    //print_forth(stk);
                    if (stk->size >= 2) {
                        int top_val, next_val;
                        int_stack_pop(stk, &top_val);
                        int_stack_pop(stk, &next_val);
                        //print_forth(stk);
                        for (int i = 0; i < 100; i++){
                            if (intList[i] == 0 && stringList[i] != NULL && strcmp(text, stringList[i]) == 0) {
                                intList[i] = next_val;
                                break;
                            }
                            //printf("Index %d: %d\n", i, intList[i]);
                            //printf("Index %d: %s\n", i, stringList[i]);
                            
                        
                        }
                    }
                    
                }

                
                
            }
        } else if (type == BOOLEAN){
            
            //char *next_token = strtok_r(rest, space, &rest);
            //char *third_token = strtok_r(rest, space, &rest);
            if (strcmp(token, "=")==0) {
                int_stack_push(stk, int_stack_equal(stk));
                //printf("%d\n", int_stack_equal(stk));
            } else if (strcmp(token, "<") == 0) {
                //printf("%d\n", int_stack_less(stk));
                int_stack_push(stk, int_stack_less(stk));
            } else if (strcmp(token, ">") == 0){
                int_stack_push(stk, int_stack_greater(stk));
            }

            
            if (strcmp(token, "and") == 0){
                //printf("%d\n", int_stack_and(stk));
                
                int_stack_and(stk);
            } else if (strcmp(token, "or")==0){
                int_stack_or(stk);
            } else if (strcmp(token, "invert")==0){
                int_stack_invert(stk);
            }
        } else if (type == SYMBOL){
            int top_value;
            if (strcmp(token, "!")==0){
                int next_val;
                int_stack_pop(stk, &top_value);
                int_stack_pop(stk, &next_val);
                
                for (int i = 0; i < 100; i++){
                    if (stringList[i] != NULL && strcmp(token, stringList[i]) == 0) {
                        intList[i] = next_val;
                        
                    }
                }
            }

        }
    }

    //if (next_token && strcmp(token, "invert")==0 && strcmp(next_token, ".")==0){
               // printf("%d\n", int_stack_greater(stk));
           // }
}


