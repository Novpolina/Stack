#include "stack.h"



int main()
{
    stack my_stack = {};

    StackInit(&my_stack, 20);
    StackDump(&my_stack);
    StackPush(&my_stack, 20);
    StackPush(&my_stack, 5);
    StackPush(&my_stack, 3);
    stack_element num = 0;
    StackPop(&my_stack, &num);
    StackDump(&my_stack);
    StackDestroy(&my_stack);




    return 0;
}