#include "dynamicArray.h"

// ---------------------------------------
// DEBUG MANAGEMENT
// ---------------------------------------

void throw_DA_error_abort(char *msg)
{
    printf("---------------------------------\n");
    printf("ERROR:\n");
    printf("%s\n",msg);
    printf("Aborting the program.\n");
    printf("---------------------------------\n");

    exit(1);
}


void print_DA_info(struct dynamicArray *dArr, char *additionalInfo)
{
    struct charArray strArr = CharArray.createCA("");

    if (dArr->DATA_TYPE != DA_DATA_NA)
    {
        char buffor[255];
        for (size_t i=0; i<dArr->size; i++)
        {
            DynamicArray.voidPtr_to_str(buffor, dArr, i);
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
void voidPtr_to_str(char *buffor, struct dynamicArray *arr, size_t index)
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
// CONSTRUCTOR
// ---------------------------------------

/* Constructor for dynamicArray */
struct dynamicArray createDA(void *data, size_t size, size_t dataTypeSize, DA_DATA_TYPE DATA_TYPE)
{
    if (size < 1){ throw_DA_error_abort("Tried to create empty dynamic Array!"); }
    struct dynamicArray arr;

    // Assign array values
    arr.size = size;
    arr.maxSize = size;
    arr.dataTypeSize = dataTypeSize;
    arr.arrayPointer = malloc( size*arr.dataTypeSize );
    arr.DATA_TYPE = DATA_TYPE;

    // Copy the array
    for (size_t i=0; i<size; i++)
    {
        memcpy ( ARR_PTR_AT(arr.arrayPointer, arr.dataTypeSize, i), ARR_PTR_AT(data, arr.dataTypeSize, i), arr.dataTypeSize);
    }

    return arr;
}

// ---------------------------------------
// CONSTRUCTOR
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
  .throw_DA_error_abort = throw_DA_error_abort,
  .print_DA_info = print_DA_info,
  .destroyDA = destroyDA,
  .voidPtr_to_str = voidPtr_to_str
};
