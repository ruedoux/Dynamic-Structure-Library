#pragma once
#ifndef DYNAMICARR_C
#define DYNAMICARR_C

#include "ArrayMaster.h"
#include "charArray.h"


/* DYNAMIC ARRAY DATA TYPES */
// This is only for debug purposes, you can pass DA_DATA_NA to constructor.
// Ignoring it will only result in not being able to convert data type to string
// in array print function.
typedef enum {
    DA_DATA_NA,
    DA_DATA_UCHAR,
    DA_DATA_CHAR,
    DA_DATA_USHORT,
    DA_DATA_SHORT,
    DA_DATA_UINT,
    DA_DATA_INT,
    DA_DATA_ULLI,
    DA_DATA_LLI,
    DA_DATA_FLOAT,
    DA_DATA_DOUBLE,
    DA_DATA_LDOUBLE,
} DA_DATA_TYPE;


/* DYNAMIC ARR */
typedef struct{
    void *arrayPointer;         // Void pointer to array
    unsigned int dataTypeSize;  // Size of data type

    unsigned int size;          // Number of objects in array
    unsigned int maxSize;       // Number of max objects in array

    DA_DATA_TYPE DATA_TYPE;     // Data type
} DynamicArray;

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

// Creates new dynamic array
DynamicArray create_DA(void*, size_t, size_t, DA_DATA_TYPE);

// Deletes array
void destroy_DA(DynamicArray*);

// Get pointer to object at given index, return NULL if incorrect index
void* get_DA_ptr_at(DynamicArray*, unsigned int);

// Checks if array is empty
char is_DA_empty(DynamicArray*);

// Appends array of the same type to the dynamic array
ARR_ERR_CODE append_DA(DynamicArray*, void*, unsigned int);

// Sets value of array at given index
ARR_ERR_CODE set_DA_at(DynamicArray*, void*, unsigned int);

// Increases maximum size of array
ARR_ERR_CODE increase_DA_size(DynamicArray*, unsigned int);

// Decreases maximum size of array
ARR_ERR_CODE decrease_DA_size(DynamicArray*, unsigned int);

// Resizes array to a given size
ARR_ERR_CODE resize_DA(DynamicArray*, unsigned int);

// Tries to convert array content into string
void DA_to_str(char *, DynamicArray *, size_t);

// Prints information regarding array
void print_DA_info(DynamicArray*, char*);


#endif
