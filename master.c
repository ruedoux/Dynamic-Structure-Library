#include "src/charArray.h"
#include "src/dynamicArray.h"

// Multiple functionalities of the char array being shown as example
void test_CA()
{
    struct charArray arr = CharArray.createCA("");
    CharArray.print_CA_info(&arr,"");

    // START------------------------------------
    printf("\nResize to 20 result:\n");

    CharArray.resize_CA(&arr, 20);
    CharArray.print_CA_info(&arr,"");
    // END--------------------------------------

    // START------------------------------------
    printf("\nAppend \"good-job-is-done\" result:\n");

    CharArray.append_CA(&arr, "good-job-is-done");
    CharArray.print_CA_info(&arr,"");
    // END--------------------------------------

    // START------------------------------------
    printf("\nFind \"job\" in array result:\n");

    int foundIndex = CharArray.find_CA_str(&arr, "job");
    char content[255];
    sprintf(content,"found = %s, on index: %d\n", "job", foundIndex);
    CharArray.print_CA_info(&arr,content);
    // END--------------------------------------

    // START------------------------------------
    printf("\nResize to 5 result:\n");

    CharArray.resize_CA(&arr, 5);
    CharArray.print_CA_info(&arr,"");
    // END--------------------------------------

    // START------------------------------------
    printf("\nAppend 1234567 result:\n");

    CharArray.append_CA(&arr, "1234567");
    CharArray.print_CA_info(&arr,"");
    // END--------------------------------------

    // START------------------------------------
    printf("\nPop back result:\n");

    char contentT[255];
    sprintf(contentT,"Popped letter %c\n", CharArray.pop_CA_back(&arr));
    CharArray.print_CA_info(&arr,contentT);
    // END--------------------------------------

    CharArray.destroyCA(&arr);
}


void test_DA()
{
    char chTest[] = "Test array of chars";
    struct dynamicArray chArr = DynamicArray.createDA(chTest, strlen(chTest), sizeof *chTest, DA_DATA_CHAR);
    DynamicArray.print_DA_info(&chArr,"");
    DynamicArray.destroyDA(&chArr);

    int intTest[] = {1,2,3,4};
    struct dynamicArray intArr = DynamicArray.createDA(intTest, 4, sizeof *intTest, DA_DATA_INT);
    DynamicArray.print_DA_info(&intArr,"");
    DynamicArray.destroyDA(&intArr);
}




int main()
{
    //test_CA();
    test_DA();
    return 0;
}
