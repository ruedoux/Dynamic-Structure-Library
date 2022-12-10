#include "CharArray.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void print_CA_info( CharArray *arr, char *additionalInfo)
{
    printf("---------------------------------\n");
    printf("CHAR ARRAY INFO:\n");
    printf("size: %u, maxSize: %u\n", arr->size, arr->maxSize);
    printf("text: %s\n", arr->arrayPointer);
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");
}

// ---------------------------------------
// SIZE MANAGEMENT
// ---------------------------------------

ARR_ERR_CODE increase_CA_size( CharArray *arr, unsigned int addSize)
{
    // +1 to size so i can put null at the end
    void* tmp = realloc(arr->arrayPointer,sizeof(char)*arr->size + sizeof(char)*addSize + 1);
    if (tmp == NULL) { ERROR("Unable to realloc."); return ARR_ERR_REALLOC; }
    
    arr->maxSize += addSize;
    arr->arrayPointer[arr->size+1] = '\0'; // Termination of array

    return ARR_ERR_OK;
}


ARR_ERR_CODE decrease_CA_size( CharArray *arr, unsigned int minusSize)
{
    // If decrease more than array size just make array size 0
    int sizeTest = arr->maxSize - minusSize;
    if( sizeTest < 0 ) { minusSize = arr->maxSize; }

    // +1 to size so i can put null at the end
    void* tmp = realloc(arr->arrayPointer,sizeof(char)*arr->size - sizeof(char)*minusSize + 1);
    if (tmp == NULL) { ERROR("Unable to realloc"); return ARR_ERR_REALLOC; }

    arr->maxSize -= minusSize;
    if (arr->size > arr->maxSize){ arr->size = arr->maxSize; }

    arr->arrayPointer[arr->size] = '\0'; // Termination of array

    return ARR_ERR_OK;
}


ARR_ERR_CODE resize_CA( CharArray *arr, unsigned int destSize)
{
    ARR_ERR_CODE err_result = ARR_ERR_OK;

    if (destSize > arr->maxSize)
    {
        unsigned int addSize = destSize - arr->maxSize;
        err_result = increase_CA_size(arr, addSize);
    }
    else if (destSize < arr->maxSize)
    {
        unsigned int minusSize = arr->maxSize - destSize;
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


ARR_ERR_CODE set_CA_char( CharArray *arr, char ch, unsigned int index)
{
    if (index >= arr->maxSize)
    {
        ERROR("Tried to set index: %u, when max index is %u in CharArray.", index, arr->maxSize-1);
        return ARR_ERR_INDEX;
    }

    arr->arrayPointer[index] = ch;
    if (index > arr->size-1){ arr->size = index + 1; }

    return ARR_ERR_OK;
}


ARR_ERR_CODE append_CA( CharArray *arr, char *str)
{
    ARR_ERR_CODE err_result = ARR_ERR_OK;

    unsigned int strSize = strlen(str);
    unsigned int lenCombined = strSize + arr->size;
    if (lenCombined > arr->maxSize)
    {
        unsigned int increaseSize = lenCombined - arr->maxSize;
        err_result = increase_CA_size(arr, increaseSize);
    }

    strcpy(arr->arrayPointer + arr->size, str);
    arr->size += strSize;

    return err_result;
}

// ---------------------------------------
// GET FROM ARRAY
// ---------------------------------------

int find_CA_str( CharArray *arr, char *str)
{
    int strSize = strlen(str);
    int matchingIndex = 0;
    int foundIndex = -1;

    for (int i=0; i<arr->size; i++)
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


char get_CA_char( CharArray *arr, unsigned int index)
{
    if (index >= arr->maxSize)
    {
        ERROR("Tried to get index: %u, when max index is %u in CharArray.", index, arr->maxSize-1);
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

 CharArray createCA(char *str)
{
    CharArray arr;
    unsigned int maxSize = strlen(str);

    arr.size = maxSize;
    arr.maxSize = maxSize;
    arr.arrayPointer = calloc(maxSize + 1, sizeof(char));  // Alocate memory
    strcpy(arr.arrayPointer,str);                          // Copy string to arrayPointer

    return arr;
}

// ---------------------------------------
// DESTRUCTOR
// ---------------------------------------

void destroyCA( CharArray *arr)
{
    free(arr->arrayPointer);
}
