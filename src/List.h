#pragma once
#ifndef LIST_C
#define LIST_C

#include "ArrayMaster.h"


/* LINKED LIST */
typedef struct{
    void *objectPointer;    // Void pointer to object
    size_t dataTypeSize;    // Size of object
    char *ID;               // Identifier of element
} ListElement;

typedef struct{
    ListElement **elementPointers;  // Array of pointer to elements
    size_t size;                    // Number of objects in list
    size_t maxSize;                 // Number of max objects in list
} List;

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

List create_list();

void destroy_list(List*);

void destory_list_element(ListElement*);

void print_list_info(List*, char*);

void print_listElement_info(List*, size_t, char*);

ARR_ERR_CODE list_append(List*, void*, size_t, char*);

ARR_ERR_CODE increase_list_size(List*, size_t);

ARR_ERR_CODE decrease_list_size(List*, size_t);

ARR_ERR_CODE resize_list(List*, size_t);

ListElement* list_get_element_ptr(List*, size_t);


#endif
