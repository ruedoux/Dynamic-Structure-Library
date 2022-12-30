#include "charArray.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void print_CA_info( CharArray *arr, char *additionalInfo)
{
    printf("---------------------------------\n");
    printf("CHAR ARRAY INFO:\n");
    printf("maxSize: "TYPE_SIZE_T"\n", arr->maxSize);
    printf("text: ");
    for (size_t i=0;i<arr->maxSize;i++)
    {
        char ch = arr->arrayPointer[i];
        if ((unsigned)ch>126 || (unsigned)ch<32) { ch = '#'; }
        putchar(ch);
    }
    printf("\n");
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");
}

// ---------------------------------------
// SIZE MANAGEMENT
// ---------------------------------------

ARR_ERR_CODE increase_CA_size( CharArray *arr, size_t addSize)
{
    // +1 to size so i can put null at the end
    if (size_t_will_overflow(arr->maxSize,addSize)) { ERROR_MSG("Size overflow."); return ARR_ERR_OVER;}
    size_t increasedSize = arr->maxSize + addSize;

    void* tmp = realloc(arr->arrayPointer, sizeof(char)*(increasedSize + 1));
    if (tmp == NULL) { ERROR_MSG("Unable to realloc."); return ARR_ERR_REALLOC; }
    arr->arrayPointer = tmp;

    // NULL new elements
    for (size_t i=arr->maxSize; i<increasedSize; i++){ arr->arrayPointer[i] = '\0'; }
    
    arr->maxSize += addSize;

    return ARR_ERR_OK;
}


ARR_ERR_CODE decrease_CA_size( CharArray *arr, size_t minusSize)
{
    // If decrease more than array size just make array size 0
    if( size_t_will_underflow(arr->maxSize, minusSize) ) { minusSize = arr->maxSize; } // Overflow check
    size_t decreasedSize = arr->maxSize - minusSize;

    // +1 to size so i can put null at the end
    void* tmp = realloc(arr->arrayPointer, sizeof(char)*(decreasedSize + 1));
    if (tmp == NULL) { ERROR_MSG("Unable to realloc"); return ARR_ERR_REALLOC; }
    arr->arrayPointer = tmp;

    arr->maxSize -= minusSize;
    arr->arrayPointer[arr->maxSize] = '\0'; // Termination of array

    return ARR_ERR_OK;
}


ARR_ERR_CODE resize_CA(CharArray *arr, size_t destSize)
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
char pop_CA_back(CharArray *arr)
{
    if ( !(arr->maxSize > 0) ) { return '\n'; }
    char ch = arr->arrayPointer[arr->maxSize - 1];
    decrease_CA_size(arr, 1);
    return ch;
}


ARR_ERR_CODE set_CA_char(CharArray *arr, char ch, size_t index)
{
    if (index >= arr->maxSize)
    {
        ERROR_MSG("Tried to set index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in CharArray.", index, arr->maxSize-1);
        return ARR_ERR_INDEX;
    }

    arr->arrayPointer[index] = ch;
    return ARR_ERR_OK;
}


ARR_ERR_CODE append_CA(CharArray *arr, char *str)
{
    ARR_ERR_CODE err_result = ARR_ERR_OK;
    size_t preIncreaseSize = arr->maxSize;

    err_result = increase_CA_size(arr, strlen(str));
    memcpy(arr->arrayPointer + preIncreaseSize, str, strlenT(str));

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

    for (size_t i=0; i<arr->maxSize; i++)
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


char get_CA_char(CharArray *arr, size_t index)
{
    if (index >= arr->maxSize)
    {
        ERROR_MSG("Tried to get index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in CharArray.", index, arr->maxSize-1);
        return -1;
    }
    return arr->arrayPointer[index];
}


bool is_CA_empty(CharArray *arr)
{
    bool isEmpty = true;
    if (arr->maxSize > 0) { isEmpty = false; }
    return isEmpty;
}


// ---------------------------------------
// CONSTRUCTOR
// ---------------------------------------

CharArray* create_CA(char *str)
{
    CharArray charArr;

    charArr.maxSize = strlen(str);

    // Alocate space for string and copy it
    charArr.arrayPointer = calloc(strlenT(str), sizeof(char));
    if (charArr.arrayPointer == NULL) {ERROR_MSG("Failed to calloc."); exit(1); }
    memcpy(charArr.arrayPointer, str, strlenT(str));

    // Allocate space for the char array and copy it
    CharArray *ArrPtr = malloc(sizeof *ArrPtr);  //DEBUG_MSG("Creating charArray: %p", ArrPtr);
    if (ArrPtr == NULL) { return NULL; }
    memcpy(ArrPtr, &charArr, sizeof *ArrPtr);

    return ArrPtr;
}

// ---------------------------------------
// DESTRUCTOR
// ---------------------------------------

void destroy_CA(CharArray **ptrToArr)
{
    CharArray *arr = *ptrToArr; //DEBUG_MSG("Destroying charArray: %p", arr);

    free_and_NULL(arr->arrayPointer);
    free_and_NULL(*ptrToArr);
}
