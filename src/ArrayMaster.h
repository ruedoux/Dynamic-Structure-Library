#pragma once
#ifndef ARRMASTER_C
#define ARRMASTER_C

// ---------------------------------------
// LIBS
// ---------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------
// MACROS
// ---------------------------------------

// Returns pointer to i element of the dynamic array
#define ARR_PTR_AT(ptr, size, i) ( (void *)((char *)ptr + i * size) )

// ---------------------------------------
// DEBUG / ERROR MANAGEMENT
// ---------------------------------------

/* ARRAY ERROR CODES */
typedef enum {
    ARR_ERR_OK      =  0,  // Success
    ARR_ERR_ERR     = -1,  // Unspecified error
    ARR_ERR_REALLOC = -2,  // Realloc error
    ARR_ERR_INDEX   = -3,  // index error

} ARR_ERR_CODE;

# define BOLD				"\033[1m"
# define RED				"\033[31m"
# define GREEN				"\033[32m"
# define BLUE				"\033[34m"
# define ANSI_RESET			"\033[0m"

//  Example : DEBUG("MSG") will print : [filename: line_no] MSG \n
# define DEBUG(msg,...) fprintf(stderr, BOLD BLUE"[DEBUG](%s:%d) " ANSI_RESET BOLD msg ANSI_RESET"\n" , __FILE__, __LINE__, ##__VA_ARGS__)
//  Example : ERROR("ERROR") will print : [filename: line_no] ERROR \n
# define ERROR(msg,...) fprintf(stderr, BOLD RED"[ERROR](%s:%d) " ANSI_RESET BOLD msg ANSI_RESET"\n" , __FILE__, __LINE__, ##__VA_ARGS__)

#endif
