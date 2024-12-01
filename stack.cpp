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

    for (int i = 1; i <= capacity; i++)
    {
        stk->data[stk->size + i] = POIZON_NUMBER;
    }

    stk->hash = hash_djb2((const char*) stk, sizeof(*stk));
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
    printf(GREEN "CANARY_START = %g\n" CLEAR, stk->data[0]);
    for (int i = 1; i <= stk->capacity; i++)
        printf (BLUE "stack->data[%d] = %g\n" CLEAR, i, stk->data[i]);

    printf(GREEN "CANARY_END = %g\n" CLEAR, stk->data[stk->capacity + 1]);

    printf(RED "\n\nstack->data adress: %p\n" CLEAR, stk->data);
    printf(PURPLE "stack->capacity:    %d\n" CLEAR, stk->capacity);
    printf(PURPLE"stack->size:        %d\n" CLEAR, stk->size);
    printf(PURPLE"last deleted_value: %d\n" CLEAR, stk->deleted_value);
    printf(RED "hash:               %lu\n" CLEAR,  stk->hash);
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

    return 0;
}

int stack_error(struct stack* stk)
{
    int errors = 0;

    if(stk == NULL)
    {
        errors |= STK_IS_NULL;
    }
    if (stk->data == NULL)
    {
        errors |= STACK_DATA_IS_NULL;
    }
    if(stk->size > stk->capacity)
    {
        errors |= STACK_CAPACITY_LESS_SIZE;
    }
    if (stk->size < 0)
    {
        errors |= STACK_SIZE_IS_ERROR;
    }
    if (stk->capacity < 0)
    {
        errors |= STACK_CAPACITY_IS_ERROR;
    }
    if (stk->data[0] != CANARY_START)
    {
        errors |= CANARY_START_CHANGE;
    }
    if (stk->data[stk->capacity + 1] != CANARY_END)
    {
        errors |= CANARY_END_CHANGE;
    }

    return errors;
}

int error_output(int errors)
{
    printf("Error:");

    convert_to_binary (errors);

    switch(errors)
    {
        case STK_IS_NULL:
            printf(RED " - STK_IS_NULL" CLEAR);
            break;
        case STACK_DATA_IS_NULL:
            printf(RED " - STACK_DATA_IS_NULL" CLEAR);
            break;
        case STACK_CAPACITY_LESS_SIZE:
            printf(RED " - STACK_CAPACITY_LESS_SIZE" CLEAR);
            break;
        case STACK_SIZE_IS_ERROR:
            printf(RED " - STACK_SIZE_IS_ERROR" CLEAR);
            break;
        case STACK_CAPACITY_IS_ERROR:
            printf(RED " - STACK_CAPACITY_IS_ERROR" CLEAR);
            break;
        case CANARY_START_CHANGE:
            printf(RED " - CANARY_START_CHANGE" CLEAR);
            break;
        case CANARY_END_CHANGE:
            printf(RED " - CANARY_END_CHANGE" CLEAR);
            break;
        default:
            printf(RED " - UNKNOWN ERROR" CLEAR);
        
    }

    return 0;
}

void stack_realloc(struct stack* stk)
{
    const int scale_factor = 2;

    stk->capacity *= scale_factor;
    
    stk->data = (stackElem*) realloc (stk->data, stk->capacity * sizeof (stk->data[0]));

    for (int i = stk->size + 1; i <= stk->capacity; i++)
        stk->data[i] = POIZON_NUMBER;

    stk->data[stk->capacity + 1] = CANARY_END; 

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

    stk->hash = hash_djb2((const char*) stk, sizeof(*stk));

    stack_assert(stk);
    
    return 0;
}

int stack_pop(struct stack* stk)
{
    stack_assert(stk);
    
    stk->size--;
    stk->deleted_value = stk->data[stk->size + 1];
    stk->data[stk->size + 1] = POIZON_NUMBER;

    stk->hash = hash_djb2((const char*) stk, sizeof(*stk));

    stack_assert(stk);

    return 0;
}

hash_elem hash_djb2 (const char* str, size_t size_of_str)
{
    hash_elem hash = 5381;

    for (size_t i = 0; i < size_of_str; i++)
    {
        hash_elem a = (hash_elem) *str++;
        hash = ((hash << 5) + hash) + a;
    }

    return hash;
}

int convert_to_binary (int n)
{
    if (n > 1) 
        convert_to_binary(n / 2);

    printf(RED "%d", (int) n % 2);

    return 0;
}

