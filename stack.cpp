#include <stdio.h>
#include "stack.h"         
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

const stack_element DEFAULT_VALUE= 0xC6E5EDFF20;

ERRORS StackInit(stack * stk, size_t capacity) {

    stk->data       = (stack_element*)malloc(capacity * sizeof(stack_element));
    stk -> capacity = capacity;
    stk -> size     = 0;

    for(int i = 0; i < capacity; i++){
        stk->data[i] = DEFAULT_VALUE;
    }

    return VSE_ZAYEBIS;

}

ERRORS StackPush(stack* my_stack, stack_element new_element ) {

    if (my_stack->size == my_stack->capacity) {

        my_stack->capacity = my_stack->capacity * 2;
        my_stack->data     = (stack_element*)realloc(my_stack->data, my_stack->capacity * sizeof(stack_element)); 
    
    } 
    printf(" push: %lf \n", new_element);


    my_stack -> data[my_stack -> size] = new_element;

    my_stack -> size++;

    return VSE_ZAYEBIS;

}

ERRORS StackPop(stack* my_stack, stack_element* pop_element) {

    if(my_stack -> size - 1 < my_stack -> capacity / 4) {

        my_stack->capacity = my_stack->capacity / 4;

        my_stack->data = (stack_element*)realloc(my_stack->data, my_stack->capacity * sizeof(stack_element));

    }


    *pop_element =  my_stack->data[my_stack->size - 1];
    printf(" pop: %lf \n ", pop_element);
    StackDump(my_stack);

    
    my_stack->data[my_stack->size - 1] = DEFAULT_VALUE;

    my_stack->size--;

    return VSE_ZAYEBIS;

}

ERRORS StackDump(stack* my_stack) {

    printf("\n \n%s \n", "Derzhite vash stack:");

    printf("\t%s\n", "Sam stack:");

    size_t i = 0;
    for(; i < my_stack->size; i++) {
        printf("\t\t[%zu]: %lf \n", i, my_stack->data[i]);

    }
    for(;i < my_stack->capacity; i++) {

        printf("\t\t[%zu]: %lf  - POISON\n", i, my_stack->data[i]);
    }

    printf("\t Size: %zu \n", my_stack->size);
    printf("\t Capacity: %zu \n", my_stack->capacity);

}

ERRORS StackDestroy(stack* my_stack) {

    free(my_stack->data);

}