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
CharArray *create_CA(char*);

// Deletes dynamic char array (free memory)
void destroy_CA(CharArray**);

// Finds string in array, returns starting index of first find
// Returns -1 if none was found
int find_CA_str(CharArray*, char*);

// Returns char on given index
char get_CA_char(CharArray*, size_t);

// Checks if array is empty
bool is_CA_empty(CharArray*);

// Pops last character from array and returns it
char pop_CA_back(CharArray*);

// Sets char at given index
ARR_ERR_CODE set_CA_char(CharArray*, char, size_t);

// Appends char array at the end of dynamic char array
ARR_ERR_CODE append_CA(CharArray*, char*);

// Resizes the array to destined size
// All new indexes will be set to '\0'
// All indexes above the new max size will be lost
ARR_ERR_CODE resize_CA(CharArray*, size_t);

// Increases the size of allocated memory by value
ARR_ERR_CODE increase_CA_size(CharArray*, size_t);

// Decreases the size of allocated memory by value
ARR_ERR_CODE decrease_CA_size(CharArray*, size_t);

// Prints array info (debug)
void print_CA_info(CharArray*, char*);

#endif
