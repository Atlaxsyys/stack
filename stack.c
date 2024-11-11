#include <stdio.h>
#include <stdlib.h>

typedef double stackElem;

struct stack
{
    stackElem* data;
    int size;
    int capasity;
};

enum errors
{
    STACK_IS_OK = 0,

    STACK_DATA_IS_NULL,

    STACK_COPASITY_LESS_SIZE,

    STACK_SIZE_IS_ERROR,

    STACK_CAPASITY_IS_ERROR
};

int stack_constructor(struct stack* stk, int capasity);
int stack_destroy(struct stack* stk);
int stack_dump(struct stack* stk);
int stack_error(struct stack* stk);
void stack_realloc(struct stack* stk);
int stack_push (struct stack* stk, stackElem number);
int stack_pop(struct stack* stk, int *temp);

const int POIZON_NUMBER = -666;

int main (void)
{
    struct stack stk = {};
    stack_constructor(&stk, 2);
    
    int temp = 0;

    stack_push(&stk, 10);
    stack_dump(&stk);
    
    stack_push(&stk, 20);
    stack_dump(&stk);

    stack_push(&stk, 30);
    stack_dump(&stk);

    stack_push(&stk, 40);
    stack_dump(&stk);

    stack_pop(&stk, &temp);
    stack_dump(&stk);
    
    stack_pop(&stk, &temp);
    stack_dump(&stk);

    stack_push(&stk, 50);
    stack_dump(&stk);

}


int stack_constructor(struct stack* stk, int capasity)
{
    stk->data = (stackElem*) calloc(capasity, sizeof(stackElem));
    stk->capasity = capasity;
    stk->size = 0;
    return 0;
}

int stack_destroy(struct stack* stk)
{
    free(stk->data);
    stk->size = -1;
    stk->capasity = -1;
    stk->data = NULL;
    return 0;
}

int stack_dump(struct stack* stk)
{
    for (int i = 0; i < stk->capasity; i++)
        printf ("%g  ", stk->data[i]);

    printf("\n\nstack->data adress: %p\n", stk->data);
    printf("stack->capasity:    %d\n", stk->capasity);
    printf("stack->size:        %d\n", stk->size);

    getchar();
}

int stack_error(struct stack* stk)
{
    int error = 0;
    if (stk->data == NULL)
    {
        error = STACK_DATA_IS_NULL;
    }
    else if(stk->size >= stk->capasity)
    {
        error = STACK_COPASITY_LESS_SIZE;
    }
    else if (stk->size < 0)
    {
        error = STACK_SIZE_IS_ERROR;
    }
    else if (stk->capasity < 0)
    {
        error = STACK_CAPASITY_IS_ERROR;
    }

    return error;
}
void stack_realloc(struct stack* stk)
{
    stk->capasity *= 2;
    
    stk->data = (stackElem*) realloc (stk->data, stk->capasity * sizeof (stk->data[0]));

    for (int i = 0; i < stk->size; i++)
        stk->data[stk->size + i] = POIZON_NUMBER;

}
int stack_push (struct stack* stk, stackElem number)
{
    if (stk->capasity <= stk->size)
    {
        stack_realloc(stk);
    }

    stk->data[stk->size] = number;
    stk->size++;
}

int stack_pop(struct stack* stk, int *temp)
{
    *temp = stk->data[stk->size - 1];
    stk->data[--stk->size] = POIZON_NUMBER;
}