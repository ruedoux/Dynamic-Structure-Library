#pragma once
#ifndef LIST_C
#define LIST_C

#include "ArrayMaster.h"

// ---------------------------------------
// STRUCTS
// ---------------------------------------

/* LIST ELEMENTS */
typedef struct{
    void *objectPointer;    // Void pointer to object
    size_t dataTypeSize;    // Size of object
    char *ID;               // Identifier of element
} ListElement;

/* LIST */
typedef struct{
    ListElement **elementPointers;  // Array of pointer to elements
    size_t maxSize;                 // Number of max objects in list
} List;

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

// Creates a list (allocated), returns a pointer
List* create_list();

// Creates a list element (allocated), returns a pointer
ListElement* create_listElement(void*, size_t, char*);

// Destroys list
void destroy_list(List**);

// Destroys list element
void destory_listElement(ListElement**);

// Prints information regarding list
void print_list_info(List*, char*);

// Prints information regarding list element
void print_listElement_info(List*, size_t, char*);

// Appends data to the list
ARR_ERR_CODE list_append(List*, void*, size_t, char*);

// Increase list by a given size
ARR_ERR_CODE increase_list_size(List*, size_t);

// Decrease list by a given size
ARR_ERR_CODE decrease_list_size(List*, size_t);

// Resizes list to a given size
ARR_ERR_CODE resize_list(List*, size_t);

// Returns pointer to element on a given index
ListElement* list_get_element_ptr(List*, size_t);

// Returns pointer to object inside of element on a given index
void* list_obj_ptr_at(List*, size_t);

#endif
