#pragma once
#ifndef ARRMASTER_C
#define ARRMASTER_C

#define _CRT_SECURE_NO_WARNINGS // VS

// ---------------------------------------
// LIBS
// ---------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// ---------------------------------------
// MACROS
// ---------------------------------------

// Returns pointer to i element of the dynamic array
#define ARR_PTR_AT(ptr, size, i) ( (void *)((char *)ptr + i * size) )

// Frees a given allocated pointer and NULL's it
#define free_and_NULL(ptr) (free(ptr), ptr = NULL)

// Returns size of char* + null terminator
#define strlenT(str) strlen(str)+1

// ---------------------------------------
// WIN / LINUX MACROS
// ---------------------------------------

#ifdef _WIN32
#define TYPE_SIZE_T "%Iu"
#endif

#ifdef linux
#define TYPE_SIZE_T "%Ilu"
#endif

// ---------------------------------------
// DEBUG_MSG / ERROR_MSG MANAGEMENT
// ---------------------------------------

/* ARRAY ERROR_MSG CODES */
typedef enum {
    ARR_ERR_OK      =  0,  // Success
    ARR_ERR_ERR     = -1,  // Unspecified error
    ARR_ERR_REALLOC = -2,  // Realloc error
    ARR_ERR_MALLOC  = -3,  // Malloc error
    ARR_ERR_CALLOC  = -4,  // Calloc error
    ARR_ERR_INDEX   = -5,  // Index error
    ARR_ERR_OVER    = -6,  // Overflow error

} ARR_ERR_CODE;

# define BOLD				"\033[1m"
# define RED				"\033[31m"
# define GREEN				"\033[32m"
# define BLUE				"\033[34m"
# define ANSI_RESET			"\033[0m"

// Example : DEBUG_MSG("MSG") will print : [filename: line_no] MSG \n
# define DEBUG_MSG(msg,...) fprintf(stderr, BOLD BLUE"[DEBUG](%s:%d) " ANSI_RESET BOLD msg ANSI_RESET"\n" , __FILE__, __LINE__, ##__VA_ARGS__)

// Example : ERROR_MSG("ERROR_MSG") will print : [filename: line_no] ERROR_MSG \n
# define ERROR_MSG(msg,...) fprintf(stderr, BOLD RED"[ERROR](%s:%d) " ANSI_RESET BOLD msg ANSI_RESET"\n" , __FILE__, __LINE__, ##__VA_ARGS__)

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

// Checks if minus operation (a-b) on size_t variables will underflow
bool size_t_will_underflow(size_t a, size_t b);

// Checks if plus operation (a+b) on size_t variables will overflow
bool size_t_will_overflow(size_t a, size_t b);

#endif
