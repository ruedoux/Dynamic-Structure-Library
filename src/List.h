#pragma once
#ifndef LIST_C
#define LIST_C

#include "ArrayMaster.h"


/* LINKED LIST */
typedef struct{
    void *objectPointer;       // Void pointer to object
    unsigned int dataTypeSize; // Size of object

    char *ID;                  // Identifier of element
} ListElement;

typedef struct{
    ListElement **elementPointers;    // Array of pointer to elements
    unsigned int size;               // Number of objects in list
} List;

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

List create_list();

void destroy_list(List*);

void print_list_info(List*, char*);

void print_listElement_info(List*, unsigned int, char*);

void list_append(List*, void*, unsigned int, char*);

void increase_list_size(List*, unsigned int);

ListElement* list_get_element_ptr(List*, unsigned int);


#endif
