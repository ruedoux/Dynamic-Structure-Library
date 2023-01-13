#include "DSL_String.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void str_print_info( DSL_String *arr, char *additionalInfo)
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

DSL_ERR_CODE str_increase_size( DSL_String *arr, size_t addSize)
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


DSL_ERR_CODE str_decrease_size( DSL_String *arr, size_t minusSize)
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


DSL_ERR_CODE str_resize(DSL_String *arr, size_t destSize)
{
    DSL_ERR_CODE err_result = ARR_ERR_OK;

    if (destSize > arr->maxSize)
    {
        size_t addSize = destSize - arr->maxSize;
        err_result = str_increase_size(arr, addSize);
    }
    else if (destSize < arr->maxSize)
    {
        size_t minusSize = arr->maxSize - destSize;
        err_result = str_decrease_size(arr, minusSize);
    }

    return err_result;
}

// ---------------------------------------
// CHANGE ARRAY MANAGEMENT
// ---------------------------------------

/* Pops last char from array */
char str_pop_back(DSL_String *arr)
{
    if ( !(arr->maxSize > 0) ) { return '\n'; }
    char ch = arr->arrayPointer[arr->maxSize - 1];
    str_decrease_size(arr, 1);
    return ch;
}


DSL_ERR_CODE str_set_char(DSL_String *arr, char ch, size_t index)
{
    if (index >= arr->maxSize)
    {
        ERROR_MSG("Tried to set index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in DSL_String.", index, arr->maxSize-1);
        return ARR_ERR_INDEX;
    }

    arr->arrayPointer[index] = ch;
    return ARR_ERR_OK;
}


DSL_ERR_CODE str_append(DSL_String *arr, char *str)
{
    DSL_ERR_CODE err_result = ARR_ERR_OK;
    size_t preIncreaseSize = arr->maxSize;

    err_result = str_increase_size(arr, strlen(str));
    memcpy(arr->arrayPointer + preIncreaseSize, str, strlenT(str));

    return err_result;
}

// ---------------------------------------
// GET FROM ARRAY
// ---------------------------------------

int str_find(DSL_String *arr, char *str)
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


char str_get_char(DSL_String *arr, size_t index)
{
    if (index >= arr->maxSize)
    {
        ERROR_MSG("Tried to get index: "TYPE_SIZE_T", when max index is "TYPE_SIZE_T" in DSL_String.", index, arr->maxSize-1);
        return -1;
    }
    return arr->arrayPointer[index];
}


bool str_is_empty(DSL_String *arr)
{
    bool isEmpty = true;
    if (arr->maxSize > 0) { isEmpty = false; }
    return isEmpty;
}


// ---------------------------------------
// CONSTRUCTOR
// ---------------------------------------

DSL_String* str_create(char *str)
{
    DSL_String charArr;

    charArr.maxSize = strlen(str);

    // Alocate space for string and copy it
    charArr.arrayPointer = calloc(strlenT(str), sizeof(char));
    if (charArr.arrayPointer == NULL) {ERROR_MSG("Failed to calloc."); exit(1); }
    memcpy(charArr.arrayPointer, str, strlenT(str));

    // Allocate space for the char array and copy it
    DSL_String *ArrPtr = malloc(sizeof *ArrPtr);  //DEBUG_MSG("Creating DSL_String: %p", ArrPtr);
    if (ArrPtr == NULL) { return NULL; }
    memcpy(ArrPtr, &charArr, sizeof *ArrPtr);

    return ArrPtr;
}

// ---------------------------------------
// DESTRUCTOR
// ---------------------------------------

void str_destroy(DSL_String **ptrToArr)
{
    DSL_String *arr = *ptrToArr; //DEBUG_MSG("Destroying DSL_String: %p", arr);

    free_and_NULL(arr->arrayPointer);
    free_and_NULL(*ptrToArr);
}
