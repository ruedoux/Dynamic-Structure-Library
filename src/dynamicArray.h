/*
 * DynamicArray is same data type dynamic array.
 *
 * DynamicArray structure info:
 * 1) DynamicArray stores array of objects of the same type.
 * 2) DynamicArray is allocated so has to be freed.
*/

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
    size_t dataTypeSize;        // Size of data type
    size_t maxSize;             // Number of max objects in array
    DA_DATA_TYPE DATA_TYPE;     // Data type
} DynamicArray;

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

// Creates new dynamic array (allocate memory)
DynamicArray* create_DA(void*, size_t, size_t, DA_DATA_TYPE);

// Deletes dynamic array (free memory)
void destroy_DA(DynamicArray**);

// Get pointer to object at given index, return NULL if incorrect index
// To get to value at a pointer cast it to the proper data type, example:
// int intVal = *(int*)get_DA_ptr_at(arr, 3);
void* get_DA_ptr_at(DynamicArray*, size_t);

// Checks if array is empty
bool is_DA_empty(DynamicArray*);

// Appends array of the same type to the end of dynamic array
ARR_ERR_CODE append_DA(DynamicArray*, void*, size_t);

// Sets value of array at given index
ARR_ERR_CODE set_DA_at(DynamicArray*, void*, size_t);

// Increases maximum size of array
ARR_ERR_CODE increase_DA_size(DynamicArray*, size_t);

// Decreases maximum size of array
ARR_ERR_CODE decrease_DA_size(DynamicArray*, size_t);

// Resizes array to a given size
// All new indexes will be set to NULL
// All indexes above the new max size will be lost
ARR_ERR_CODE resize_DA(DynamicArray*, size_t);

// Tries to convert array content into string
// Returns "err" if unknown data type
void DA_to_str(char *, DynamicArray *, size_t);

// Prints information regarding array
void print_DA_info(DynamicArray*, char*);

#endif
