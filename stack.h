#ifndef _STACK_H_
#define _STACK_H_

typedef double stackElem;

struct stack
{
    stackElem* data;
    int size;
    int capacity;
};

enum errors
{
    STK_IS_NULL = 0,

    STACK_IS_OK,

    STACK_DATA_IS_NULL,

    STACK_CAPACITY_LESS_SIZE,

    STACK_SIZE_IS_ERROR,

    STACK_CAPACITY_IS_ERROR
};

int stack_constructor(struct stack* stk, int capasity);
int stack_destroy(struct stack* stk);
int stack_dump(struct stack* stk);
int stack_error(struct stack* stk);
int stack_assert(struct stack* stk);
void stack_realloc(struct stack* stk);
int stack_push (struct stack* stk, stackElem number);
int stack_pop(struct stack* stk, int *temp);

#endif // _STACK_H_ 