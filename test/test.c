#include "test.h"


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


void test_function(void (*test_function)(size_t), char* testName, size_t repeats)
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


void test_CA_mem(size_t size)
{
    CharArray *arr = create_CA("test");
    resize_CA(arr, size);

    // Random operations on array
    for (unsigned i=0; i<100; i++)
    {
        char *randArr = alloc_random_charArr(10);
        append_CA(arr, randArr);
        free(randArr);
        pop_CA_back(arr);
    } //

    destroy_CA(&arr);
}


void test_DA_mem(size_t size)
{
    char *charTest = "abcde";
    DynamicArray *arr = create_DA(charTest, strlen(charTest), sizeof *charTest, DA_DATA_CHAR);
    resize_DA(arr, size);

    // Random operations on array
    for (unsigned i=0; i<100; i++)
    {
        char *randArr = alloc_random_charArr(10);
        append_DA(arr, randArr, strlen(randArr));
        free(randArr);
    } //

    destroy_DA(&arr);
}


void test_list_mem(size_t size)
{
    List *list = create_list();
    resize_list(list, size);

    // Random operations on list
    for (unsigned i=0; i<100; i++)
    {
        char *randArr = alloc_random_charArr(10);
        list_append(list, randArr, strlenT(randArr), randArr);
        free(randArr);
    } //

    destroy_list(&list);
}


void do_mem_tests()
{
    printf("\n"); DEBUG_MSG("STARTING UNIT TESTS");
    test_function(&test_CA_mem, "CharArray", rand()%1000);
    test_function(&test_DA_mem, "DynamicArray (int)", rand()%1000);
    test_function(&test_list_mem, "List", rand()%1000);
    DEBUG_MSG("ENDING UNIT TESTS\n\n");
}
