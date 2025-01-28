
// #ifndef TEST_COMMON_H
// #define TEST_COMMON_H

// #include <check.h>

// char *
// bin_to_hex(const char *input, int length);

// Suite *make_suite_test_fifo(void);
// Suite *make_suite_test_list(void);
// Suite *make_suite_test_parse(void);
// Suite *make_suite_test_string(void);
// Suite *make_suite_test_string_unicode(void);
// Suite *make_suite_test_os_calls(void);
// Suite *make_suite_test_ssl_calls(void);
// Suite *make_suite_test_base64(void);
// Suite *make_suite_test_guid(void);
// Suite *make_suite_test_scancode(void);

// TCase *make_tcase_test_os_calls_signals(void);

// void os_calls_signals_init(void);
// void os_calls_signals_deinit(void);

// #endif /* TEST_COMMON_H */

#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include "unity.h"

char *
bin_to_hex(const char *input, int length);

void test_fifo(void);
void test_list(void);
void test_parse(void);
void test_string(void);
void test_string_unicode(void);
void test_os_calls(void);
void test_ssl_calls(void);
void test_base64(void);
void test_guid(void);
void test_scancode(void);

// Setup and teardown functions for signal tests
void setUp(void);
void tearDown(void);

// Signal handling setup/cleanup
void os_calls_signals_init(void);
void os_calls_signals_deinit(void);

#endif /* TEST_COMMON_H */