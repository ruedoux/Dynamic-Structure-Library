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
ListElement* create_listElement(void* data, size_t dataSize, char* ID);

// Destroys list (free momory)
void destroy_list(List **ptrTolist);

// Destroys list element (free momory)
void destory_listElement(ListElement **ptrToElement);

// Appends data to the end of the list
ARR_ERR_CODE list_append(List* list, void* data, size_t dataSize, char* ID);

// Increase list size by a given size
ARR_ERR_CODE increase_list_size(List* list, size_t addSize);

// Decrease list size by a given size
ARR_ERR_CODE decrease_list_size(List* list, size_t minusSize);

// Resizes list to a given size
ARR_ERR_CODE resize_list(List* list, size_t destSize);

// Returns pointer to element on a given index
ListElement* list_get_element_ptr(List* list, size_t index);

// Returns pointer to object inside of element on a given index
// To get to value at a pointer cast it to the proper data type, example:
// int intVal = *(int*)list_obj_ptr_at(list, 3);
void* list_obj_ptr_at(List *list, size_t index);

// Prints information regarding list
void print_list_info(List *list, char *additionalInfo);

// Prints information regarding list element
void print_listElement_info(List *list, size_t index, char *additionalInfo);

#endif
