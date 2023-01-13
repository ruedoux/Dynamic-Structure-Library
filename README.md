DSL - Dynamic Structure Library
=========

About
-----
Simple implementation of dynamic structures in C

Example Use
-----------
Char array (String):
```
DSL_String *arr = str_create("");         // Create array struct (allocate memory)
str_append(arr, "append this text");     // Append text to array
str_resize(arr, 5);                      // Resize the array to size 5
str_destroy(&arr);                       // Destroy array struct (free memory)
```

Dynamic array (any data type, in example provided it is int):
```
int intTest[] = {1,2,3,4,5,6};
int appendValues[] = {8,9};

// Create dynamic array from above fixed size array (allocate memory)
DynamicArray *intArr = da_create(intTest, 6, sizeof *intTest, DA_DATA_INT);

// Append values to dynamic array
da_append(intArr, appendValues, 2);

// Destroy array struct (free memory)
da_destroy(&intArr);
```

Dynamic list (similar to python list):
```
char *val1 = "abc";
int   val2 = 111;
char *val3 = "some text";

// Create dynamic list (allocate memory)
DSL_List *list = list_create();

// Append above variables as elements in list
list_append(list, val1, strlenT(val1), "str");
list_append(list, &val2, sizeof val2, "int");
list_append(list, val3, strlenT(val3), "str");

// Destroy list struct (free memory)
list_destroy(&list);
```

Example usage is also provided in main.c file.

For functions and documentation check .h files in src directory.

Unit tests
-----------
Some tests are provided in test directory, mainly checking for any memory leaks in implementation.