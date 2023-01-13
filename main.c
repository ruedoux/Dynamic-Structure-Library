/*
 * This file serves only as example usage of the library
 * Includes running unit tests for the library
*/

#include "test/unitTest.h"


void example_CA()
{
    DSL_String *arr = str_create("");
    str_print_info(arr,"Creation of char array (String).\n");

    // START------------------------------------
    str_append(arr, "good-job-is-done");
    str_print_info(arr,"Append \"good-job-is-done\" result.\n");
    // END--------------------------------------

    // START------------------------------------
    char content[255];
    sprintf(content,"found = %s, on index: %d\n", "job", str_find(arr, "job"));
    str_print_info(arr,content);
    // END--------------------------------------

    // START------------------------------------
    str_resize(arr, 5);
    str_print_info(arr,"Resize to 5 result.\n");
    // END--------------------------------------

    // START------------------------------------
    str_append(arr, "1234567");
    str_print_info(arr,"Append 1234567 result.\n");
    // END--------------------------------------

    // START------------------------------------
    char contentT[255];
    sprintf(contentT,"Popped letter %c\n", str_pop_back(arr));
    str_print_info(arr,contentT);
    // END--------------------------------------

    // START------------------------------------
    str_decrease_size(arr, 999);
    str_print_info(arr,"Decrease size by 999 result.\n");
    // END--------------------------------------

    str_destroy(&arr);
}


void example_DA_char()
{
    char chTest[] = "Test array of chars";
    DynamicArray *chArr = da_create(chTest, strlen(chTest), sizeof *chTest, DA_DATA_CHAR);
    da_print_info(chArr,"Creating dynamic array.\n");

    // START------------------------------------
    da_resize(chArr, 4);
    da_print_info(chArr,"Resize to 4 result.\n");
    // END--------------------------------------

    // START------------------------------------
    da_set_at(chArr, "x", 2);
    da_print_info(chArr,"Set x at index 2 result.\n");
    // END--------------------------------------

    // START------------------------------------
    da_append(chArr, " ABCD", 5);
    da_print_info(chArr,"Append \" ABCD\" result.\n");
    // END--------------------------------------

    // START------------------------------------
    char content[255];
    sprintf(content,"Data at index 6 is: %c\n", *(char *)da_get_ptr_at(chArr, 6));
    da_print_info(chArr,content);
    // END--------------------------------------

    da_destroy(&chArr);
}


void example_DA_int()
{
    int intTest[] = {1,2,3,4,5,6};
    DynamicArray *intArr = da_create(intTest, 6, sizeof *intTest, DA_DATA_INT);
    da_print_info(intArr,"Creation of dynamic array.\n");

    // START------------------------------------
    da_resize(intArr, 3);
    da_print_info(intArr,"Resize to 3 result.\n");
    // END------------------------------------

    // START------------------------------------
    int val = 4564;
    da_set_at(intArr, &val, 2);
    da_print_info(intArr,"Set 4564 at index 2 result.\n");
    // END--------------------------------------

    // START------------------------------------
    int values[] = {8,9};
    da_append(intArr, values, 2);
    da_print_info(intArr,"Append {8,9} result.\n");
    // END--------------------------------------

    // START------------------------------------
    da_resize(intArr, 10);
    da_print_info(intArr,"Resize to 10 result.\n");
    // END------------------------------------

    da_destroy(&intArr);
}


void example_DSL_List()
{
    DSL_List *list = list_create();

    // START------------------------------------
    char *val1 = "abc";
    int   val2 = 111;
    char *val3 = "some text";
    list_append(list, val1, strlenT(val1), "str");
    list_append(list, &val2, sizeof val2, "int");
    list_append(list, val3, strlenT(val3), "str");

    char buffor[255];
    sprintf(buffor,"Content of element index 0: %s\n", (char*)list_obj_ptr_at(list, 0));
    list_print_info(list, buffor);

    sprintf(buffor,"Content of element index 1: %d\n", *(int*)list_obj_ptr_at(list, 1));
    list_print_info(list, buffor);

    sprintf(buffor,"Content of element index 2: %s\n", (char*)list_obj_ptr_at(list, 2));
    list_print_info(list, buffor);
    // END--------------------------------------

    // START------------------------------------
    list_resize(list, 10);
    list_print_info(list, "Resize to 10 result.\n");
    // END--------------------------------------

    // START------------------------------------
    list_resize(list, 2);
    list_print_info(list, "Resize to 2 result.\n");
    // END--------------------------------------

    list_destroy(&list);
}


int main()
{
    srand(time(NULL));

    //example_CA();        // Char array example (String)
    //example_DA_char();   // Dynamic array example(char)
    //example_DA_int();    // Dynamic array example (int)
    //example_DSL_List();      // DSL_List example

    UT_run_all();   // UNIT TESTS

    return 0;
}
