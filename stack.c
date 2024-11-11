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
    printf("______________________________________________________\n");
    for (int i = 0; i < stk->capasity; i++)
        printf ("\033[34mstack->data[%d] = %g  \033[0m\n",i, stk->data[i]);

    printf("\n\n\033[31mstack->data adress: %p\033[0m\n", stk->data);
    printf("\033[35mstack->capasity:    %d\033[0m\n", stk->capasity);
    printf("\033[35mstack->size:        %d\033[0m\n", stk->size);
    printf("______________________________________________________\n\n");

    getchar();
}

int stack_error(struct stack* stk)
{
    int error = 0;
    if (stk->data == NULL)
    {
        printf("Error is %d\n", STACK_DATA_IS_NULL);
    }
    if(stk->size > stk->capasity)
    {
        printf("Error is %d\n", STACK_COPASITY_LESS_SIZE);
    }
    if (stk->size < 0)
    {
        printf("Error is %d\n", STACK_SIZE_IS_ERROR);
    }
    if (stk->capasity < 0)
    {
        printf("Error is %d\n", STACK_CAPASITY_IS_ERROR);
    }

    return 1;
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