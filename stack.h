#include <stdio.h>

struct stack{
    double* data;
    size_t size;
    size_t capacity;
};

struct error{
    int name_of_err;
    char* file;
    int function;
    int number_of_line;
};

enum NAMES_OF_ERRORS{
    VSE_ZAYEBIS,
    NULL_POINTER_OF_STACK,
    NULL_POINTER_OF_STACK_IN_INIT,
    NULL_POINTER_OF_DATA,
    WRONG_CANARY,
    WRONG_HASH,
    WRONG_NAME_OF_CHECK_OPTION

};
enum FUNCTIONS{
    INIT,
    POP,
    PUSH,
    DUMP,
    DESTROY,
    CHECK
};

enum WHAT_TO_CHECK{
    CHECK_ALL,
    CHECK_NULL_POINTERS,
    CHECK_CAPACITY,
    CHECK_SIZE,
    CHECK_CANARY,
    CHECK_HASH

};

typedef double stack_element;
typedef double canary;

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



error StackInit(stack * stk, size_t capacity);

error StackPush(stack* my_stack, stack_element new_element );

error StackPop(stack* my_stack, stack_element* pop_element);

error StackDump(stack* my_stack);

error StackDestroy(stack* my_stack);

void ErrorPrint(error error);


