/*
 * DSL_List is a python like list object that holds pointers to various data.
 *
 * DSL_List structure info:
 * 1) DSL_List object stores list of pointers to list elements.
 * 2) The DSL_List structure is allocated so has to be freed.
 *
 * DSL_ListElement structure info:
 * 1) DSL_List element is a structure holding a pointer to a given data.
 * 2) The DSL_ListElement structure is allocated so has to be freed.
 * 3) DSL_ListElement holds ID (short identifier of a structure) and its size.
*/

#pragma once
#ifndef LIST_C
#define LIST_C

#include "DSL_Master.h"

// ---------------------------------------
// STRUCTS
// ---------------------------------------

/* LIST ELEMENT */
typedef struct{
    void *objectPointer;    // Void pointer to object
    size_t dataTypeSize;    // Size of object
    char *ID;               // Identifier of element
} DSL_ListElement;

/* LIST */
typedef struct{
    DSL_ListElement **elementPointers;  // Array of pointer to elements
    size_t maxSize;                     // Number of max objects in list
} DSL_List;

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

// Creates a list (allocate memory)
DSL_List* list_create();

// Creates a list element (allocate memory)
DSL_ListElement* listElement_create(void* data, size_t dataSize, char* ID);

// Destroys list (free momory)
void list_destroy(DSL_List **ptrTolist);

// Destroys list element (free momory)
void listElement_destroy(DSL_ListElement **ptrToElement);

// Appends data to the end of the list
DSL_ERR_CODE list_append(DSL_List* list, void* data, size_t dataSize, char* ID);

// Increase list size by a given size
DSL_ERR_CODE list_increase_size(DSL_List* list, size_t addSize);

// Decrease list size by a given size
DSL_ERR_CODE list_decrease_size(DSL_List* list, size_t minusSize);

// Resizes list to a given size
DSL_ERR_CODE list_resize(DSL_List* list, size_t destSize);

// Returns pointer to element on a given index
DSL_ListElement* list_get_element_ptr(DSL_List* list, size_t index);

// Returns pointer to object inside of element on a given index
// To get to value at a pointer cast it to the proper data type, example:
// int intVal = *(int*)list_obj_ptr_at(list, 3);
void* list_obj_ptr_at(DSL_List *list, size_t index);

// Prints information regarding list
void list_print_info(DSL_List *list, char *additionalInfo);

// Prints information regarding list element
void listElement_print_info(DSL_List *list, size_t index, char *additionalInfo);

#endif
