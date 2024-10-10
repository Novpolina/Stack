#include <stdio.h>
#include "stack.h"         
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>


const stack_element DEFAULT_VALUE= 597696;

const stack_element CANARY_VALUE = 66585665;

const size_t NUM_OF_CANARY = 2;
Errors error = VSE_ZAYEBIS;


#define PROTECT_NULL_POINTER    error = StackCheck(my_stack, NULL_POINTER_OF_STACK);    \
                                if(error != VSE_ZAYEBIS){                                      \
                                    STACK_DUMP(my_stack, error);                                \
                                    return error; \
                                }                                                                \


#define PROTECT_ALL             error = StackCheck(my_stack, CHECK_ALL);   \
                                if(error != VSE_ZAYEBIS){                         \
                                    STACK_DUMP(my_stack, error);                   \
                                    return error;                                 \
                                }                                                 \
//миша, не хейти конструкторы пжпжпж, мне реально так удобнее структуру создавать, чтоб подсказывало, что следующим элементом писать
info MakeInfo(char* file, char * function, int number_of_line){

    info info = {};

    info.file = file;
    info.name_of_function = function;
    info.number_of_line = number_of_line;

    return info;

}

Errors StackInit(stack * my_stack, size_t capacity) {
    my_stack->first_canary_for_stack = CANARY_VALUE;
    my_stack->last_canary_for_stack = CANARY_VALUE;
    //printf("ghviycyfc");

    PROTECT_NULL_POINTER;


    my_stack->data       = (stack_element*)malloc(capacity * sizeof(stack_element) + NUM_OF_CANARY * sizeof(canary_element));
    *(canary_element*)((char*)my_stack->data) = CANARY_VALUE;
    *(canary_element*)((char*)my_stack->data + sizeof(stack_element) * capacity + sizeof(canary_element) ) = CANARY_VALUE;
    my_stack->data = (stack_element*)((char*)my_stack->data + sizeof(canary_element));

    my_stack -> capacity = capacity;
    my_stack -> size     = 0;

    for(int i = 0; i < capacity; i++) {
        my_stack->data[i] = DEFAULT_VALUE;
    }
    my_stack->hash_data = CountHashOfData(my_stack);
    my_stack->hash_stack = CountHashOfStack(my_stack);
    //printf("\niuiycturci62\n");

    PROTECT_ALL;
    //printf("64");

    return VSE_ZAYEBIS;

}

Errors StackPush(stack* my_stack, stack_element new_element ) {
    //printf("hgvyufcturx");

    PROTECT_NULL_POINTER;

    if (my_stack->size == my_stack->capacity) {
        //fprintf(stderr, "size = %zu\ncapasity = %zu\n", my_stack -> capacity, my_stack -> size);
        my_stack->capacity = my_stack->capacity * 2;
         //printf("\nFBHVDHUou\n");
        my_stack->data = (stack_element*)((char*)my_stack->data - sizeof(canary_element));
         //fprintf(stderr, "\nFBHVDHUou\n");
        my_stack->data = (stack_element*) realloc(my_stack->data, my_stack->capacity * sizeof(stack_element) + NUM_OF_CANARY * sizeof(canary_element)); 
         //printf("\nFBHVDHUou\n");
        my_stack->data = (stack_element*)((char*)my_stack->data + sizeof(canary_element));
        //printf("IBVUYTCTCUC");
        *(canary_element*)((char*)my_stack->data + sizeof(stack_element) * my_stack->capacity ) = CANARY_VALUE;

    
    } 

    my_stack -> data[my_stack -> size] = new_element;

    my_stack -> size++;
    my_stack->hash_data = CountHashOfData(my_stack);
    my_stack->hash_stack = CountHashOfStack(my_stack);
    //printf("\nriofboerbou size = %i\n", my_stack->size);
    
    // err = MakeErr(StackCheck(my_stack, CHECK_ALL), __FILE__, INIT,  __LINE__);
    // StackDump(my_stack, err);
    PROTECT_ALL;
    //printf("\n\n1234567890\n\n");

    return VSE_ZAYEBIS;

}

Errors StackPop(stack* my_stack, stack_element* pop_element) {

    PROTECT_ALL;

    if(my_stack -> size - 1 < my_stack -> capacity / 4) {

        my_stack->capacity = my_stack->capacity / 4;

        my_stack->data = my_stack->data - sizeof(canary_element);
        my_stack->data = (stack_element*)realloc(my_stack->data, my_stack->capacity * sizeof(stack_element) + NUM_OF_CANARY * sizeof(canary_element));
        my_stack->data = my_stack->data + sizeof(canary_element);

    }


    *pop_element =  my_stack->data[my_stack->size - 1];


    my_stack->data[my_stack->size - 1] = DEFAULT_VALUE;

    my_stack->size--;
    my_stack->hash_data = CountHashOfData(my_stack);
    my_stack->hash_stack = CountHashOfStack(my_stack);

    PROTECT_ALL;
    

    return VSE_ZAYEBIS;

}

void StackDump(stack* my_stack, Errors err ON_DEBUG(, char* file, char * function, int number_of_line) ) {

    FILE* log_file = fopen("log_file.txt", "w");

    ON_DEBUG(


    fprintf(log_file, "\n\n\n Dump called from function %s in file %s, in line %i. \n", function, file, number_of_line);
    fprintf(log_file, "Main function: File: %s, function %s, line %i. \n", my_stack->main_info.file, my_stack->main_info.name_of_function, my_stack->main_info.number_of_line);
    fprintf(log_file,  "\nDerzhite vash stack: \n"); 


    if(err == NULL_POINTER_OF_STACK){
        fprintf(log_file, "\n \t Pizdez, steka ne suschestvuet \n");
        fprintf(log_file, "\n \t Oshibka v faile %s \n \t \t v funkzii %s \n \t \t na %i stroke ", file, function, number_of_line);

    }
    else{
        if (err == NULL_POINTER_OF_DATA){
            fprintf(log_file, "\n Pizdez pomenbshe, data ne sushestvuet \n");
            fprintf(log_file, "\n \t Oshibka v faile %s \n \t \t v funkzii %s \n \t \t na %i stroke ", file, function, number_of_line);
        }
        else {
            //if(err == WRONG_CANARY){
                //printf("qwerty!!!!!!!!!!!!!!!!");


                if(my_stack->first_canary_for_stack != CANARY_VALUE){
                    fprintf(log_file, "Wrong first canary of stack! \n");
                    fprintf(log_file, "First canary of stack: [%lf], shoulb be [%lf]. \n", my_stack->first_canary_for_stack, CANARY_VALUE);
                }
                else{
                    fprintf(log_file, "First canary of stack: [%lf].\n ", my_stack->first_canary_for_stack);

                }
                if(my_stack->last_canary_for_stack != CANARY_VALUE){
                    fprintf(log_file, "Wrong last canary of stack! \n");
                    fprintf(log_file, "Last canary of stack: [%lf], shoulb be [%lf]. \n", my_stack->last_canary_for_stack, CANARY_VALUE);
                }
                else{
                    fprintf(log_file, "Last canary of stack: [%lf].\n", my_stack->last_canary_for_stack);

                }
                
                if(*(canary_element*)((char*)my_stack->data - sizeof(canary_element)) != CANARY_VALUE){
                    fprintf(log_file, "Wrong first canary of data! \n");
                    fprintf(log_file, "First canary of data: [%lf], shoulb be [%lf].\n", *(canary_element*)((char*)(my_stack->data) - sizeof(canary_element)), CANARY_VALUE);
                }
                else{
                    fprintf(log_file, "First canary of data: [%lf].\n", *(canary_element*)( (char*)my_stack->data - sizeof(canary_element)));

                }   

                if(*(canary_element*)((char*)my_stack->data + my_stack->capacity * sizeof(stack_element)) != CANARY_VALUE){
                    fprintf(log_file, "Wrong last canary of data! \n");
                    fprintf(log_file, "Last canary of data: [%lf], shoulb be [%lf].\n", *(canary_element*) ((char*)my_stack->data + my_stack->capacity * sizeof(stack_element)), CANARY_VALUE);
                }
                else{
                    fprintf(log_file, "Last canary of data: [%lf].\n", *(canary_element*) ((char*)my_stack->data + my_stack->capacity * sizeof(stack_element)));

                }

            //}
            
            if(err == WRONG_HASH_OF_DATA){

            }
            if (err == VSE_ZAYEBIS){
                size_t i = 0;
                fprintf(log_file, "\t%s\n", "Sam stack: \n");
                for(; i < my_stack->size; i++) {
                    fprintf(log_file, "\t\t[%zu]: %lf \n", i, my_stack->data[i]);

                }
                for(;i < my_stack->capacity; i++) {

                    fprintf(log_file, "\t\t[%zu]: %lf  - POISON\n", i, my_stack->data[i]);
                }

            }
        
        }
    }
    fprintf(log_file, "\t Size: %zu \n", my_stack->size);
    fprintf(log_file, "\t Capacity: %zu \n", my_stack->capacity);

    )

    printf( "\n \n%s \n", "Derzhite vash stack:"); 
    printf( "First canary of data: [%lf].\n", *(canary_element*)( (char*)my_stack->data - sizeof(canary_element)));


    size_t i = 0;
                printf( "\t%s\n", "Sam stack:");
                for(; i < my_stack->size; i++) {
                    printf("\t\t[%zu]: %lf \n", i, my_stack->data[i]);

                }
                for(;i < my_stack->capacity; i++) {

                    printf("\t\t[%zu]: %lf  - POISON\n", i, my_stack->data[i]);
                }

        
    printf("Last canary of stack: [%lf].\n", *(canary_element*) ((char*)my_stack->data + my_stack->capacity * sizeof(stack_element)));   
    printf("\t Size: %zu \n", my_stack->size);
    printf("\t Capacity: %zu \n", my_stack->capacity);

}

void StackDestroy(stack* my_stack) {


    CHECK_ALL;

    my_stack -> data = (stack_element*)((char*)my_stack -> data - sizeof(canary_element));

    free(my_stack->data);


}

Errors StackCheck(stack* my_stack, const int what_to_check) {

    switch (what_to_check) {
    case CHECK_ALL: {
         if(!my_stack){
            return NULL_POINTER_OF_STACK;

        }
        else if(!my_stack->data){
            return NULL_POINTER_OF_DATA;
        }

        else if(my_stack->first_canary_for_stack != CANARY_VALUE ||
            my_stack->last_canary_for_stack != CANARY_VALUE ||
            *(canary_element*)((char*)my_stack->data - sizeof(canary_element)) != CANARY_VALUE ||
            *(canary_element*)((char*)my_stack->data + my_stack->capacity * sizeof(stack_element)) != CANARY_VALUE){
                //printf("jhgjfcufc");
            return WRONG_CANARY;
        }
        hash_element new_stack_hash = CountHashOfStack(my_stack);

        if(new_stack_hash != my_stack->hash_stack){
            return WRONG_HASH_OF_STACK;
        }

        hash_element new_data_hash = CountHashOfData(my_stack);

        if(new_data_hash != my_stack -> hash_data){
            return WRONG_HASH_OF_DATA;
        }
        return VSE_ZAYEBIS;

        break;
    }
    case CHECK_NULL_POINTERS: {
        if(my_stack == NULL){
            //printf("qwerty");
            return NULL_POINTER_OF_STACK;

        }
        //printf("qwerty3");
         
        return VSE_ZAYEBIS;
        break;
    }
    case CHECK_CANARY: {
        if(my_stack->first_canary_for_stack != CANARY_VALUE ||
            my_stack->last_canary_for_stack != CANARY_VALUE ||
            *(canary_element*)((char*)my_stack->data - sizeof(canary_element)) != CANARY_VALUE ||
            *(canary_element*)((char*)my_stack->data + my_stack->capacity * sizeof(stack_element)) != CANARY_VALUE){
            return WRONG_CANARY;
        }
        return VSE_ZAYEBIS;

        break;
    }
    case CHECK_HASH: {
        hash_element new_stack_hash = CountHashOfStack(my_stack);

        if(new_stack_hash != my_stack->hash_stack){
            return WRONG_HASH_OF_STACK;
        }

        hash_element new_data_hash = CountHashOfData(my_stack);

        if(new_data_hash != my_stack -> hash_data){
            return WRONG_HASH_OF_DATA;
        }
        return VSE_ZAYEBIS;
        break;
    }
    default: {
        return WRONG_NAME_OF_CHECK_OPTION;
    }
    }
    return VSE_ZAYEBIS;


}


hash_element CountHashOfStack(stack* my_stack) {
    hash_element temp_hash = my_stack -> hash_stack;
    my_stack -> hash_stack = 0;

    info temp_info = my_stack->main_info;
    my_stack->main_info = MakeInfo("", "", 0);

    hash_element hash = fnv1aHash(my_stack, sizeof(stack));

    my_stack -> hash_stack = temp_hash;
    my_stack->main_info = temp_info;

    return hash;
}

hash_element CountHashOfData(stack* my_stack) {
    hash_element hash = djb2_hash(my_stack -> data, my_stack -> capacity * sizeof(my_stack -> data[0]));

    return hash;
}
hash_element fnv1aHash(const void* data, size_t size) {
    hash_element hash = 2166136261u; // Начальное значение FNV-1a

    const unsigned char* data_new = (const unsigned char*) data;

    for (size_t i = 0; i < size; i++)
    {
        hash ^= data_new[i];      // XOR с текущим байтом
        hash *= 16777619;         // Умножение на FNV-1a prime
    }

    return hash;
}

hash_element djb2_hash(const void* data, size_t size) {
    hash_element hash = 5381;                             

    long long unsigned int cast_to_type = 0;

    const unsigned char* data_new = (const unsigned char*) data;

    for(size_t i = 0; i < size; i++)
    {
        memcpy(&cast_to_type, &(data_new[i]), sizeof(long long unsigned int));

        hash = hash + (33 ^ cast_to_type);
    }

    return hash;
}


