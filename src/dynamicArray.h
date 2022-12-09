#pragma once
#ifndef DYNAMICARR_C
#define DYNAMICARR_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "charArray.h"

// Returns pointer to i element of the dynamic array
#define ARR_PTR_AT(ptr, size, i) ( (void *)((char *)ptr + i * size) )


/* DYNAMIC ARRAY ERROR CODES */
typedef enum {
	DA_ERR_OK      =  0,  // Success
    DA_ERR_ERR     = -1,  // Unspecified error
    DA_ERR_REALLOC = -2,  // Realloc error
    DA_ERR_INDEX   = -3,  // index error

} DA_ERR_CODE;


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
struct dynamicArray{
    void *arrayPointer;         // Void pointer to array
    unsigned int dataTypeSize;  // Size of data type

    unsigned int size;          // Number of objects in array
    unsigned int maxSize;       // Number of max objects in array

    DA_DATA_TYPE DATA_TYPE;     // Data type

    // ---------------------------------------
    // FUNCTIONS
    // ---------------------------------------

    // Creates new dynamic array
    struct dynamicArray (*createDA)(void*, size_t, size_t, DA_DATA_TYPE);

    // Deletes array
    void (*destroyDA)(struct dynamicArray*);

    // Get pointer to object at given index, return NULL if incorrect index
    void* (*get_DA_ptr_at)(struct dynamicArray*, unsigned int);

    // Checks if array is empty
    char (*is_DA_empty)(struct dynamicArray*);

    // Appends array of the same type to the dynamic array
    DA_ERR_CODE (*append_DA)(struct dynamicArray*, void*, unsigned int);

    // Sets value of array at given index
    DA_ERR_CODE (*set_DA_at)(struct dynamicArray*, void*, unsigned int);

    // Increases maximum size of array
    DA_ERR_CODE (*increase_DA_size)(struct dynamicArray*, unsigned int);

    // Decreases maximum size of array
    DA_ERR_CODE (*decrease_DA_size)(struct dynamicArray*, unsigned int);

    // Resizes array to a given size
    DA_ERR_CODE (*resize_DA)(struct dynamicArray*, unsigned int);

    // Tries to convert array content into string
    void (*DA_to_str)(char *, struct dynamicArray *, size_t);

    // Throws error message
    void (*throw_DA_error)(char*);

    // Prints information regarding array
    void (*print_DA_info)(struct dynamicArray*, char*);
};

extern const struct dynamicArray DynamicArray;

#endif
