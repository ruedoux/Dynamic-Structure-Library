#include "List.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void print_list_info(List *list, char *additionalInfo)
{
    printf("---------------------------------\n");
    printf("LIST INFO:\n");
    printf("size: %d\n", list->size);
    printf("Content: WIP\n");
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");
}


void print_listElement_info(List *list, unsigned int index, char *additionalInfo)
{
    ListElement *ePtr = list_get_element_ptr(list, index);

    printf("---------------------------------\n");
    printf("LIST ELEMENT INFO:\n");
    printf("dataTypeSize: %u\n", ePtr->dataTypeSize);
    printf("Content Type: %s\n", ePtr->ID);
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");
}

// ---------------------------------------
// SIZE MANAGEMENT
// ---------------------------------------

void increase_list_size(List* list, unsigned int addSize)
{
    unsigned int increasedSize = (list->size + addSize) * sizeof(ListElement*);
    void *tmp = realloc(list->elementPointers, increasedSize);
    if (tmp == NULL) { ERROR("Unable to realloc."); return; }

    list->size += addSize;
}

// ---------------------------------------
// CHANGE LIST MANAGEMENT
// ---------------------------------------

void list_append(List* list, void* data, unsigned int dataSize, char* ID)
{
    // Create element
    ListElement element;
    element.dataTypeSize = dataSize;
    element.ID = malloc(strlen(ID) * sizeof(char)); // Allocate space for char array
    memcpy(element.ID, ID, strlen(ID));             // Copy char array
    element.objectPointer = malloc(dataSize);        // Allocate space for data
    memcpy(element.objectPointer, data, dataSize);   // Copy data

    // Allocate space for the element
    ListElement *Eptr = malloc(sizeof *Eptr);
    if (Eptr == NULL) { ERROR("Unable to malloc.");}

    // Copy element to allocated space
    memcpy(Eptr, &element, sizeof *Eptr);

    // Add element to list of elements
    increase_list_size(list, 1);
    list->elementPointers[list->size-1] = Eptr;
}

// ---------------------------------------
// GET FROM LIST
// ---------------------------------------


ListElement* list_get_element_ptr(List* list, unsigned int index)
{
    if (index >= list->size)
    {
        ERROR("Tried to get index: %u, when max index is %u in List.", index, list->size-1);
        return NULL;
    }

    return list->elementPointers[index];
}

// ---------------------------------------
// CONSTRUCTOR
// ---------------------------------------

List create_list()
{
    List list;
    list.size = 0;
    list.elementPointers = malloc(0);
    return list;
}
