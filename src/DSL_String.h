/*
 * DSL_String is char dynamic array (basically String).
 *
 * DSL_String structure info:
 * 1) DSL_String stores array of chars.
 * 2) DSL_String is allocated so has to be freed.
*/

#pragma once
#ifndef DSL_STR_C
#define DSL_STR_C

#include "DSL_Master.h"

/* CHAR ARRAY */
typedef struct{
    char *arrayPointer;    // Char pointer to array
    size_t maxSize;       // Maximum size of array
} DSL_String;

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

// Creates a new dynamic char array from char array (allocate memory)
DSL_String *str_create(char *str);

// Deletes dynamic char array (free memory)
void str_destroy(DSL_String **ptrToArr);

// Finds string in array, returns starting index of first find
// Returns -1 if none was found
i32 str_find(DSL_String *arr, char *str);

// Returns char on given index
char str_get_char(DSL_String *arr, size_t index);

// Checks if array is empty
bool str_is_empty(DSL_String *arr);

// Pops last character from array and returns it
char str_pop_back(DSL_String *arr);

// Sets char at given index
DSL_ERR_CODE str_set_char(DSL_String *arr, char ch, size_t index);

// Appends char array at the end of dynamic char array
DSL_ERR_CODE str_append(DSL_String *arr, char *str);

// Resizes the array to destined size
// All new indexes will be set to '\0'
// All indexes above the new max size will be lost
DSL_ERR_CODE str_resize(DSL_String *arr, size_t destSize);

// Increases the size of allocated memory by value
DSL_ERR_CODE str_increase_size( DSL_String *arr, size_t addSize);

// Decreases the size of allocated memory by value
DSL_ERR_CODE str_decrease_size( DSL_String *arr, size_t minusSize);

// Prints array info (debug)
void str_print_info( DSL_String *arr, char *additionalInfo);

#endif
