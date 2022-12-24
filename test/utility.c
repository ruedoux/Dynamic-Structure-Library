#include "utility.h"


char* alloc_random_charArr(size_t size)
{
    char *randArr = malloc(size + 1);
    for (size_t i=0; i<size; i++)
    {
        char randChar = (char)(rand()%94 + 31);
        randArr[i] = randChar;
    }
    randArr[size] = '\0';
    return randArr;
}
