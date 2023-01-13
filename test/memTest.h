/*
 * Unit Tests for the dynamic array implementations.
 * Mainly checking for any possible memory leaks.
*/

#pragma once
#ifndef MEMTEST_C
#define MEMTEST_C

// ---------------------------------------
// UNIT TEST LIBS
// ---------------------------------------

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#endif

#include "utility.h"

// ---------------------------------------
// TESTED LIBS
// ---------------------------------------

#include "../src/charArray.h"
#include "../src/dynamicArray.h"
#include "../src/List.h"

// ---------------------------------------
// MACROS
// ---------------------------------------

#define MB_SIZE 1048576

// ---------------------------------------
// FUNCTIONS
// ---------------------------------------

// Perform all unit tests
void UT_do_mem_tests();

// Test a given function in a loop
void UT_test_func_mem(void (*test_function)(size_t), char* testName, size_t repeats);

// Generates CharArray of given size and destroys it
void UT_test_CA_mem(size_t size);

// Generates DynamicArray of given size and destroys it
void UT_test_DA_mem(size_t size);

// Generates List of given size and destroys it
void UT_test_list_mem(size_t size);

#endif
