/*
 * DynamicArray is same data type dynamic array.
 *
 * DynamicArray structure info:
 * 1) DynamicArray stores array of objects of the same type.
 * 2) DynamicArray is allocated so has to be freed.
*/

#pragma once
#ifndef DSL_DYNAMIC_ARR_C
#define DSL_DYNAMIC_ARR_C

#include "DSL_Master.h"
#include "DSL_String.h"

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
DynamicArray* da_create(void *data, size_t size, size_t dataTypeSize, DA_DATA_TYPE DATA_TYPE);

// Deletes dynamic array (free memory)
void da_destroy(DynamicArray **ptrToArr);

// Get pointer to object at given index, return NULL if incorrect index
// To get to value at a pointer cast it to the proper data type, example:
// int intVal = *(int*)da_get_ptr_at(arr, 3);
void* da_get_ptr_at(DynamicArray *arr, size_t index);

// Checks if array is empty
bool da_is_empty(DynamicArray *arr);

// Appends array of the same type to the end of dynamic array
DSL_ERR_CODE da_append(DynamicArray *arr, void* data, size_t dataSize);

// Sets value of array at given index
DSL_ERR_CODE da_set_at(DynamicArray *arr, void* data, size_t index);

// Increases maximum size of array
DSL_ERR_CODE da_increase_size(DynamicArray *arr, size_t addSize);

// Decreases maximum size of array
DSL_ERR_CODE da_decrease_size(DynamicArray *arr, size_t minusSize);

// Resizes array to a given size
// All new indexes will be set to NULL
// All indexes above the new max size will be lost
DSL_ERR_CODE da_resize(DynamicArray *arr, size_t destSize);

// Tries to convert array content into string
// Returns "err" if unknown data type
void da_to_str(char *buffor, DynamicArray *arr, size_t index);

// Prints information regarding array
void da_print_info(DynamicArray *dArr, char *additionalInfo);

#endif
