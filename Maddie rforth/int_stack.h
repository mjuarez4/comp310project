// int_stack.h - interface to the int_stack

#ifndef INT_STACK_H
#define INT_STACK_H

#include <stdio.h>
#include <sys/queue.h>

typedef struct int_entry {
    int value;
    SLIST_ENTRY(int_entry) entries;
} int_entry_t;

typedef struct int_stack {
    SLIST_HEAD(stackhead, int_entry) head;
    int size;
    int capacity;
} int_stack_t;

extern void int_stack_init(int_stack_t *stk, int capacity);
extern int int_stack_push(int_stack_t *stk, int value);
extern int int_stack_pop(int_stack_t *stk, int *top_value);
extern int int_stack_top(int_stack_t *stk, int *top_value);
extern int int_stack_dup(int_stack_t *stk);
extern int int_stack_swap(int_stack_t *stk);
extern int int_stack_add(int_stack_t *stk);
extern void int_stack_print(int_stack_t *stk, FILE *file);
extern int int_stack_size(int_stack_t* stk);
extern int int_stack_capacity(int_stack_t* stk);
extern int int_stack_subtract(int_stack_t *stk);
extern int int_stack_mult(int_stack_t *stk);
extern int int_stack_div(int_stack_t *stk);
extern int int_stack_over(int_stack_t *stk);
extern int int_stack_rot(int_stack_t *stk);
extern int int_stack_2swap(int_stack_t *stk);
extern int int_stack_2dup(int_stack_t *stk);
extern int int_stack_2over(int_stack_t *stk);
extern int int_stack_mod(int_stack_t *stk);
extern int int_stack_divmod(int_stack_t *stk);
extern int int_stack_equal(int_stack_t *stk);
extern int int_stack_less(int_stack_t *stk);
extern int int_stack_greater(int_stack_t *stk);
extern int int_stack_and(int_stack_t *stk);
extern int int_stack_or(int_stack_t *stk);
extern int int_stack_invert(int_stack_t *stk);
#endif // INT_STACK_H

