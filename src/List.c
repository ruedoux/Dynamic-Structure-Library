#include "List.h"
#include "charArray.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void print_list_info(List *list, char *additionalInfo)
{
    CharArray *strArr = create_CA(""); // utilize char array

    char buffor[255];
    for (size_t i=0; i<list->maxSize; i++)
    {
        sprintf(buffor,""TYPE_SIZE_T":",i);
        append_CA(strArr, buffor);
        
        ListElement* element = list_get_element_ptr(list, i);
        if (element == NULL) { append_CA(strArr, "NULL"); }
        else { append_CA(strArr, list->elementPointers[i]->ID); }
        append_CA(strArr, ", ");
    }
    pop_CA_back(strArr); // pop space
    pop_CA_back(strArr); // pop comma

    printf("---------------------------------\n");
    printf("LIST INFO:\n");
    printf("maxSize: "TYPE_SIZE_T"\n", list->maxSize);
    printf("Content: %s\n", strArr->arrayPointer);
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");

    destroy_CA(&strArr);
}


void print_listElement_info(List *list, size_t index, char *additionalInfo)
{
    ListElement *ePtr = list_get_element_ptr(list, index);
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

ARR_ERR_CODE increase_list_size(List* list, size_t addSize)
{
    if (size_t_will_overflow(list->maxSize, addSize)) { DEBUG("Size overflow."); return ARR_ERR_OVER;}
    size_t increasedSize = list->maxSize + addSize;

    ListElement **tmp = realloc(list->elementPointers, increasedSize * sizeof(ListElement *));
    if (tmp == NULL) { ERROR("Unable to realloc."); return ARR_ERR_REALLOC; }
    list->elementPointers = tmp;

    // NULL new elements
    for (size_t i=list->maxSize; i<increasedSize; i++){ list->elementPointers[i] = NULL; }

    list->maxSize += addSize;

    return ARR_ERR_OK;
}


ARR_ERR_CODE decrease_list_size(List* list, size_t minusSize)
{
    // If decrease more than list size just make list size 0
    if( size_t_will_underflow(list->maxSize, minusSize) ) { minusSize = list->maxSize; } // Overflow check
    size_t decreasedSize = list->maxSize - minusSize;

    // Destroy elements
    if (decreasedSize < list->maxSize)
    {
        for (size_t i = decreasedSize; i<list->maxSize; i++)
        {
            ListElement *elementPtr = list_get_element_ptr(list, i);
            if (elementPtr == NULL) { continue; }
            destory_listElement(&elementPtr);
        }
    }

    ListElement **tmp = realloc(list->elementPointers, decreasedSize * sizeof(ListElement *));
    if (tmp == NULL) { ERROR("Unable to realloc."); return ARR_ERR_REALLOC; }
    list->elementPointers = tmp;

    list->maxSize -= minusSize;

    return ARR_ERR_OK;
}


ARR_ERR_CODE resize_list(List* list, size_t destSize)
{
    ARR_ERR_CODE err_result = ARR_ERR_OK;

    if (destSize > list->maxSize)
    {
        size_t addSize = destSize - list->maxSize;
        err_result = increase_list_size(list, addSize);
    }
    else if (destSize < list->maxSize)
    {
        size_t minusSize = list->maxSize - destSize;
        err_result = decrease_list_size(list, minusSize);
    }

    return err_result;
}

// ---------------------------------------
// CHANGE LIST MANAGEMENT
// ---------------------------------------

ARR_ERR_CODE list_append(List* list, void* data, size_t dataSize, char* ID)
{
    ListElement *Eptr = create_listElement(data, dataSize, ID);
    if (Eptr == NULL) { ERROR("Unable to malloc."); return ARR_ERR_MALLOC; }

    increase_list_size(list, 1);
    list->elementPointers[list->maxSize-1] = Eptr;

    return ARR_ERR_OK;
}

// ---------------------------------------
// GET FROM LIST
// ---------------------------------------


ListElement* list_get_element_ptr(List* list, size_t index)
{
    if (index >= list->maxSize)
    {
        ERROR("Tried to get index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in List.", index, list->maxSize-1);
        return NULL;
    }

    return list->elementPointers[index];
}


void* list_obj_ptr_at(List *list, size_t index)
{
    if (index >= list->maxSize)
    {
        ERROR("Tried to get index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in List.", index, list->maxSize-1);
        return NULL;
    }
    
    return list_get_element_ptr(list, index)->objectPointer;
}

// ---------------------------------------
// CONSTRUCTOR
// ---------------------------------------

ListElement* create_listElement(void* data, size_t dataSize, char* ID)
{
    // Create element
    ListElement element;
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
    ListElement *Eptr = malloc(sizeof *Eptr); //DEBUG("Creating Eptr: %p", Eptr);
    if (Eptr == NULL) { return NULL; }
    memcpy(Eptr, &element, sizeof *Eptr);

    return Eptr;
}


List* create_list()
{
    // Create list
    List list;
    list.maxSize = 0;

    // Allocate space for pointer list
    list.elementPointers = malloc(0);
    if (list.elementPointers == NULL) {ERROR("Failed to malloc."); exit(1); }

    // Allocate space for the list and copy it
    List *Lptr = malloc(sizeof *Lptr);  //DEBUG("Creating list: %p", Lptr);
    if (Lptr == NULL) { return NULL; }
    memcpy(Lptr, &list, sizeof *Lptr);

    return Lptr;
}

// ---------------------------------------
// DESTRUCTOR
// ---------------------------------------

void destory_listElement(ListElement **ptrToElement)
{
    // Get the actual pointer from pointer to a pointer
    ListElement *element = *ptrToElement; //DEBUG("Destroying element: %p",element);

    free_and_NULL(element->objectPointer);
    free_and_NULL(element->ID);
    free_and_NULL(*ptrToElement);
}


void destroy_list(List **ptrTolist)
{
    // Get the actual pointer from pointer to a pointer
    List *list = *ptrTolist; //DEBUG("Destroying list: %p", list);

    // Free all elements in list
    for (size_t i=0; i<list->maxSize;i++)
    {
        ListElement *elementPtr = list_get_element_ptr(list, i);
        if (elementPtr == NULL) { continue; }
        destory_listElement(&elementPtr);
    }

    // Free pointers list
    free_and_NULL(list->elementPointers);

    // Free the list itself
    free_and_NULL(*ptrTolist);
}
