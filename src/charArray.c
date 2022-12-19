#include "charArray.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void print_CA_info( CharArray *arr, char *additionalInfo)
{
    printf("---------------------------------\n");
    printf("CHAR ARRAY INFO:\n");
    printf("size: "TYPE_SIZE_T", maxSize: "TYPE_SIZE_T"\n", arr->size, arr->maxSize);
    printf("text: %s\n", arr->arrayPointer);
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");
}

// ---------------------------------------
// SIZE MANAGEMENT
// ---------------------------------------

ARR_ERR_CODE increase_CA_size( CharArray *arr, size_t addSize)
{
    // +1 to size so i can put null at the end
    if (size_t_will_overflow_add(arr->maxSize,addSize)) { DEBUG("Size overflow."); return ARR_ERR_OVER;}
    size_t increaseSize = arr->maxSize + addSize;

    void* tmp = realloc(arr->arrayPointer, sizeof(char)*(increaseSize + 1));
    if (tmp == NULL) { ERROR("Unable to realloc."); return ARR_ERR_REALLOC; }
    arr->arrayPointer = tmp;
    
    arr->maxSize += addSize;
    arr->arrayPointer[arr->size+1] = '\0'; // Termination of array

    return ARR_ERR_OK;
}


ARR_ERR_CODE decrease_CA_size( CharArray *arr, size_t minusSize)
{
    // If decrease more than array size just make array size 0
    if( size_t_will_overflow_minus(arr->maxSize, minusSize) ) { minusSize = arr->maxSize; } // Overflow check
    size_t decreasedSize = arr->maxSize - minusSize;

    // +1 to size so i can put null at the end
    void* tmp = realloc(arr->arrayPointer, sizeof(char)*(decreasedSize + 1));
    if (tmp == NULL) { ERROR("Unable to realloc"); return ARR_ERR_REALLOC; }
    arr->arrayPointer = tmp;

    arr->maxSize -= minusSize;
    if (arr->size > arr->maxSize){ arr->size = arr->maxSize; }

    arr->arrayPointer[arr->size] = '\0'; // Termination of array

    return ARR_ERR_OK;
}


ARR_ERR_CODE resize_CA( CharArray *arr, size_t destSize)
{
    ARR_ERR_CODE err_result = ARR_ERR_OK;

    if (destSize > arr->maxSize)
    {
        size_t addSize = destSize - arr->maxSize;
        err_result = increase_CA_size(arr, addSize);
    }
    else if (destSize < arr->maxSize)
    {
        size_t minusSize = arr->maxSize - destSize;
        err_result = decrease_CA_size(arr, minusSize);
    }

    return err_result;
}

// ---------------------------------------
// CHANGE ARRAY MANAGEMENT
// ---------------------------------------

/* Pops last char from array */
char pop_CA_back( CharArray *arr)
{
    char ch = arr->arrayPointer[arr->size - 1];
    decrease_CA_size(arr, 1);
    return ch;
}


ARR_ERR_CODE set_CA_char( CharArray *arr, char ch, size_t index)
{
    if (index >= arr->maxSize)
    {
        ERROR("Tried to set index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in CharArray.", index, arr->maxSize-1);
        return ARR_ERR_INDEX;
    }

    arr->arrayPointer[index] = ch;
    if (index > arr->size-1){ arr->size = index + 1; }

    return ARR_ERR_OK;
}


ARR_ERR_CODE append_CA( CharArray *arr, char *str)
{
    ARR_ERR_CODE err_result = ARR_ERR_OK;

    size_t strSize = strlen(str);
    size_t lenCombined = strSize + arr->size;
    if (lenCombined > arr->maxSize)
    {
        size_t increaseSize = lenCombined - arr->maxSize;
        err_result = increase_CA_size(arr, increaseSize);
    }

    strcpy(arr->arrayPointer + arr->size, str);
    arr->size += strSize;

    return err_result;
}

// ---------------------------------------
// GET FROM ARRAY
// ---------------------------------------

int find_CA_str(CharArray *arr, char *str)
{
    size_t strSize = strlen(str);
    size_t matchingIndex = 0;
    int foundIndex = -1;

    for (size_t i=0; i<arr->size; i++)
    {
        if (arr->arrayPointer[i] == str[matchingIndex])
        {
            matchingIndex++;
            if (matchingIndex == strSize) { foundIndex = i - matchingIndex + 1; break; }
            continue;
        }
        matchingIndex = 0;
        if (arr->arrayPointer[i] == str[matchingIndex]) { matchingIndex++; }
    }

    return foundIndex;
}


char get_CA_char( CharArray *arr, size_t index)
{
    if (index >= arr->maxSize)
    {
        ERROR("Tried to get index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in CharArray.", index, arr->maxSize-1);
        return -1;
    }
    return arr->arrayPointer[index];
}


char is_CA_empty( CharArray *arr)
{
    char isEmpty = 1;
    if (arr->size > 0) { isEmpty = 0; }
    return isEmpty;
}


// ---------------------------------------
// CONSTRUCTOR
// ---------------------------------------

 CharArray create_CA(char *str)
{
    CharArray arr;
    size_t maxSize = strlen(str);

    arr.size = maxSize;
    arr.maxSize = maxSize;

    arr.arrayPointer = calloc(maxSize + 1, sizeof(char));
    if (arr.arrayPointer == NULL) {ERROR("Failed to calloc."); exit(1); }

    strcpy(arr.arrayPointer, str);

    return arr;
}

// ---------------------------------------
// DESTRUCTOR
// ---------------------------------------

void destroy_CA( CharArray *arr)
{
    free(arr->arrayPointer);
}
