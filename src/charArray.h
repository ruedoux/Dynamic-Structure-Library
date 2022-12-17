#pragma once
#ifndef CHARARR_C
#define CHARARR_C

#include "ArrayMaster.h"


/* CHAR ARRAY */
typedef struct{
    char *arrayPointer;     // Char pointer to array
    size_t size;          // Size of the text (can be printed with %s)
    size_t maxSize;       // Maximum size of array
} CharArray;

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

// Creates a new char array
CharArray create_CA(char*);

// Deletes array
void destroy_CA(CharArray*);

// Finds string in array
int find_CA_str(CharArray*, char*);

// Gets char on given index
char get_CA_char(CharArray*, size_t);

// Checks if array is empty
char is_CA_empty(CharArray*);

// pops last character from array
char pop_CA_back(CharArray*);

// Sets char to given index
ARR_ERR_CODE set_CA_char(CharArray*, char, size_t);

// Appends char array at the end of array
ARR_ERR_CODE append_CA(CharArray*, char*);

// Resizes the array to destined size
ARR_ERR_CODE resize_CA(CharArray*, size_t);

// Increases the size of allocated mem by value
ARR_ERR_CODE increase_CA_size(CharArray*, size_t);

// Decreases the size of allocated mem by value
ARR_ERR_CODE decrease_CA_size(CharArray*, size_t);

// Prints array info (debug)
void print_CA_info(CharArray*, char*);

#endif
