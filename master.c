#include "src/charArray.h"
#include "src/dynamicArray.h"
#include "src/List.h"


void test_CA()
{
    CharArray arr = create_CA("");
    print_CA_info(&arr,"Creation of char array (String).\n");

    // START------------------------------------
    append_CA(&arr, "good-job-is-done");
    print_CA_info(&arr,"Append \"good-job-is-done\" result.\n");
    // END--------------------------------------

    // START------------------------------------
    char content[255];
    sprintf(content,"found = %s, on index: %d\n", "job", find_CA_str(&arr, "job"));
    print_CA_info(&arr,content);
    // END--------------------------------------

    // START------------------------------------
    resize_CA(&arr, 5);
    print_CA_info(&arr,"Resize to 5 result.\n");
    // END--------------------------------------

    // START------------------------------------
    append_CA(&arr, "1234567");
    print_CA_info(&arr,"Append 1234567 result.\n");
    // END--------------------------------------

    // START------------------------------------
    char contentT[255];
    sprintf(contentT,"Popped letter %c\n", pop_CA_back(&arr));
    print_CA_info(&arr,contentT);
    // END--------------------------------------

    // START------------------------------------
    decrease_CA_size(&arr, 999);
    print_CA_info(&arr,"Decrease size by 999 result.\n");
    // END--------------------------------------

    destroy_CA(&arr);
}


void test_DA_char()
{
    char chTest[] = "Test array of chars";
    DynamicArray chArr = create_DA(chTest, strlen(chTest), sizeof *chTest, DA_DATA_CHAR);
    print_DA_info(&chArr,"Creating dynamic array.\n");

    // START------------------------------------
    resize_DA(&chArr, 4);
    print_DA_info(&chArr,"Resize to 4 result.\n");
    // END--------------------------------------

    // START------------------------------------
    set_DA_at(&chArr, "x", 2);
    print_DA_info(&chArr,"Set x at index 2 result.\n");
    // END--------------------------------------

    // START------------------------------------
    append_DA(&chArr, " ABCD", 5);
    print_DA_info(&chArr,"Append \" ABCD\" result.\n");
    // END--------------------------------------

    // START------------------------------------
    char content[255];
    sprintf(content,"Data at index 6 is: %c\n", *(char *)get_DA_ptr_at(&chArr, 6));
    print_DA_info(&chArr,content);
    // END--------------------------------------

    destroy_DA(&chArr);
}


void test_DA_int()
{
    int intTest[] = {1,2,3,4,5,6};
    DynamicArray intArr = create_DA(intTest, 6, sizeof *intTest, DA_DATA_INT);
    print_DA_info(&intArr,"Creation of dynamic array.\n");

    // START------------------------------------
    resize_DA(&intArr, 3);
    print_DA_info(&intArr,"Resize to 3 result.\n");
    // END------------------------------------

    // START------------------------------------
    int val = 4564;
    set_DA_at(&intArr, &val, 2);
    print_DA_info(&intArr,"Set 4564 at index 2 result.\n");
    // END--------------------------------------

    // START------------------------------------
    int values[] = {8,9};
    append_DA(&intArr, values, 2);
    print_DA_info(&intArr,"Append {8,9} result.\n");
    // END--------------------------------------

    destroy_DA(&intArr);
}


void test_List()
{
    List *list = create_list();

    // START------------------------------------
    char *val1 = "abc";
    int   val2 = 111;
    char *val3 = "some text";
    list_append(list, val1, strlenT(val1), "str");
    list_append(list, &val2, sizeof val2, "int");
    list_append(list, val3, strlenT(val3), "str");
    
    char buffor[255];
    sprintf(buffor,"Content of element index 0: %s\n", (char*)list_obj_ptr_at(list, 0));
    print_list_info(list, buffor);

    sprintf(buffor,"Content of element index 1: %d\n", *(int*)list_obj_ptr_at(list, 1));
    print_list_info(list, buffor);

    sprintf(buffor,"Content of element index 2: %s\n", (char*)list_obj_ptr_at(list, 2));
    print_list_info(list, buffor);
    // END--------------------------------------
    
    // START------------------------------------
    resize_list(list, 10);
    print_list_info(list, "Resize to 10 result.\n");
    // END--------------------------------------
    
    // START------------------------------------
    resize_list(list, 2);
    print_list_info(list, "Resize to 2 result.\n");
    // END--------------------------------------

    destroy_list(&list);
}


int main()
{
    // Uncomment any function you want to test
    //test_CA();        // Char array tests (String)
    //test_DA_char();   // Dynamic array tests (char)
    //test_DA_int();    // Dynamic array tests (int)
    test_List();      // List tests
    
    DEBUG("DONE");
    return 0;
}
