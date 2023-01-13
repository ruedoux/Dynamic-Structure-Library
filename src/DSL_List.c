#include "DSL_List.h"
#include "DSL_String.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void list_print_info(DSL_List *list, char *additionalInfo)
{
    DSL_String *strArr = str_create(""); // utilize char array

    char buffor[255];
    for (size_t i=0; i<list->maxSize; i++)
    {
        sprintf(buffor,""TYPE_SIZE_T":",i);
        str_append(strArr, buffor);
        
        DSL_ListElement* element = list_get_element_ptr(list, i);
        if (element == NULL) { str_append(strArr, "NULL"); }
        else { str_append(strArr, list->elementPointers[i]->ID); }
        str_append(strArr, ", ");
    }
    str_pop_back(strArr); // pop space
    str_pop_back(strArr); // pop comma

    printf("---------------------------------\n");
    printf("LIST INFO:\n");
    printf("maxSize: "TYPE_SIZE_T"\n", list->maxSize);
    printf("Content: %s\n", strArr->arrayPointer);
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");

    str_destroy(&strArr);
}


void listElement_print_info(DSL_List *list, size_t index, char *additionalInfo)
{
    DSL_ListElement *ePtr = list_get_element_ptr(list, index);
    if (ePtr == NULL) { return; }

    printf("---------------------------------\n");
    printf("LIST ELEMENT INFO:\n");
    printf("dataTypeSize: "TYPE_SIZE_T"\n", ePtr->dataTypeSize);
    printf("Content Type: %s\n", ePtr->ID);
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");
}

// ---------------------------------------
// SIZE MANAGEMENT
// ---------------------------------------

DSL_ERR_CODE list_increase_size(DSL_List* list, size_t addSize)
{
    if (size_t_will_overflow(list->maxSize, addSize)) { ERROR_MSG("Size overflow."); return ARR_ERR_OVER;}
    size_t increasedSize = list->maxSize + addSize;

    DSL_ListElement **tmp = realloc(list->elementPointers, increasedSize * sizeof(DSL_ListElement *));
    if (tmp == NULL) { ERROR_MSG("Unable to realloc."); return ARR_ERR_REALLOC; }
    list->elementPointers = tmp;

    // NULL new elements
    for (size_t i=list->maxSize; i<increasedSize; i++){ list->elementPointers[i] = NULL; }

    list->maxSize += addSize;

    return ARR_ERR_OK;
}


DSL_ERR_CODE list_decrease_size(DSL_List* list, size_t minusSize)
{
    // If decrease more than list size just make list size 0
    if( size_t_will_underflow(list->maxSize, minusSize) ) { minusSize = list->maxSize; } // Overflow check
    size_t decreasedSize = list->maxSize - minusSize;

    // Destroy elements
    if (decreasedSize < list->maxSize)
    {
        for (size_t i = decreasedSize; i<list->maxSize; i++)
        {
            DSL_ListElement *elementPtr = list_get_element_ptr(list, i);
            if (elementPtr == NULL) { continue; }
            listElement_destroy(&elementPtr);
        }
    }

    DSL_ListElement **tmp = realloc(list->elementPointers, decreasedSize * sizeof(DSL_ListElement *));
    if (tmp == NULL) { ERROR_MSG("Unable to realloc."); return ARR_ERR_REALLOC; }
    list->elementPointers = tmp;

    list->maxSize -= minusSize;

    return ARR_ERR_OK;
}


DSL_ERR_CODE list_resize(DSL_List* list, size_t destSize)
{
    DSL_ERR_CODE err_result = ARR_ERR_OK;

    if (destSize > list->maxSize)
    {
        size_t addSize = destSize - list->maxSize;
        err_result = list_increase_size(list, addSize);
    }
    else if (destSize < list->maxSize)
    {
        size_t minusSize = list->maxSize - destSize;
        err_result = list_decrease_size(list, minusSize);
    }

    return err_result;
}

// ---------------------------------------
// CHANGE LIST MANAGEMENT
// ---------------------------------------

DSL_ERR_CODE list_append(DSL_List* list, void* data, size_t dataSize, char* ID)
{
    DSL_ListElement *Eptr = listElement_create(data, dataSize, ID);
    if (Eptr == NULL) { ERROR_MSG("Unable to malloc."); return ARR_ERR_MALLOC; }

    list_increase_size(list, 1);
    list->elementPointers[list->maxSize-1] = Eptr;

    return ARR_ERR_OK;
}

// ---------------------------------------
// GET FROM LIST
// ---------------------------------------


DSL_ListElement* list_get_element_ptr(DSL_List* list, size_t index)
{
    if (index >= list->maxSize)
    {
        ERROR_MSG("Tried to get index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in DSL_List.", index, list->maxSize-1);
        return NULL;
    }

    return list->elementPointers[index];
}


void* list_obj_ptr_at(DSL_List *list, size_t index)
{
    if (index >= list->maxSize)
    {
        ERROR_MSG("Tried to get index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in DSL_List.", index, list->maxSize-1);
        return NULL;
    }
    
    return list_get_element_ptr(list, index)->objectPointer;
}

// ---------------------------------------
// CONSTRUCTOR
// ---------------------------------------

DSL_ListElement* listElement_create(void* data, size_t dataSize, char* ID)
{
    // Create element
    DSL_ListElement element;
    element.dataTypeSize = dataSize;

    // Allocate space for char array and copy it to element
    size_t id_len = strlen(ID) + 1;
    element.ID = malloc(id_len);
    if (element.ID == NULL) { return NULL; }
    memcpy(element.ID, ID, id_len);

    // Allocate space for data and copy it to element
    element.objectPointer = malloc(dataSize);
    if (element.objectPointer == NULL) { return NULL; }
    memcpy(element.objectPointer, data, dataSize);

    // Allocate space for the element and copy it
    DSL_ListElement *Eptr = malloc(sizeof *Eptr); //ERROR_MSG("Creating Eptr: %p", Eptr);
    if (Eptr == NULL) { return NULL; }
    memcpy(Eptr, &element, sizeof *Eptr);

    return Eptr;
}


DSL_List* list_create()
{
    // Create list
    DSL_List list;
    list.maxSize = 0;

    // Allocate space for pointer list
    list.elementPointers = malloc(0);
    if (list.elementPointers == NULL) {ERROR_MSG("Failed to malloc."); exit(1); }

    // Allocate space for the list and copy it
    DSL_List *Lptr = malloc(sizeof *Lptr);  //DEBUG_MSG("Creating list: %p", Lptr);
    if (Lptr == NULL) { return NULL; }
    memcpy(Lptr, &list, sizeof *Lptr);

    return Lptr;
}

// ---------------------------------------
// DESTRUCTOR
// ---------------------------------------

void listElement_destroy(DSL_ListElement **ptrToElement)
{
    // Get the actual pointer from pointer to a pointer
    DSL_ListElement *element = *ptrToElement; //DEBUG_MSG("Destroying element: %p",element);

    free_and_NULL(element->objectPointer);
    free_and_NULL(element->ID);
    free_and_NULL(*ptrToElement);
}


void list_destroy(DSL_List **ptrTolist)
{
    // Get the actual pointer from pointer to a pointer
    DSL_List *list = *ptrTolist; //DEBUG_MSG("Destroying list: %p", list);

    // Free all elements in list
    for (size_t i=0; i<list->maxSize;i++)
    {
        DSL_ListElement *elementPtr = list_get_element_ptr(list, i);
        if (elementPtr == NULL) { continue; }
        listElement_destroy(&elementPtr);
    }

    // Free pointers list
    free_and_NULL(list->elementPointers);

    // Free the list itself
    free_and_NULL(*ptrTolist);
}
