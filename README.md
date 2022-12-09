C Dynamic Array
=========

About
-----
Simple implementation of dynamic arrays in C

Building
--------
**Windows compilation:**
1) Compile using .bat file:
    - `winBuild.bat` builds the project using gcc

**Linux compilation:**
1) Compile using .sh file:
    - `linuxBuild.sh` builds the project using gcc

Example Use
-----------
Char array (String):
```
struct charArray arr = CharArray.createCA("");
CharArray.append_CA(&arr, "append this text");
```

Dynamic array (any data type, in example provided it is int):
```
int intTest[] = {1,2,3,4,5,6};
struct dynamicArray intArr = DynamicArray.createDA(intTest, 6, sizeof *intTest, DA_DATA_INT);

int values[] = {8,9};
DynamicArray.append_DA(&intArr, values, 2);
```
Example usage is also provided in master.c file.

For functions check .h files in src directory.