#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

typedef double stackElem;
typedef unsigned long hash_elem;

struct stack
{
    int deleted_value = -666;
    stackElem* data;
    int size;
    int capacity;
    hash_elem hash;
};

enum errors
{
    STK_IS_NULL = 1,

    STACK_DATA_IS_NULL = 2,

    STACK_CAPACITY_LESS_SIZE = 4,

    STACK_SIZE_IS_ERROR = 8,

    STACK_CAPACITY_IS_ERROR = 16,

    CANARY_START_CHANGE = 32,

    CANARY_END_CHANGE = 64
};

int stack_constructor(struct stack* stk, int capasity);
int stack_destroy(struct stack* stk);
int stack_dump(struct stack* stk);
int stack_error(struct stack* stk);
int error_output(int errors);
int stack_assert(struct stack* stk);
void stack_realloc(struct stack* stk);
int stack_push (struct stack* stk, stackElem number);
int stack_pop(struct stack* stk);
hash_elem hash_djb2 (const char* str, size_t size_of_str);
int convert_to_binary (int n);

#endif // STACK_H_ 