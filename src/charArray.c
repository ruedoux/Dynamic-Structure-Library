#include "charArray.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void throw_CA_error(char *msg)
{
    printf("---------------------------------\n");
    printf("ERROR:\n");
    printf("%s\n",msg);
    printf("---------------------------------\n");
}


void print_CA_info(struct charArray *arr, char *additionalInfo)
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

CA_ERR_CODE increase_CA_size(struct charArray *arr, unsigned int addSize)
{
    // +1 to size so i can put null at the end
    void* tmp = realloc(arr->arrayPointer,sizeof(char)*arr->size + sizeof(char)*addSize + 1);
    if (tmp == NULL) { throw_CA_error("Unable to realloc"); return CA_ERR_REALLOC; }
    
    arr->maxSize += addSize;
    arr->arrayPointer[arr->size+1] = '\0'; // Termination of array

    return CA_ERR_OK;
}


CA_ERR_CODE decrease_CA_size(struct charArray *arr, unsigned int minusSize)
{
    // If decrease more than array size just make array size 0
    int sizeTest = arr->maxSize - minusSize;
    if( sizeTest < 0 ) { minusSize = arr->maxSize; }

    // +1 to size so i can put null at the end
    void* tmp = realloc(arr->arrayPointer,sizeof(char)*arr->size - sizeof(char)*minusSize + 1);
    if (tmp == NULL) { throw_CA_error("Unable to realloc"); return CA_ERR_REALLOC; }

    arr->maxSize -= minusSize;
    if (arr->size > arr->maxSize){ arr->size = arr->maxSize; }

    arr->arrayPointer[arr->size] = '\0'; // Termination of array

    return CA_ERR_OK;
}


CA_ERR_CODE resize_CA(struct charArray *arr, unsigned int destSize)
{
    CA_ERR_CODE err_result = CA_ERR_OK;

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
char pop_CA_back(struct charArray *arr)
{
    char ch = arr->arrayPointer[arr->size - 1];
    decrease_CA_size(arr, 1);
    return ch;
}


CA_ERR_CODE set_CA_char(struct charArray *arr, char ch, unsigned int index)
{
    if (index >= arr->maxSize)
    {
        char content[255];
        sprintf(content,"Tried to set index: %u, when max index is %u in charArray.",
                       index, arr->maxSize-1);

        throw_CA_error(content);
        return CA_ERR_INDEX;
    }

    arr->arrayPointer[index] = ch;
    if (index > arr->size-1){ arr->size = index + 1; }

    return CA_ERR_OK;
}


CA_ERR_CODE append_CA(struct charArray *arr, char *str)
{
    CA_ERR_CODE err_result = CA_ERR_OK;

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

int find_CA_str(struct charArray *arr, char *str)
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


char get_CA_char(struct charArray *arr, unsigned int index)
{
	if (index >= arr->maxSize)
	{
		char content[255];
		sprintf(content,"Tried to get index: %u, when max index is %u in charArray.",
		               index, arr->maxSize-1);

		throw_CA_error(content);
        return -1;
	}
	return arr->arrayPointer[index];
}


char is_CA_empty(struct charArray *arr)
{
    char isEmpty = 1;
    if (arr->size > 0) { isEmpty = 0; }
    return isEmpty;
}


// ---------------------------------------
// CONSTRUCTOR
// ---------------------------------------

struct charArray createCA(char *str)
{
    struct charArray arr;
    unsigned int maxSize = strlen(str);

    arr.size = maxSize;
    arr.maxSize = maxSize;
    arr.arrayPointer = calloc(maxSize + 1, sizeof(char));  // Alocate memory
    strcpy(arr.arrayPointer,str);                          // Copy string to arrayPointer

    return arr;
}

// ---------------------------------------
// Destructor
// ---------------------------------------

void destroyCA(struct charArray *arr)
{
    free(arr->arrayPointer);
}

// ---------------------------------------
// ARRAY INTERFACE
// ---------------------------------------

/* Library interface */
const struct charArray CharArray = {
  .increase_CA_size = increase_CA_size,
  .set_CA_char = set_CA_char,
  .createCA = createCA,
  .throw_CA_error = throw_CA_error,
  .append_CA = append_CA,
  .decrease_CA_size = decrease_CA_size,
  .print_CA_info = print_CA_info,
  .get_CA_char = get_CA_char,
  .is_CA_empty = is_CA_empty,
  .find_CA_str = find_CA_str,
  .resize_CA = resize_CA,
  .pop_CA_back = pop_CA_back,
  .destroyCA = destroyCA
};
