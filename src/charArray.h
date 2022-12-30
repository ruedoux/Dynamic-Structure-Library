/*
 * CharArray is char dynamic array (basically String).
 *
 * CharArray structure info:
 * 1) CharArray stores array of chars.
 * 2) CharArray is allocated so has to be freed.
*/

#pragma once
#ifndef CHARARR_C
#define CHARARR_C

#include "ArrayMaster.h"

/* CHAR ARRAY */
typedef struct{
    char *arrayPointer;    // Char pointer to array
    size_t maxSize;       // Maximum size of array
} CharArray;

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

// Creates a new dynamic char array from char array (allocate memory)
CharArray *create_CA(char *str);

// Deletes dynamic char array (free memory)
void destroy_CA(CharArray **ptrToArr);

// Finds string in array, returns starting index of first find
// Returns -1 if none was found
int find_CA_str(CharArray *arr, char *str);

// Returns char on given index
char get_CA_char(CharArray *arr, size_t index);

// Checks if array is empty
bool is_CA_empty(CharArray *arr);

// Pops last character from array and returns it
char pop_CA_back(CharArray *arr);

// Sets char at given index
ARR_ERR_CODE set_CA_char(CharArray *arr, char ch, size_t index);

// Appends char array at the end of dynamic char array
ARR_ERR_CODE append_CA(CharArray *arr, char *str);

// Resizes the array to destined size
// All new indexes will be set to '\0'
// All indexes above the new max size will be lost
ARR_ERR_CODE resize_CA(CharArray *arr, size_t destSize);

// Increases the size of allocated memory by value
ARR_ERR_CODE increase_CA_size( CharArray *arr, size_t addSize);

// Decreases the size of allocated memory by value
ARR_ERR_CODE decrease_CA_size( CharArray *arr, size_t minusSize);

// Prints array info (debug)
void print_CA_info( CharArray *arr, char *additionalInfo);

#endif
