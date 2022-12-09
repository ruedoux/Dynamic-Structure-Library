#pragma once
#ifndef CHARARR_C
#define CHARARR_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CHAR ARRAY ERROR CODES */
typedef enum {
    CA_ERR_OK = 0,       // Success
    CA_ERR_ERR = -1,     // Unspecified error
    CA_ERR_REALLOC = -2, // Realloc error
    CA_ERR_INDEX = -3,   // index error

} CA_ERR_CODE;


/* CHAR ARRAY */
struct charArray{
    char *arrayPointer;     // Char pointer to array
    unsigned int size;      // Size of the text (can be printed with %s)
    unsigned int maxSize;   // Maximum size of array

    // ---------------------------------------
    // FUNCTIONS
    // ---------------------------------------

    // Creates a new char array
    struct charArray (*createCA)(char*);

    // Deletes array
    void (*destroyCA)(struct charArray *);

    // Finds string in array
    int (*find_CA_str)(struct charArray*, char*);

    // Gets char on given index
    char (*get_CA_char)(struct charArray*, unsigned int);

    // Checks if array is empty
    char (*is_CA_empty)(struct charArray*);

    // pops last character from array
    char (*pop_CA_back)(struct charArray*);

    // Sets char to given index
    CA_ERR_CODE (*set_CA_char)(struct charArray*, char, unsigned int);

    // Appends char array at the end of array
    CA_ERR_CODE (*append_CA)(struct charArray*, char*);

    // Resizes the array to destined size
    CA_ERR_CODE (*resize_CA)(struct charArray *, unsigned int);

    // Increases the size of allocated mem by value
    CA_ERR_CODE (*increase_CA_size)(struct charArray*, unsigned int);

    // Decreases the size of allocated mem by value
    CA_ERR_CODE (*decrease_CA_size)(struct charArray*, unsigned int);

    // Throws an error (debug)
    void (*throw_CA_error)(char*);

    // Prints array info (debug)
    void (*print_CA_info)(struct charArray*, char*);
};

extern const struct charArray CharArray;

#endif
