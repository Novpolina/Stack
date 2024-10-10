#include "stack.h"



int main()
{
    stack my_stack = {};
    Errors err = VSE_ZAYEBIS;
    stack_element element = 0;
    CHECK_STACK_(StackInit, &my_stack, 1);
    CHECK_STACK_(StackPush, &my_stack, 5);
    CHECK_STACK_(StackPush, &my_stack, 20);
    CHECK_STACK_(StackPush, &my_stack, 20);
    STACK_DUMP(&my_stack, err);

    CHECK_STACK_(StackPush, &my_stack, 5);
    CHECK_STACK_(StackPop, &my_stack, &element);
    STACK_DUMP(&my_stack, err);

    StackDestroy(&my_stack);
    return 0;
}