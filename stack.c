#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "colour.h"


enum errors
{
    STACK_IS_OK = 0,

    STACK_DATA_IS_NULL,

    STACK_CAPACITY_LESS_SIZE,

    STACK_SIZE_IS_ERROR,

    STACK_CAPACITY_IS_ERROR
};

const int POIZON_NUMBER = -666;

int stack_constructor(struct stack* stk, int capacity)
{
    assert(stk != NULL);
    stk->data = (stackElem*) calloc(capacity, sizeof(stackElem));
    assert(stk->data != NULL);
    stk->capacity = capacity;
    stk->size = 0;

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
    for (int i = 0; i < stk->capacity; i++)
        printf (BLUE "stack->data[%d] = %g\n" CLEAR, i, stk->data[i]);

    printf(RED "\n\nstack->data adress: %p\n" CLEAR, stk->data);
    printf(PURPLE "stack->capacity:    %d\n" CLEAR, stk->capacity);
    printf(PURPLE"stack->size:        %d\n" PURPLE, stk->size);
    printf(YELLOW "______________________________________________________\n\n" CLEAR);

    getchar();

    return 0;
}

int stack_error(struct stack* stk)
{
    int error = 0;
    if (stk->data == NULL)
    {
        fprintf(stderr, "Error is %d\n", STACK_DATA_IS_NULL);
    }
    if(stk->size > stk->capacity)
    {
        fprintf(stderr,"Error is %d\n", STACK_CAPACITY_LESS_SIZE);
    }
    if (stk->size < 0)
    {
        fprintf(stderr, "Error is %d\n", STACK_SIZE_IS_ERROR);
    }
    if (stk->capacity < 0)
    {
        fprintf(stderr, "Error is %d\n", STACK_CAPACITY_IS_ERROR);
    }

    return 1;
}

void stack_realloc(struct stack* stk)
{
    stk->capacity *= 2;
    
    stk->data = (stackElem*) realloc (stk->data, stk->capacity * sizeof (stk->data[0]));

    for (int i = 0; i < stk->size; i++)
        stk->data[stk->size + i] = POIZON_NUMBER;

}

int stack_push(struct stack* stk, stackElem number)
{
    if (stk->capacity <= stk->size)
    {
        stack_realloc(stk);
    }

    stk->data[stk->size] = number;
    stk->size++;
    
    return 0;
}

int stack_pop(struct stack* stk, int *temp)
{
    *temp = stk->data[stk->size - 1];
    stk->data[--stk->size] = POIZON_NUMBER;

    return 0;
}