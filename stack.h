typedef double stackElem;

struct stack
{
    stackElem* data;
    int size;
    int capacity;
};

int stack_constructor(struct stack* stk, int capasity);
int stack_destroy(struct stack* stk);
int stack_dump(struct stack* stk);
int stack_error(struct stack* stk);
void stack_realloc(struct stack* stk);
int stack_push (struct stack* stk, stackElem number);
int stack_pop(struct stack* stk, int *temp);