#pragma once
#ifndef ARRTEST_C
#define ARRTEST_C

// ---------------------------------------
// UNIT TEST LIBS
// ---------------------------------------

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#endif

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

void do_mem_tests();

void test_function(void (*test_function)(size_t), char* testName, size_t repeats);

void test_CA_mem(size_t size);

void test_DA_mem(size_t size);

void test_list_mem(size_t size);
#endif
