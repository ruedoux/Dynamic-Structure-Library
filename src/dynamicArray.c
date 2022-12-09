#include "dynamicArray.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void throw_DA_error(char *msg)
{
    printf("---------------------------------\n");
    printf("ERROR:\n");
    printf("%s\n",msg);
    printf("---------------------------------\n");
}


void print_DA_info(struct dynamicArray *dArr, char *additionalInfo)
{
    struct charArray strArr = CharArray.createCA(""); // utilize char array

    if (dArr->DATA_TYPE != DA_DATA_NA)
    {
        char buffor[255];
        for (size_t i=0; i<dArr->size; i++)
        {
            DynamicArray.DA_to_str(buffor, dArr, i);
            CharArray.append_CA(&strArr, buffor);
            CharArray.append_CA(&strArr, ", ");
        }
        CharArray.pop_CA_back(&strArr); // pop space
        CharArray.pop_CA_back(&strArr); // pop comma

    } else {CharArray.append_CA(&strArr,"Unknown data type, Unable to convert to text.");}

    printf("---------------------------------\n");
    printf("DYNAMIC ARRAY INFO:\n");
    printf("size: %d, maxSize: %d, dataTypeSize: %d\n", dArr->size, dArr->maxSize, dArr->dataTypeSize);
    printf("Content: %s\n", strArr.arrayPointer);
    if (strlen(additionalInfo) != 0) { printf("Additional info: "); printf("%s",additionalInfo); }
    printf("---------------------------------\n");

    CharArray.destroyCA(&strArr);
}

// ---------------------------------------
// STRING CONVERSION
// ---------------------------------------

void DA_to_str(char *buffor, struct dynamicArray *arr, size_t index)
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

DA_ERR_CODE increase_DA_size(struct dynamicArray *arr, unsigned int addSize)
{
    void* tmp = realloc(arr->arrayPointer, arr->dataTypeSize*arr->size + arr->dataTypeSize*addSize);
    if (tmp == NULL) { throw_DA_error("Unable to realloc"); return DA_ERR_REALLOC; }

    arr->maxSize += addSize;
    return DA_ERR_OK;
}


DA_ERR_CODE decrease_DA_size(struct dynamicArray *arr, unsigned int minusSize)
{
    // If decrease more than array size just make array size 0
    int sizeTest = arr->maxSize - minusSize;
    if( sizeTest < 0 ) { minusSize = arr->maxSize; }

    void* tmp = realloc(arr->arrayPointer, arr->dataTypeSize*arr->size - arr->dataTypeSize*minusSize);
    if (tmp == NULL) { throw_DA_error("Unable to realloc"); return DA_ERR_REALLOC; }

    arr->maxSize -= minusSize;
    if (arr->size > arr->maxSize){ arr->size = arr->maxSize; }

    return DA_ERR_OK;
}


DA_ERR_CODE resize_DA(struct dynamicArray *arr, unsigned int destSize)
{
    DA_ERR_CODE err_result = DA_ERR_OK;

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

DA_ERR_CODE set_DA_at(struct dynamicArray *arr, void* data, unsigned int index)
{
    printf("index: %d\n",index);
    if (index >= arr->maxSize)
    {
        char content[255];
        sprintf(content,"Tried to set index: %u, when max index is %u in dynamicArray.",
                       index, arr->maxSize-1);

        throw_DA_error(content);
        return DA_ERR_INDEX;
    }

    memcpy( ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index),
            data, arr->dataTypeSize);
    if (index > arr->size-1){ arr->size = index; }

    return DA_ERR_OK;
}


DA_ERR_CODE append_DA(struct dynamicArray *arr, void* data, unsigned int dataSize)
{
    DA_ERR_CODE err_result = DA_ERR_OK;

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

void* get_DA_ptr_at(struct dynamicArray *arr, unsigned int index)
{
	if (index >= arr->maxSize)
	{
		char content[255];
		sprintf(content,"Tried to get index: %u, when max index is %u in dynamicArray.",
		               index, arr->maxSize-1);

		throw_DA_error(content);
        return NULL;
	}
	return ARR_PTR_AT(arr->arrayPointer, arr->dataTypeSize, index);
}


char is_DA_empty(struct dynamicArray *arr)
{
    char isEmpty = 1;
    if (arr->size > 0) { isEmpty = 0; }
    return isEmpty;
}

// ---------------------------------------
// CONSTRUCTOR
// ---------------------------------------

/* Constructor for dynamicArray */
struct dynamicArray createDA(void *data, size_t size, size_t dataTypeSize, DA_DATA_TYPE DATA_TYPE)
{
    if (size < 1){ throw_DA_error("Tried to create empty dynamic Array!"); }
    struct dynamicArray arr;

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

void destroyDA(struct dynamicArray *arr)
{
    free(arr->arrayPointer);
}

// ---------------------------------------
// ARRAY INTERFACE
// ---------------------------------------

/* Library interface */
const struct dynamicArray DynamicArray = {
  .createDA = createDA,
  .throw_DA_error = throw_DA_error,
  .print_DA_info = print_DA_info,
  .destroyDA = destroyDA,
  .DA_to_str = DA_to_str,
  .resize_DA = resize_DA,
  .decrease_DA_size = decrease_DA_size,
  .increase_DA_size = increase_DA_size,
  .get_DA_ptr_at = get_DA_ptr_at,
  .is_DA_empty = is_DA_empty,
  .set_DA_at = set_DA_at,
  .append_DA = append_DA
};
