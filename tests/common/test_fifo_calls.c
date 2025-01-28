// #if defined(HAVE_CONFIG_H)
// #include "config_ac.h"
// #endif

// #include "fifo.h"

// #include "os_calls.h"
// #include "test_common.h"
// #include "string_calls.h"

// static const char *strings[] =
// {
//     "one",
//     "two",
//     "three",
//     "four",
//     "five",
//     "six",
//     "seven",
//     "eight",
//     "nine",
//     "ten",
//     "eleven",
//     "twelve",
//     NULL
// };

// #define LARGE_TEST_SIZE 10000

// /******************************************************************************/
// /* Item destructor function for fifo tests involving allocated strings */
// static void
// string_item_destructor(void *item, void *closure)
// {
//     free(item);

//     if (closure != NULL)
//     {
//         /* Count the free operation */
//         int *c = (int *)closure;
//         ++(*c);
//     }
// }
// /******************************************************************************/

// START_TEST(test_fifo__null)
// {
//     struct fifo *f = NULL;
//     void *vp;
//     int status;

//     // These calls should not crash!
//     fifo_delete(f, NULL);
//     fifo_clear(f, NULL);

//     status = fifo_add_item(f, NULL);
//     ck_assert_int_eq(status, 0);

//     vp = fifo_remove_item(f);
//     ck_assert_ptr_eq(vp, NULL);

//     status = fifo_is_empty(f);
//     ck_assert_int_eq(status, 1);
// }

// END_TEST

// START_TEST(test_fifo__simple)
// {
//     struct fifo *f = fifo_create(NULL);
//     ck_assert_ptr_ne(f, NULL);

//     int empty = fifo_is_empty(f);
//     ck_assert_int_eq(empty, 1);

//     // Check we can't add NULL to the fifo
//     int success = fifo_add_item(f, NULL);
//     ck_assert_int_eq(success, 0);

//     // Check we can't remove anything from an empty fifo
//     void *vp = fifo_remove_item(f);
//     ck_assert_ptr_eq(vp, NULL);

//     // Add some static strings to the FIFO
//     const char **s;
//     unsigned int n = 0;
//     for (s = &strings[0] ; *s != NULL; ++s)
//     {
//         fifo_add_item(f, (void *)*s);
//         ++n;
//     }

//     empty = fifo_is_empty(f);
//     ck_assert_int_eq(empty, 0);

//     unsigned int i;
//     for (i = 0 ; i < n ; ++i)
//     {
//         const char *p = (const char *)fifo_remove_item(f);
//         ck_assert_ptr_eq(p, strings[i]);
//     }

//     empty = fifo_is_empty(f);
//     ck_assert_int_eq(empty, 1);

//     fifo_delete(f, NULL);
// }
// END_TEST


// START_TEST(test_fifo__strdup)
// {
//     struct fifo *f = fifo_create(string_item_destructor);
//     ck_assert_ptr_ne(f, NULL);

//     // Add some dynamically allocated strings to the FIFO
//     const char **s;
//     unsigned int n = 0;
//     for (s = &strings[0] ; *s != NULL; ++s)
//     {
//         int ok = fifo_add_item(f, (void *)strdup(*s));
//         ck_assert_int_eq(ok, 1);
//         ++n;
//     }

//     // Delete the fifo, freeing the allocated strings. Check free() is called
//     // the expected number of times.
//     int c = 0;
//     fifo_delete(f, &c);
//     ck_assert_int_eq(c, n);
// }
// END_TEST

// START_TEST(test_fifo__large_test_1)
// {
//     struct fifo *f = fifo_create(string_item_destructor);
//     ck_assert_ptr_ne(f, NULL);

//     // Fill the fifo with dynamically allocated strings
//     int i;
//     for (i = 0; i < LARGE_TEST_SIZE; ++i)
//     {
//         int ok = fifo_add_item(f, (void *)strdup("test item"));
//         ck_assert_int_eq(ok, 1);
//     }

//     // Clear the fifo, checking free is called the expected number of times
//     int c = 0;
//     fifo_clear(f, &c);
//     ck_assert_int_eq(c, LARGE_TEST_SIZE);

//     int empty = fifo_is_empty(f);
//     ck_assert_int_eq(empty, 1);

//     // Finally delete the fifo, checking free is not called this time
//     c = 0;
//     fifo_delete(f, &c);
//     ck_assert_int_eq(c, 0);
// }
// END_TEST

// START_TEST(test_fifo__large_test_2)
// {
//     char buff[64];

//     struct fifo *f = fifo_create(string_item_destructor);
//     ck_assert_ptr_ne(f, NULL);

//     // Fill the fifo with dynamically allocated strings
//     int i;
//     for (i = 0; i < LARGE_TEST_SIZE; ++i)
//     {
//         g_snprintf(buff, sizeof(buff), "%d", i);
//         int ok = fifo_add_item(f, (void *)strdup(buff));
//         ck_assert_int_eq(ok, 1);
//     }

//     // Extract all the strings from the fifo, making sure they're
//     // as expected
//     for (i = 0; i < LARGE_TEST_SIZE; ++i)
//     {
//         g_snprintf(buff, sizeof(buff), "%d", i);
//         char *s = fifo_remove_item(f);
//         ck_assert_ptr_ne(s, NULL);
//         ck_assert_str_eq(s, buff);
//         free(s);
//     }

//     int empty = fifo_is_empty(f);
//     ck_assert_int_eq(empty, 1);

//     int c = 0;
//     fifo_delete(f, &c);
//     ck_assert_int_eq(c, 0);
// }
// END_TEST

// /******************************************************************************/
// Suite *
// make_suite_test_fifo(void)
// {
//     Suite *s;
//     TCase *tc_simple;

//     s = suite_create("Fifo");

//     tc_simple = tcase_create("simple");
//     suite_add_tcase(s, tc_simple);
//     tcase_add_test(tc_simple, test_fifo__null);
//     tcase_add_test(tc_simple, test_fifo__simple);
//     tcase_add_test(tc_simple, test_fifo__strdup);
//     tcase_add_test(tc_simple, test_fifo__large_test_1);
//     tcase_add_test(tc_simple, test_fifo__large_test_2);

//     return s;
// }

#if defined(HAVE_CONFIG_H)
#include "config_ac.h"
#endif

#include "fifo.h"
#include "os_calls.h"
#include "test_common.h"
#include "string_calls.h"
#include "unity.h"
#include "xrdp_types.h"

static const char *strings[] =
{
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten",
    "eleven",
    "twelve",
    NULL
};

#define LARGE_TEST_SIZE 10000

/* Item destructor function for fifo tests involving allocated strings */
static void
string_item_destructor(void *item, void *closure)
{
    free(item);

    if (closure != NULL)
    {
        /* Count the free operation */
        int *c = (int *)closure;
        ++(*c);
    }
}

void setUp(void)
{
    // Unity setup - called before each test
}

void tearDown(void)
{
    // Unity teardown - called after each test
}

void test_fifo__null(void)
{
    struct fifo *f = NULL;
    void *vp;
    int status;

    // These calls should not crash!
    fifo_delete(f, NULL);
    fifo_clear(f, NULL);

    status = fifo_add_item(f, NULL);
    TEST_ASSERT_EQUAL_INT(0, status);

    vp = fifo_remove_item(f);
    TEST_ASSERT_NULL(vp);

    status = fifo_is_empty(f);
    TEST_ASSERT_EQUAL_INT(1, status);
}

void test_fifo__simple(void)
{
    struct fifo *f = fifo_create(NULL);
    TEST_ASSERT_NOT_NULL(f);

    int empty = fifo_is_empty(f);
    TEST_ASSERT_EQUAL_INT(1, empty);

    // Check we can't add NULL to the fifo
    int success = fifo_add_item(f, NULL);
    TEST_ASSERT_EQUAL_INT(0, success);

    // Check we can't remove anything from an empty fifo
    void *vp = fifo_remove_item(f);
    TEST_ASSERT_NULL(vp);

    // Add some static strings to the FIFO
    const char **s;
    unsigned int n = 0;
    for (s = &strings[0]; *s != NULL; ++s)
    {
        fifo_add_item(f, (void *)*s);
        ++n;
    }

    empty = fifo_is_empty(f);
    TEST_ASSERT_EQUAL_INT(0, empty);

    unsigned int i;
    for (i = 0; i < n; ++i)
    {
        const char *p = (const char *)fifo_remove_item(f);
        TEST_ASSERT_EQUAL_STRING(strings[i], p);
    }

    empty = fifo_is_empty(f);
    TEST_ASSERT_EQUAL_INT(1, empty);

    fifo_delete(f, NULL);
}

void test_fifo__strdup(void)
{
    struct fifo *f = fifo_create(string_item_destructor);
    TEST_ASSERT_NOT_NULL(f);

    // Add some dynamically allocated strings to the FIFO
    const char **s;
    unsigned int n = 0;
    for (s = &strings[0]; *s != NULL; ++s)
    {
        int ok = fifo_add_item(f, (void *)strdup(*s));
        TEST_ASSERT_EQUAL_INT(1, ok);
        ++n;
    }

    // Delete the fifo, freeing the allocated strings. Check free() is called
    // the expected number of times.
    int c = 0;
    fifo_delete(f, &c);
    TEST_ASSERT_EQUAL_INT(n, c);
}

void test_fifo__large_test_1(void)
{
    struct fifo *f = fifo_create(string_item_destructor);
    TEST_ASSERT_NOT_NULL(f);

    // Fill the fifo with dynamically allocated strings
    int i;
    for (i = 0; i < LARGE_TEST_SIZE; ++i)
    {
        int ok = fifo_add_item(f, (void *)strdup("test item"));
        TEST_ASSERT_EQUAL_INT(1, ok);
    }

    // Clear the fifo, checking free is called the expected number of times
    int c = 0;
    fifo_clear(f, &c);
    TEST_ASSERT_EQUAL_INT(LARGE_TEST_SIZE, c);

    int empty = fifo_is_empty(f);
    TEST_ASSERT_EQUAL_INT(1, empty);

    // Finally delete the fifo, checking free is not called this time
    c = 0;
    fifo_delete(f, &c);
    TEST_ASSERT_EQUAL_INT(0, c);
}

void test_fifo__large_test_2(void)
{
    char buff[64];

    struct fifo *f = fifo_create(string_item_destructor);
    TEST_ASSERT_NOT_NULL(f);

    // Fill the fifo with dynamically allocated strings
    int i;
    for (i = 0; i < LARGE_TEST_SIZE; ++i)
    {
        g_snprintf(buff, sizeof(buff), "%d", i);
        int ok = fifo_add_item(f, (void *)strdup(buff));
        TEST_ASSERT_EQUAL_INT(1, ok);
    }

    // Extract all the strings from the fifo, making sure they're
    // as expected
    for (i = 0; i < LARGE_TEST_SIZE; ++i)
    {
        g_snprintf(buff, sizeof(buff), "%d", i);
        char *s = fifo_remove_item(f);
        TEST_ASSERT_NOT_NULL(s);
        TEST_ASSERT_EQUAL_STRING(buff, s);
        free(s);
    }

    int empty = fifo_is_empty(f);
    TEST_ASSERT_EQUAL_INT(1, empty);

    int c = 0;
    fifo_delete(f, &c);
    TEST_ASSERT_EQUAL_INT(0, c);
}

START_TEST(test_get_key_info_from_kbd_event__numlock_min_boundary)
{
    struct xrdp_keymap keymap;
    int keys[256] = {0};
    struct xrdp_key_info *key_info;

    /* Initialize test keymap */
    memset(&keymap, 0, sizeof(struct xrdp_keymap));
    keymap.caps_lock_supported = 1;

    /* Set up a known value in numlock array at minimum index */
    keymap.keys_numlock[0].sym = 12345;
    keymap.keys_numlock[0].chr = 67890;

    /* Test with numlock on at minimum boundary */
    key_info = get_key_info_from_kbd_event(0, 
                                          SCANCODE_MIN_NUMLOCK, 
                                          keys,
                                          0,  /* caps lock off */
                                          1,  /* num lock on */
                                          0,  /* scroll lock off */
                                          &keymap);

    ck_assert_ptr_ne(key_info, NULL);
    ck_assert_int_eq(key_info->sym, 12345);
    ck_assert_int_eq(key_info->chr, 67890);
}