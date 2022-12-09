#include "src/charArray.h"
#include "src/dynamicArray.h"


void test_CA()
{
    struct charArray arr = CharArray.createCA("");
    CharArray.print_CA_info(&arr,"Creation of char array (String).\n");

    // START------------------------------------
    CharArray.append_CA(&arr, "good-job-is-done");
    CharArray.print_CA_info(&arr,"Append \"good-job-is-done\" result.\n");
    // END--------------------------------------

    // START------------------------------------
    char content[255];
    sprintf(content,"found = %s, on index: %d\n", "job", CharArray.find_CA_str(&arr, "job"));
    CharArray.print_CA_info(&arr,content);
    // END--------------------------------------

    // START------------------------------------
    CharArray.resize_CA(&arr, 5);
    CharArray.print_CA_info(&arr,"Resize to 5 result.\n");
    // END--------------------------------------

    // START------------------------------------
    CharArray.append_CA(&arr, "1234567");
    CharArray.print_CA_info(&arr,"Append 1234567 result.\n");
    // END--------------------------------------

    // START------------------------------------
    char contentT[255];
    sprintf(contentT,"Popped letter %c\n", CharArray.pop_CA_back(&arr));
    CharArray.print_CA_info(&arr,contentT);
    // END--------------------------------------

    CharArray.destroyCA(&arr);

}


void test_DA_char()
{
    char chTest[] = "Test array of chars";
    struct dynamicArray chArr = DynamicArray.createDA(chTest, strlen(chTest), sizeof *chTest, DA_DATA_CHAR);
    DynamicArray.print_DA_info(&chArr,"Creating dynamic array.\n");

    // START------------------------------------
    DynamicArray.resize_DA(&chArr, 4);
    DynamicArray.print_DA_info(&chArr,"Resize to 4 result.\n");
    // END--------------------------------------

    // START------------------------------------
    DynamicArray.set_DA_at(&chArr, "x", 2);
    DynamicArray.print_DA_info(&chArr,"Set x at index 2 result.\n");
    // END--------------------------------------

    // START------------------------------------
    DynamicArray.append_DA(&chArr, " ABCD", 5);
    DynamicArray.print_DA_info(&chArr,"Append \" ABCD\" result.\n");
    // END--------------------------------------

    // START------------------------------------
    char content[255];
    sprintf(content,"Data at index 6 is: %c\n", *(char *)DynamicArray.get_DA_ptr_at(&chArr, 6));
    DynamicArray.print_DA_info(&chArr,content);
    // END--------------------------------------

    DynamicArray.destroyDA(&chArr);
}


void test_DA_int()
{
    int intTest[] = {1,2,3,4,5,6};
    struct dynamicArray intArr = DynamicArray.createDA(intTest, 6, sizeof *intTest, DA_DATA_INT);
    DynamicArray.print_DA_info(&intArr,"Creation of dynamic array.\n");

    // START------------------------------------
    DynamicArray.resize_DA(&intArr, 3);
    DynamicArray.print_DA_info(&intArr,"Resize to 3 result.\n");
    // END------------------------------------

    // START------------------------------------
    int val = 4564;
    DynamicArray.set_DA_at(&intArr, &val, 2);
    DynamicArray.print_DA_info(&intArr,"Set 4564 at index 2 result.\n");
    // END--------------------------------------

    // START------------------------------------
    int values[] = {8,9};
    DynamicArray.append_DA(&intArr, values, 2);
    DynamicArray.print_DA_info(&intArr,"Append {8,9} result.\n");
    // END--------------------------------------

    DynamicArray.destroyDA(&intArr);
}


int main()
{
    // Uncomment any function you want to test
    //test_CA();        // Char array tests (String)
    //test_DA_char();   // Dynamic array tests (char)
    //test_DA_int();    // Synamic array tests (int)
    return 0;
}
