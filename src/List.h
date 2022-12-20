/*
 * List is a python like list object that holds pointers to various data.
 *
 * List structure info:
 * 1) List object stores list of pointers to list elements.
 * 2) The List structure is allocated so has to be freed.
 *
 * ListElement structure info:
 * 1) List element is a structure holding a pointer to a given data.
 * 2) The ListElement structure is allocated so has to be freed.
 * 3) ListElement holds ID (short identifier of a structure) and its size.
*/

#pragma once
#ifndef LIST_C
#define LIST_C

#include "ArrayMaster.h"

// ---------------------------------------
// STRUCTS
// ---------------------------------------

/* LIST ELEMENT */
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

// Creates a list (allocate memory)
List* create_list();

// Creates a list element (allocate memory)
ListElement* create_listElement(void*, size_t, char*);

// Destroys list (free momory)
void destroy_list(List**);

// Destroys list element (free momory)
void destory_listElement(ListElement**);

// Appends data to the end of the list
ARR_ERR_CODE list_append(List*, void*, size_t, char*);

// Increase list size by a given size
ARR_ERR_CODE increase_list_size(List*, size_t);

// Decrease list size by a given size
ARR_ERR_CODE decrease_list_size(List*, size_t);

// Resizes list to a given size
ARR_ERR_CODE resize_list(List*, size_t);

// Returns pointer to element on a given index
ListElement* list_get_element_ptr(List*, size_t);

// Returns pointer to object inside of element on a given index
// To get to value at a pointer cast it to the proper data type, example:
// int intVal = *(int*)list_obj_ptr_at(list, 3);
void* list_obj_ptr_at(List*, size_t);

// Prints information regarding list
void print_list_info(List*, char*);

// Prints information regarding list element
void print_listElement_info(List*, size_t, char*);

#endif
