#include "dynamicArray.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void print_DA_info(DynamicArray *dArr, char *additionalInfo)
{
    CharArray *strArr = create_CA(""); // utilize char array

    if (dArr->DATA_TYPE != DA_DATA_NA)
    {
        char buffor[255];
        for (size_t i=0; i<dArr->maxSize; i++)
        {
            DA_to_str(buffor, dArr, i);
            append_CA(strArr, buffor);
            append_CA(strArr, ", ");
        }
        pop_CA_back(strArr); // pop space
        pop_CA_back(strArr); // pop comma

    } else {append_CA(strArr, "Unknown data type, Unable to convert to text.");}

    printf("---------------------------------\n");
    printf("DYNAMIC ARRAY INFO:\n");
    printf("maxSize: "TYPE_SIZE_T", dataTypeSize: "TYPE_SIZE_T"\n", dArr->maxSize, dArr->dataTypeSize);
    printf("Content: %s\n", strArr->arrayPointer);
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");

    destroy_CA(&strArr);
}

// ---------------------------------------
// STRING CONVERSION
// ---------------------------------------

void DA_to_str(char *buffor, DynamicArray *arr, size_t index)
{
    sprintf(buffor,"%s","err");

    if (arr->DATA_TYPE == DA_DATA_UCHAR)
    { sprintf(buffor,"%c", *(unsigned char*)ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index)); }
    else if (arr->DATA_TYPE == DA_DATA_CHAR)
    { sprintf(buffor,"%c", *(char*)ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index)); }
    else if (arr->DATA_TYPE == DA_DATA_UINT)
    { sprintf(buffor,"%u", *(unsigned int*)ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index)); }
    else if (arr->DATA_TYPE == DA_DATA_INT)
    { sprintf(buffor,"%d", *(int*)ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index)); }
    else if (arr->DATA_TYPE == DA_DATA_USHORT)
    { sprintf(buffor,"%hu", *(unsigned short*)ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index)); }
    else if (arr->DATA_TYPE == DA_DATA_SHORT)
    { sprintf(buffor,"%hd", *(short*)ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index)); }
}

// ---------------------------------------
// SIZE MANAGEMENT
// ---------------------------------------

ARR_ERR_CODE increase_DA_size(DynamicArray *arr, size_t addSize)
{
    if (size_t_will_overflow(arr->maxSize, addSize)) { ERROR_MSG("Size overflow."); return ARR_ERR_OVER;}
    size_t increasedSize = arr->maxSize + addSize;

    void* tmp = realloc(arr->arrayPointer, arr->dataTypeSize*increasedSize);
    if (tmp == NULL) { ERROR_MSG("Unable to realloc."); return ARR_ERR_REALLOC; }
    arr->arrayPointer = tmp;

    // NULL new elements
    for (size_t i=arr->maxSize; i<increasedSize; i++)
    {
        memset(ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, i), 0, arr->dataTypeSize);
    }

    arr->maxSize += addSize;
    return ARR_ERR_OK;
}


ARR_ERR_CODE decrease_DA_size(DynamicArray *arr, size_t minusSize)
{
    // If decrease more than array size just make array size 0
    if( size_t_will_underflow(arr->maxSize, minusSize) ) { minusSize = arr->maxSize; } // Overflow check
    size_t decreasedSize = arr->maxSize - minusSize;

    void* tmp = realloc(arr->arrayPointer, arr->dataTypeSize*decreasedSize);
    if (tmp == NULL) { ERROR_MSG("Unable to realloc."); return ARR_ERR_REALLOC; }
    arr->arrayPointer = tmp;

    arr->maxSize -= minusSize;

    return ARR_ERR_OK;
}


ARR_ERR_CODE resize_DA(DynamicArray *arr, size_t destSize)
{
    ARR_ERR_CODE err_result = ARR_ERR_OK;

    if (destSize > arr->maxSize)
    {
        size_t addSize = destSize - arr->maxSize;
        err_result = increase_DA_size(arr, addSize);
    }
    else if (destSize < arr->maxSize)
    {
        size_t minusSize = arr->maxSize - destSize;
        err_result = decrease_DA_size(arr, minusSize);
    }

    return err_result;
}

// ---------------------------------------
// CHANGE ARRAY MANAGEMENT
// ---------------------------------------

ARR_ERR_CODE set_DA_at(DynamicArray *arr, void* data, size_t index)
{
    if (index >= arr->maxSize)
    {
        ERROR_MSG("Tried to set index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in DynamicArray.", index, arr->maxSize-1);
        return ARR_ERR_INDEX;
    }

    memcpy( ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index),
            data, arr->dataTypeSize);

    return ARR_ERR_OK;
}


ARR_ERR_CODE append_DA(DynamicArray *arr, void* data, size_t dataSize)
{
    ARR_ERR_CODE err_result = ARR_ERR_OK;
    size_t oldMaxSize = arr->maxSize;

    // Increase the max size
    err_result = increase_DA_size(arr, dataSize);

    // Copy the array
    for (size_t i=0; i<dataSize; i++)
    {
        size_t arrIndex = i + oldMaxSize;
        memcpy( ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, arrIndex),
                ARR_PTR_AT(data, arr->dataTypeSize, i), arr->dataTypeSize);
    }

    return err_result;
}

// ---------------------------------------
// GET FROM ARRAY
// ---------------------------------------

void* get_DA_ptr_at(DynamicArray *arr, size_t index)
{
    if (index >= arr->maxSize)
    {
        ERROR_MSG("Tried to get index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in DynamicArray.", index, arr->maxSize-1);
        return NULL;
    }
    return ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index);
}


bool is_DA_empty(DynamicArray *arr)
{
    bool isEmpty = true;
    if (arr->maxSize > 0) { isEmpty = false; }
    return isEmpty;
}

// ---------------------------------------
// CONSTRUCTOR
// ---------------------------------------

/* Constructor for DynamicArray */
DynamicArray* create_DA(void *data, size_t size, size_t dataTypeSize, DA_DATA_TYPE DATA_TYPE)
{
    if (size < 1){ ERROR_MSG("Tried to create empty dynamic Array!"); }
    DynamicArray arr;

    // Assign array values
    arr.maxSize = size;
    arr.dataTypeSize = dataTypeSize;
    arr.DATA_TYPE = DATA_TYPE;

    // Alocate space for the array
    arr.arrayPointer = malloc( size*dataTypeSize );
    if (arr.arrayPointer == NULL) {ERROR_MSG("Failed to malloc."); exit(1); }

    // Copy the array
    for (size_t i=0; i<arr.maxSize; i++)
    {
        memcpy( ARR_PTR_AT(arr.arrayPointer, arr.dataTypeSize, i),
                ARR_PTR_AT(data, arr.dataTypeSize, i), arr.dataTypeSize);
    }

    // Allocate space for the array and copy it
    DynamicArray *arrPtr = malloc(sizeof *arrPtr); //DEBUG("Creating array: %p", arrPtr);
    if (arrPtr == NULL) { return NULL; }
    memcpy(arrPtr, &arr, sizeof *arrPtr);

    return arrPtr;
}

// ---------------------------------------
// DESTRUCTOR
// ---------------------------------------

void destroy_DA(DynamicArray **ptrToArr)
{
    DynamicArray *arr = *ptrToArr; //DEBUG("Destroying charArray: %p", arr);

    free_and_NULL(arr->arrayPointer);
    free_and_NULL(*ptrToArr);
}
