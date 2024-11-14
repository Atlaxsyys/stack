#include "stack.h"

int main(void)
{
    struct stack stk = {};
    stack_constructor(&stk, 2);

    int temp = 0;
    
    stack_error(&stk);
    stack_push(&stk, 10);
    stack_error(&stk);
    stack_dump(&stk);

    stack_error(&stk);
    stack_push(&stk, 20);
    stack_error(&stk);
    stack_dump(&stk);

    stack_error(&stk);
    stack_push(&stk, 30);
    stack_error(&stk);
    stack_dump(&stk);

    stack_error(&stk);
    stack_push(&stk, 40);
    stack_error(&stk);
    stack_dump(&stk);

    stack_error(&stk);
    stack_pop(&stk, &temp);
    stack_error(&stk);
    stack_dump(&stk);
    
    stack_error(&stk);
    stack_pop(&stk, &temp);
    stack_error(&stk);
    stack_dump(&stk);

    stack_error(&stk);
    stack_push(&stk, 50);
    stack_error(&stk);
    stack_dump(&stk);
}