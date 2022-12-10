#include "DynamicArray.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void print_DA_info(DynamicArray *dArr, char *additionalInfo)
{
    CharArray strArr = createCA(""); // utilize char array

    if (dArr->DATA_TYPE != DA_DATA_NA)
    {
        char buffor[255];
        for (size_t i=0; i<dArr->size; i++)
        {
            DA_to_str(buffor, dArr, i);
            append_CA(&strArr, buffor);
            append_CA(&strArr, ", ");
        }
        pop_CA_back(&strArr); // pop space
        pop_CA_back(&strArr); // pop comma

    } else {append_CA(&strArr,"Unknown data type, Unable to convert to text.");}

    printf("---------------------------------\n");
    printf("DYNAMIC ARRAY INFO:\n");
    printf("size: %d, maxSize: %d, dataTypeSize: %d\n", dArr->size, dArr->maxSize, dArr->dataTypeSize);
    printf("Content: %s\n", strArr.arrayPointer);
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");

    destroyCA(&strArr);
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

ARR_ERR_CODE increase_DA_size(DynamicArray *arr, unsigned int addSize)
{
    void* tmp = realloc(arr->arrayPointer, arr->dataTypeSize*arr->size + arr->dataTypeSize*addSize);
    if (tmp == NULL) { ERROR("Unable to realloc."); return ARR_ERR_REALLOC; }

    arr->maxSize += addSize;
    return ARR_ERR_OK;
}


ARR_ERR_CODE decrease_DA_size(DynamicArray *arr, unsigned int minusSize)
{
    // If decrease more than array size just make array size 0
    int sizeTest = arr->maxSize - minusSize;
    if( sizeTest < 0 ) { minusSize = arr->maxSize; }

    void* tmp = realloc(arr->arrayPointer, arr->dataTypeSize*arr->size - arr->dataTypeSize*minusSize);
    if (tmp == NULL) { ERROR("Unable to realloc."); return ARR_ERR_REALLOC; }

    arr->maxSize -= minusSize;
    if (arr->size > arr->maxSize){ arr->size = arr->maxSize; }

    return ARR_ERR_OK;
}


ARR_ERR_CODE resize_DA(DynamicArray *arr, unsigned int destSize)
{
    ARR_ERR_CODE err_result = ARR_ERR_OK;

    if (destSize > arr->maxSize)
    {
        unsigned int addSize = destSize - arr->maxSize;
        err_result = increase_DA_size(arr, addSize);
    }
    else if (destSize < arr->maxSize)
    {
        unsigned int minusSize = arr->maxSize - destSize;
        err_result = decrease_DA_size(arr, minusSize);
    }

    return err_result;
}

// ---------------------------------------
// CHANGE ARRAY MANAGEMENT
// ---------------------------------------

ARR_ERR_CODE set_DA_at(DynamicArray *arr, void* data, unsigned int index)
{
    printf("index: %d\n",index);
    if (index >= arr->maxSize)
    {
        ERROR("Tried to set index: %u, when max index is %u in DynamicArray.", index, arr->maxSize-1);
        return ARR_ERR_INDEX;
    }

    memcpy( ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index),
            data, arr->dataTypeSize);
    if (index > arr->size-1){ arr->size = index; }

    return ARR_ERR_OK;
}


ARR_ERR_CODE append_DA(DynamicArray *arr, void* data, unsigned int dataSize)
{
    ARR_ERR_CODE err_result = ARR_ERR_OK;

    unsigned int lenCombined = dataSize + arr->size;
    if (lenCombined > arr->maxSize)
    {
        unsigned int increaseSize = lenCombined - arr->maxSize;
        err_result = increase_DA_size(arr, increaseSize);
    }

    // Copy the array
    for (unsigned int i=0; i<dataSize; i++)
    {
        unsigned int arrIndex = i + arr->size;
        memcpy( ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, arrIndex),
                ARR_PTR_AT(data, arr->dataTypeSize, i), arr->dataTypeSize);
    }

    arr->size += dataSize;

    return err_result;
}

// ---------------------------------------
// GET FROM ARRAY
// ---------------------------------------

void* get_DA_ptr_at(DynamicArray *arr, unsigned int index)
{
    if (index >= arr->maxSize)
    {
        ERROR("Tried to get index: %u, when max index is %u in DynamicArray.", index, arr->maxSize-1);
        return NULL;
    }
    return ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index);
}


char is_DA_empty(DynamicArray *arr)
{
    char isEmpty = 1;
    if (arr->size > 0) { isEmpty = 0; }
    return isEmpty;
}

// ---------------------------------------
// CONSTRUCTOR
// ---------------------------------------

/* Constructor for DynamicArray */
DynamicArray createDA(void *data, size_t size, size_t dataTypeSize, DA_DATA_TYPE DATA_TYPE)
{
    if (size < 1){ ERROR("Tried to create empty dynamic Array!"); }
    DynamicArray arr;

    // Assign array values
    arr.size = size;
    arr.maxSize = size;
    arr.dataTypeSize = dataTypeSize;
    arr.arrayPointer = malloc( size*dataTypeSize );
    arr.DATA_TYPE = DATA_TYPE;

    // Copy the array
    for (size_t i=0; i<size; i++)
    {
        memcpy( ARR_PTR_AT(arr.arrayPointer, arr.dataTypeSize, i),
                ARR_PTR_AT(data, arr.dataTypeSize, i), arr.dataTypeSize);
    }

    return arr;
}

// ---------------------------------------
// DESTRUCTOR
// ---------------------------------------

void destroyDA(DynamicArray *arr)
{
    free(arr->arrayPointer);
}
