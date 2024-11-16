#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "colour.h"


const stackElem POIZON_NUMBER = -666;

const stackElem CANARY_START = 0xBAD;
const stackElem CANARY_END   = 0xDED;


int stack_constructor(struct stack* stk, int capacity)
{
    assert(stk);

    stk->data = (stackElem*) calloc(capacity + 2, sizeof(stackElem));
    stk->capacity = capacity;
    stk->size = 0;

    stk->data[0] = CANARY_START;
    stk->data[capacity + 1] = CANARY_END;

    for (int i = 0; i <= capacity; i++)
    {
        stk->data[stk->size + i] = POIZON_NUMBER;
    }
    stack_assert(stk);

    return 0;
}

int stack_destroy(struct stack* stk)
{
    free(stk->data);
    stk->size = -1;
    stk->capacity = -1;
    stk->data = NULL;

    return 0;
}

int stack_dump(struct stack* stk)
{
    printf(YELLOW "______________________________________________________\n" CLEAR);
    printf(GREEN "CANARY_START = %g\n" CLEAR, CANARY_START);
    for (int i = 1; i <= stk->capacity; i++)
        printf (BLUE "stack->data[%d] = %g\n" CLEAR, i, stk->data[i]);

    printf(GREEN "CANARY_END = %g\n" CLEAR, CANARY_END);

    printf(RED "\n\nstack->data adress: %p\n" CLEAR, stk->data);
    printf(PURPLE "stack->capacity:    %d\n" CLEAR, stk->capacity);
    printf(PURPLE"stack->size:        %d\n" CLEAR, stk->size);
    printf(YELLOW "______________________________________________________\n\n" CLEAR);

    getchar();

    return 0;
}

int stack_assert(struct stack* stk)
{
    int errors = stack_error(stk);

    if (errors != 0)
    {
        stack_dump(stk);
        assert(0);
    }

}

int stack_error(struct stack* stk)
{
    int errors = 0;

    if(stk == NULL)
    {
        fprintf(stderr, "Error is %d\n", STK_IS_NULL);
        errors++;
    }
    if (stk->data == NULL)
    {
        fprintf(stderr, "Error is %d\n", STACK_DATA_IS_NULL);
        errors++;
    }
    if(stk->size > stk->capacity)
    {
        fprintf(stderr, "Error is %d\n", STACK_CAPACITY_LESS_SIZE);
        errors++;
    }
    if (stk->size < 0)
    {
        fprintf(stderr, "Error is %d\n", STACK_SIZE_IS_ERROR);
        errors++;
    }
    if (stk->capacity < 0)
    {
        fprintf(stderr, "Error is %d\n", STACK_CAPACITY_IS_ERROR);
        errors++;
    }

    return errors;
}

void stack_realloc(struct stack* stk)
{
    stk->capacity *= 2;
    
    stk->data = (stackElem*) realloc (stk->data, stk->capacity * sizeof (stk->data[0]));

    for (int i = stk->size + 1; i <= stk->capacity; i++)
        stk->data[i] = POIZON_NUMBER;

}

int stack_push(struct stack* stk, stackElem number)
{
    stack_assert(stk);

    if (stk->capacity <= stk->size)
    {
        stack_realloc(stk);
    }

    stk->data[stk->size + 1] = number;
    stk->size++;

    stack_assert(stk);
    
    return 0;
}

int stack_pop(struct stack* stk, int *temp)
{
    stack_assert(stk);
    
    stk->size--;
    *temp = stk->data[stk->size + 1];
    stk->data[stk->size + 1] = POIZON_NUMBER;

    stack_assert(stk);
    return 0;
}