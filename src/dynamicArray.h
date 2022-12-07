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
    void *arrayPointer;
    unsigned int dataTypeSize;

    unsigned int size;
    unsigned int maxSize;

    DA_DATA_TYPE DATA_TYPE;

    // Functions
    struct dynamicArray (*createDA)(void*, size_t, size_t, DA_DATA_TYPE);

    void (*voidPtr_to_str)(char *, struct dynamicArray *, size_t);
    void (*throw_DA_error_abort)(char*);                        // Throws an error (debug)
    void (*print_DA_info)(struct dynamicArray*, char*);         // Prints array info (debug)
    void (*destroyDA)(struct dynamicArray*);
};

extern const struct dynamicArray DynamicArray;

#endif
