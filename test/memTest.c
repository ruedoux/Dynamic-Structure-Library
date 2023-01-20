#include "memTest.h"

#ifdef _WIN32
size_t get_ram_usage()
{
    PROCESS_MEMORY_COUNTERS pmc;
    if ( !GetProcessMemoryInfo(GetCurrentProcess(),&pmc,sizeof(pmc)) ) { return 0; }
    return pmc.WorkingSetSize;
}
#endif


#ifdef linux
size_t get_ram_usage()
{
    return 0;
}
#endif


void UT_test_func_mem(void (*test_function)(size_t), char* testName, size_t repeats)
{
    const size_t ALLOCATE_SIZE = MB_SIZE; // Memory to allocate in a loop
    size_t prevValue = get_ram_usage();

    printf("---------------------------------\n");
    printf("Ram usage test for %s, loops: "TYPE_SIZE_T"\n\n", testName, repeats);
    printf("Starting size: "TYPE_SIZE_T" MB, "TYPE_SIZE_T" BYTES\n", prevValue/MB_SIZE, prevValue);

    for (unsigned i=0;i<repeats;i++)
    {
        test_function(ALLOCATE_SIZE);

        size_t ramUsage = get_ram_usage();
        if (prevValue < ramUsage)
        {
            size_t difference = ramUsage-prevValue;
            printf("\tSize increase detected from previous loop: "TYPE_SIZE_T" MB, "TYPE_SIZE_T" BYTES\n", difference/MB_SIZE, difference);
        }
        prevValue = ramUsage;
    }
    printf("Ending size: "TYPE_SIZE_T" MB, "TYPE_SIZE_T" BYTES\n", prevValue/MB_SIZE, prevValue);
    printf("---------------------------------\n");
}


void UT_test_CA_mem(size_t size)
{
    DSL_String *arr = str_create("test");
    str_resize(arr, size);

    // Random operations on array
    for (unsigned i=0; i<100; i++)
    {
        char *randArr = alloc_random_charArr(10);
        str_append(arr, randArr);
        free(randArr);
        str_pop_back(arr);
    } //

    str_destroy(&arr);
}


void UT_test_DA_mem(size_t size)
{
    char *charTest = "abcde";
    DynamicArray *arr = da_create(charTest, strlen(charTest), sizeof *charTest, DA_DATA_I8);
    da_resize(arr, size);

    // Random operations on array
    for (unsigned i=0; i<100; i++)
    {
        char *randArr = alloc_random_charArr(10);
        da_append(arr, randArr, strlen(randArr));
        free(randArr);
    } //

    da_destroy(&arr);
}


void UT_test_list_mem(size_t size)
{
    DSL_List *list = list_create();
    list_resize(list, size);

    // Random operations on list
    for (unsigned i=0; i<100; i++)
    {
        char *randArr = alloc_random_charArr(10);
        list_append(list, randArr, strlenT(randArr), randArr);
        free(randArr);
    } //

    list_destroy(&list);
}


void UT_do_mem_tests()
{
    printf("\n"); DEBUG_MSG("STARTING MEMORY TESTS");
    UT_test_func_mem(&UT_test_CA_mem, "DSL_String", rand()%1000);
    UT_test_func_mem(&UT_test_DA_mem, "DynamicArray (i32)", rand()%1000);
    UT_test_func_mem(&UT_test_list_mem, "DSL_List", rand()%1000);
    DEBUG_MSG("ENDING MEMORY TESTS\n\n");
}