#include "stack.h"
#include <stdio.h>


int main(void)
{

    struct stack stk = {};
    stack_constructor(&stk, 2);
    stack_dump(&stk);
    
    stack_push(&stk, 10);
    stack_dump(&stk);

    stack_push(&stk, 20);
    stack_dump(&stk);

    stack_push(&stk, 30);
    stack_dump(&stk);

    stack_push(&stk, 40);
    stack_dump(&stk);

    stack_pop(&stk);
    stack_dump(&stk);
    
    stack_pop(&stk);
    stack_dump(&stk);

    stack_push(&stk, 50);
    stack_dump(&stk);
}