#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <cstdint>
typedef double stack_element;
typedef double canary_element;
typedef int64_t hash_element ;


#ifndef NDEBUG
  #define ON_DEBUG(...) __VA_ARGS__
#else
  #define ON_DEBUG(...)
#endif  //NDEBUG

struct info{
    char* file;
    char* name_of_function;
    int number_of_line;
};

struct stack{
    canary_element first_canary_for_stack;

    //info function_info;
    info main_info;

    stack_element* data;
    size_t size;
    size_t capacity;

    hash_element hash_data;
    hash_element hash_stack;

    canary_element last_canary_for_stack;
};

enum Errors{
    VSE_ZAYEBIS,
    NULL_POINTER_OF_STACK,
    NULL_POINTER_OF_DATA,
    WRONG_CANARY,
    WRONG_HASH_OF_DATA,
    WRONG_HASH_OF_STACK,
    WRONG_NAME_OF_CHECK_OPTION

};
enum Functions{
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
typedef double canary_element;

#define CHECK_STACK_(function, my_stack, element) CHECK_(function, __LINE__, __FILE__, my_stack, element)

#define CHECK_(function, __LINE__, __FILE__, my_stack, element)  (my_stack) -> main_info.file = __FILE__;         \
                                                        (my_stack) -> main_info.number_of_line = __LINE__;    \
                                                        (my_stack) -> main_info.name_of_function = (char*)__func__;          \
                                                        if(err == VSE_ZAYEBIS) {                                \
                                                          err = function(my_stack, element);\
                                                          }                     \

#define STACK_DUMP(stk, err) StackDump(stk, err ON_DEBUG(,  __FILE__, (char *)__func__, __LINE__) ) 


info MakeInfo(char* file, char * function, int number_of_line);
Errors StackInit(stack * my_stack, size_t capacity);
Errors StackPush(stack* my_stack, stack_element new_element );
Errors StackPop(stack* my_stack, stack_element* pop_element) ;
void StackDump(stack* my_stack, Errors err ON_DEBUG(, char* file, char * function, int number_of_line) );
void StackDestroy(stack* my_stack) ;
Errors StackCheck(stack* my_stack, const int what_to_check);
hash_element CountHashOfStack(stack* my_stack) ;
hash_element CountHashOfData(stack* my_stack) ;
hash_element fnv1aHash(const void* data, size_t size);
hash_element djb2_hash(const void* data, size_t size);



