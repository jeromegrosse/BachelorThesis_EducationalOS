#include "base_test.h"
#include "strings.h"
#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>


void itoa_tests(void)
{
    unsigned int error = 0;

    // 1. Positive
    char buffer_positive[20];
    rpi_itoa(1234, &buffer_positive[0]);

    error += assert_equals_integer('1', buffer_positive[0]);
    error += assert_equals_integer('2', buffer_positive[1]);
    error += assert_equals_integer('3', buffer_positive[2]);
    error += assert_equals_integer('4', buffer_positive[3]);


    // 2. Negative
    char buffer_negative[20];
    rpi_itoa(-1234, &buffer_negative[0]);

    error += assert_equals_integer('-', buffer_negative[0]);
    error += assert_equals_integer('1', buffer_negative[1]);
    error += assert_equals_integer('2', buffer_negative[2]);
    error += assert_equals_integer('3', buffer_negative[3]);
    error += assert_equals_integer('4', buffer_negative[4]);


    // 3. Zero
    char buffer_zero[20];
    rpi_itoa(0, &buffer_zero[0]);

    error += assert_equals_integer('0', buffer_zero[0]);

    printf("itoa_tests executed with %u errors.\n", error);
}


void rpi_strlen_tests(void)
{
    unsigned int error = 0;

    // Zero length
    char *string0 = "";
    error += assert_equals_integer(1, rpi_strlen(string0));

    // Positive length
    char *string1 = "This string has 31 characters.";
    error += assert_equals_integer(31, rpi_strlen(string1));

    printf("rpi_strlen_tests executed with %u errors.\n", error);
}


void itoh_test(void)
{
    unsigned int error = 0;
    char string[11];

    // First test
    itoh(0, &string[0]);
    error += assert_equals_string("0x00000000", string);

    itoh(10, &string[0]);
    error += assert_equals_string("0x0000000A", string);

    itoh(17, &string[0]);
    error += assert_equals_string("0x00000011", string);

    printf("itoh_test executed with %u errors.\n", error);
}


void rpi_sprintf_test(void)
{
    unsigned int error = 0;

    char buffer[1024];

    // Regular string
    char* string1 = "First test.";
    rpi_sprintf(&buffer[0], "First test.");
    error += assert_equals_string(string1, &buffer[0]);

    // String
    char* string2 = "Second test.";
    rpi_sprintf(&buffer[0], "%s", string2);
    error += assert_equals_string(string2, &buffer[0]);

    // Integer
    rpi_sprintf(&buffer[0], "Test numerals %d, %d and %d.", 1, 2, -3);
    error += assert_equals_string("Test numerals 1, 2 and -3.", buffer);

    // Hexadecimal
    rpi_sprintf(&buffer[0], "Test hexadecimal %x.", 17);
    error += assert_equals_string("Test hexadecimal 0x00000011.", buffer);

    printf("rpi_sprintf_test executed with %u errors.\n", error);
}

void rpi_strcpy_test()
{
    unsigned int error = 0;
    char* string1 = "Copy this string";
    char* string2 = "";
    char* string3 = "I want only the word HERE in the copy";
    char string1_copy[50];
    char string2_copy[50];
    char string3_copy[50];
    rpi_memset(string3_copy, '\0', 50);

    rpi_strcpy(string1, string1_copy, rpi_strlen(string1));
    rpi_strcpy(string2, string2_copy, rpi_strlen(string2));
    rpi_strcpy(string3+21, string3_copy, 4);

    error += assert_equals_string(string1, string1_copy);
    error += assert_equals_string(string2, string2_copy);
    error += assert_equals_string("HERE", string3_copy);

    printf("rpi_strcpy_test executed with %u errors.\n", error);
}


void rpi_strcmp_test()
{
    unsigned int error = 0;

    error += assert_equals_integer(EQUAL_STRINGS, rpi_strcmp("", ""));
    error += assert_equals_integer(EQUAL_STRINGS, rpi_strcmp("abcde", "abcde"));
    error += assert_equals_integer(DIFFERENT_STRINGS, rpi_strcmp("abcde", "a"));
    error += assert_equals_integer(DIFFERENT_STRINGS, rpi_strcmp("abcde", ""));

    printf("rpi_strcmp_test executed with %u errors.\n", error);
}


void rpi_trim_test()
{
    unsigned int error = 0;
    char* buffer = (char*) malloc(255*sizeof(char));

    // First test
    rpi_trim("Hello there", buffer);
    error += assert_equals_string("Hello there", buffer);

    // Second test
    rpi_trim("    Hello there      ", buffer);
    error += assert_equals_string("Hello there", buffer);

    free(buffer);

    printf("rpi_trim_test executed with %u errors.\n", error);
}


void get_first_word_test() {
    unsigned int error = 0;
    char *heap = (char *)malloc(1024);
    char *buffer = (char *)malloc(1024);
    memory_init(heap, 1024);

    //char* get_first_word(char* str);
    get_first_word("This is a test", buffer);
    assert_equals_string("This", buffer);

    get_first_word("   This is a test", buffer);
    assert_equals_string("This", buffer);

    get_first_word("", buffer);
    assert_equals_string("", buffer);

    free(buffer);
    free(heap);

    printf("get_first_word_test executed with %u errors.\n", error);
}



int main()
{
    printf("\n\n *** STRINGS TEST ***\n");

    itoh_test();
    itoa_tests();
    rpi_strlen_tests();
    rpi_sprintf_test();
    rpi_strcpy_test();
    rpi_strcmp_test();
    rpi_trim_test();
    get_first_word_test();
}
