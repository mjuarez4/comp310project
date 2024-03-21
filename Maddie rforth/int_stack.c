// int_stack.c

#include "int_stack.h"

#include <stdlib.h>
#include <stdio.h>

void int_stack_init(int_stack_t *stk, int capacity) {
    SLIST_INIT(&stk->head);
    stk->size = 0;
    stk->capacity = capacity;
}

int int_stack_push(int_stack_t *stk, int value) {
    if (stk->size >= stk->capacity) {
        printf("Stack is at full capacity.\n");
        return 0; // fail
    }

    int_entry_t *newEntry = malloc(sizeof(int_entry_t));
    if (newEntry) {
        newEntry->value = value;
        SLIST_INSERT_HEAD(&stk->head, newEntry, entries);
        stk->size++;
        return 1; //success
    }
    return 0; // fail
}



int int_stack_pop(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        int value = entry->value;
        SLIST_REMOVE_HEAD(&stk->head, entries);
        free(entry);
        stk->size--;
        *top_value = value;
        return 1; // success
    }
    return 0; // fail
}

int int_stack_top(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        *top_value = entry->value;
        return 1; // success
    }
    return 0; // fail
}

/* Functions for FORTH langauge stack operators */

int int_stack_dup(int_stack_t *stk) {
    if (stk->size < 1)
        return 0;
    int top_value;
    int_stack_top(stk, &top_value);
    return int_stack_push(stk, top_value); // success only if last operation succeeds
}

int int_stack_swap(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, next_to_top_value); // success only if last operation succeeds
}

/* Example of how to create a binary operator that works o top two elements (if present) */
int int_stack_over(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_push(stk, next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, next_to_top_value);
}

int int_stack_rot(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, val2, val3;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &val2);
    int_stack_pop(stk, &val3);
    int_stack_push(stk, val2);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, val3);
}

int int_stack_2swap(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int s1, s2, s3, s4;
    int_stack_pop(stk, &s1);
    int_stack_pop(stk, &s2);
    int_stack_pop(stk, &s3);
    int_stack_pop(stk, &s4);
    int_stack_push(stk, s2);
    int_stack_push(stk, s1);
    int_stack_push(stk, s4);
    return int_stack_push(stk, s3);
}

int int_stack_2dup(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int s1, s2;
    int_stack_pop(stk, &s1);
    int_stack_pop(stk, &s2);
    int_stack_push(stk, s2);
    int_stack_push(stk, s1);
    int_stack_push(stk, s2);
    return int_stack_push(stk, s1);
}

int int_stack_2over(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int s1, s2, s3, s4;
    int_stack_pop(stk, &s1);
    int_stack_pop(stk, &s2);
    int_stack_pop(stk, &s3);
    int_stack_pop(stk, &s4);
    int_stack_push(stk, s4);
    int_stack_push(stk, s3);
    int_stack_push(stk, s2);
    int_stack_push(stk, s1);
    int_stack_push(stk, s4);
    return int_stack_push(stk, s3);
}




int int_stack_add(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value + next_to_top_value);
}

int int_stack_mult(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value * next_to_top_value);
}

int int_stack_div(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, next_to_top_value / top_value);
}

int int_stack_subtract(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value - next_to_top_value);
}

int int_stack_mod(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value % next_to_top_value);
}

int int_stack_divmod(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int s1, s2;
    int_stack_pop(stk, &s1); 
    int_stack_pop(stk, &s2);
    int rem = s2 % s1;
    int quot = s2 / s1;
    int_stack_push(stk, rem);
    return int_stack_push(stk, quot);
}

int int_stack_equal(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    if (top_value != next_to_top_value){
        return 0;
    }
    return -1;
}

int int_stack_less(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    if (top_value < next_to_top_value){
        return 0;
    }
    return -1;
}

int int_stack_greater(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    if (top_value > next_to_top_value){
        return 0;
    }
    return -1;
}

int int_stack_and(int_stack_t *stk) {
    if (stk->size < 2) {
        //return 0;
    }
    int result = -1; 
    int firstValue;
    int_stack_pop(stk, &firstValue);

    
    while (stk->size > 0) {
        int currentValue;
        int_stack_pop(stk, &currentValue);
        if (currentValue != firstValue) {
            result = 0; 
            break; 
        }
    }
    
    return int_stack_push(stk, result);
    
}

int int_stack_or(int_stack_t *stk) {
   if (stk->size < 2) {
        return 0;
   }
   int result = 0; 
   int firstValue;
   int_stack_pop(stk, &firstValue);

   while (stk->size > 0) {
        int currentValue;
        int_stack_pop(stk, &currentValue);
        if (currentValue == -1 || firstValue == -1) {
            result = -1; 
            break; 
        }
   }
   return int_stack_push(stk, result);
}

int int_stack_invert(int_stack_t *stk) {
   int firstValue;
   int_stack_pop(stk, &firstValue);

   int result = 0;
   if (firstValue == -1){
       return int_stack_push(stk, result);
   } else {
       result = -1;
   }
   return int_stack_push(stk, result);
   
}

void int_stack_print(int_stack_t *stk, FILE *file) {
    int_entry_t *entry;
    int pos = 0;
    if (stk->size == 0) {
        fprintf(file, "empty stack\n");
    }

    SLIST_FOREACH(entry, &stk->head, entries) {
        fprintf(file, "%d: %d ", pos, entry->value);
        pos++;
    }
    printf("\n");
}

int int_stack_size(int_stack_t* stk) {
    return stk->size;
}

int int_stack_capacity(int_stack_t* stk) {
    return stk->capacity;
}
