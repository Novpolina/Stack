#include <stdio.h>
#include "stack.h"         
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>


const stack_element DEFAULT_VALUE= 0xC6E5EDFF20;

const stack_element CANARY_VALUE = 0xD1EEEBEDF6E5;

const size_t NUM_OF_CANARY = 2;

//миша, не хейти конструкторы пжпжпж, мне реально так удобнее структуру создавать, чтоб подсказывало, что следующим элементом писать
error MakeErr(int name_of_err, char* file, int function, int number_of_line){

    error err = {};
    err.name_of_err = name_of_err;
    err.file = file;
    err.function = function;
    err.number_of_line = number_of_line;
    return err;

}

error StackInit(stack * my_stack, size_t capacity) {

    error err  = MakeErr(Stack_Check(my_stack, CHECK_NULL_POINTERS), __FILE__, INIT,  __LINE__);

    if(err.name_of_err != VSE_ZAYEBIS){

        return err;

    }

    my_stack->data       = (stack_element*)malloc(capacity * sizeof(stack_element));
    my_stack -> capacity = capacity;
    my_stack -> size     = 0;


    for(int i = 0; i < capacity; i++) {
        my_stack->data[i] = DEFAULT_VALUE;
    }
    err = MakeErr(Stack_Check(my_stack, CHECK_ALL), __FILE__, INIT,  __LINE__);

    return err;

}

error StackPush(stack* my_stack, stack_element new_element ) {
    error err;

    if (my_stack->size == my_stack->capacity) {

        my_stack->capacity = my_stack->capacity * 2;
        my_stack->data     = (stack_element*)realloc(my_stack->data, my_stack->capacity * sizeof(stack_element)); 
    
    } 
    printf(" push: %lf \n", new_element);


    my_stack -> data[my_stack -> size] = new_element;

    my_stack -> size++;
    err = MakeErr(Stack_Check(my_stack, CHECK_ALL), __FILE__, INIT,  __LINE__);

    return err;

}

error StackPop(stack* my_stack, stack_element* pop_element) {

    error err  = MakeErr(Stack_Check(my_stack, CHECK_NULL_POINTERS), __FILE__, INIT,  __LINE__);

    if(err.name_of_err != VSE_ZAYEBIS){

        return err;

    }



    if(my_stack -> size - 1 < my_stack -> capacity / 4) {

        my_stack->capacity = my_stack->capacity / 4;

        my_stack->data = (stack_element*)realloc(my_stack->data, my_stack->capacity * sizeof(stack_element));

    }


    *pop_element =  my_stack->data[my_stack->size - 1];
    printf(" pop: %lf \n ", pop_element);
    StackDump(my_stack);

    
    my_stack->data[my_stack->size - 1] = DEFAULT_VALUE;

    my_stack->size--;

    err = MakeErr(Stack_Check(my_stack, CHECK_ALL), __FILE__, INIT,  __LINE__);

    return err;

}

void StackDump(stack* my_stack, error err) {

    printf("\n \n%s \n", "Derzhite vash stack:");


    if(err.name_of_err == NULL_POINTER_OF_STACK){
        printf("\n \t Pizdez, steka ne suschestvuet \n");
        printf("\n \t Oshibka v faile %s \n \t \t v funkzii %s \n \t \t na %i stroke ", err.file, err.function, err.number_of_line);

    }
    else{
        if (err.name_of_err == NULL_POINTER_OF_DATA){
            printf("\n Pizdez pomenbshe, data ne sushestvuet \n");
            printf("\n \t Oshibka v faile %s \n \t \t v funkzii %s \n \t \t na %i stroke ", err.file, err.function, err.number_of_line);
        }
        else {
            if(err.name_of_err == WRONG_CANARY){

            }
            else if(err.name_of_err == WRONG_HASH){

            }
            else if (err.name_of_err == VSE_ZAYEBIS){
                size_t i = 0;
                printf("\t%s\n", "Sam stack:");
                for(; i < my_stack->size; i++) {
                    printf("\t\t[%zu]: %lf \n", i, my_stack->data[i]);

                }
                for(;i < my_stack->capacity; i++) {

                    printf("\t\t[%zu]: %lf  - POISON\n", i, my_stack->data[i]);
                }

            }

        

        }
        printf("\t Size: %zu \n", my_stack->size);
        printf("\t Capacity: %zu \n", my_stack->capacity);


    }




}

error StackDestroy(stack* my_stack) {


    error err  = MakeErr(Stack_Check(my_stack, CHECK_NULL_POINTERS), __FILE__, INIT,  __LINE__);

    if(err.name_of_err != VSE_ZAYEBIS){

        return err;

    }


    free(my_stack->data);

    return err;

}

NAMES_OF_ERRORS Stack_Check(stack* my_stack, const int what_to_check){

    switch (what_to_check)
    {
    case CHECK_ALL:
        /* code */
        break;
    case CHECK_NULL_POINTERS:
        if(!my_stack){
            return NULL_POINTER_OF_STACK;

        }
        else if(!my_stack->data){
            return NULL_POINTER_OF_DATA;
        }
         
        break;
    case CHECK_CAPACITY:
        /* code */
        break;
    case CHECK_CANARY:
        /* code */
        break;
    case CHECK_HASH:
        /* code */
        break;
    
    default:
        return WRONG_NAME_OF_CHECK_OPTION;
        
    }
    return VSE_ZAYEBIS;


}
