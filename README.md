C Dynamic Array
=========

About
-----
Simple implementation of dynamic arrays in C

Example Use
-----------
Char array (String):
```
CharArray arr = createCA("");
append_CA(&arr, "append this text");
```

Dynamic array (any data type, in example provided it is int):
```
int intTest[] = {1,2,3,4,5,6};
DynamicArray intArr = createDA(intTest, 6, sizeof *intTest, DA_DATA_INT);

int values[] = {8,9};
append_DA(&intArr, values, 2);
```
Example usage is also provided in master.c file.

For functions check .h files in src directory.