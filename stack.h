#include <stdio.h>

struct stack{
    double* data;
    size_t size;
    size_t capacity;
};

enum ERRORS{
    VSE_ZAYEBIS,
    NULL_POINTER,


};

typedef double stack_element;
#define MAKE_ERROR int error = VSE_ZAYEBIS;
#define STACK_PUSH(my_stack, new_element)           error = StackPush(my_stack, new_element);       \
                                                        if(error != VSE_ZAYEBIS){                   \
                                                            ErrorPrint(error);                      \
                                                        }                                           \

#define STACK_POP(my_stack, pop_element)            error = StackPop(my_stack, pop_element);        \
                                                        if(error != VSE_ZAYEBIS){                   \
                                                        ErrorPrint(error);                          \
                                                    }                                               \

#define STACK_INIT(my_stack, capacity, line, file)  error = StackInit(my_stack, capacity, line, file);  



ERRORS StackInit(stack * stk, size_t capacity);

ERRORS StackPush(stack* my_stack, stack_element new_element );

ERRORS StackPop(stack* my_stack, stack_element* pop_element);

ERRORS StackDump(stack* my_stack);

ERRORS StackDestroy(stack* my_stack);

void ErrorPrint(ERRORS error);


