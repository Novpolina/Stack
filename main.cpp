#include "stack.h"



int main()
{
    stack my_stack = {};
    error err = MakeErr(VSE_ZAYEBIS, 0, 0, 0);

    StackInit(&my_stack, 20);
    StackDump(&my_stack, err);
    StackPush(&my_stack, 20);
    StackPush(&my_stack, 5);
    StackPush(&my_stack, 3);
    stack_element num = 0;
    StackPop(&my_stack, &num);
    StackDump(&my_stack, err);
    StackDestroy(&my_stack);




    return 0;
}