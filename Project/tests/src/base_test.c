#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "base_test.h"

char assert_equals_integer(int expected, int actual)
{
    char error = 0;
    if (expected != actual)
    {
        error++;
        printf("Unable to assert that %d equals %d\n", expected, actual);
        int j, nptrs;
        void *buffer[SIZE];
        char **strings;

        nptrs = backtrace(buffer, SIZE);
        printf("backtrace() returned %d addresses\n", nptrs);

        strings = backtrace_symbols(buffer, nptrs);
        if (strings == NULL)
        {
            perror("backtrace_symbols");
            exit(EXIT_FAILURE);
        }

        for (j = 0; j < nptrs; j++)
        {
            printf("%s\n", strings[j]);
        }

        free(strings);
    }

    return error;
}


char assert_not_equals_integer(int expected, int actual)
{
    char error = 0;
    if (expected == actual)
    {
        error++;
        printf("Unable to assert that %d equals %d\n", expected, actual);
        int j, nptrs;
        void *buffer[SIZE];
        char **strings;

        nptrs = backtrace(buffer, SIZE);
        printf("backtrace() returned %d addresses\n", nptrs);

        strings = backtrace_symbols(buffer, nptrs);
        if (strings == NULL)
        {
            perror("backtrace_symbols");
            exit(EXIT_FAILURE);
        }

        for (j = 0; j < nptrs; j++)
        {
            printf("%s\n", strings[j]);
        }

        free(strings);
    }

    return error;
}


char assert_equals_string(char *expected, char *actual)
{
    char error = 0;
    if (strcmp(expected, actual) != 0)
    {
        error++;
        printf("Unable to assert that '%s' equals '%s'\n", expected, actual);
        int j, nptrs;
        void *buffer[SIZE];
        char **strings;

        nptrs = backtrace(buffer, SIZE);
        printf("backtrace() returned %d addresses\n", nptrs);

        strings = backtrace_symbols(buffer, nptrs);
        if (strings == NULL)
        {
            perror("backtrace_symbols");
            exit(EXIT_FAILURE);
        }

        for (j = 0; j < nptrs; j++)
        {
            printf("%s\n", strings[j]);
        }

        free(strings);
    }

    return error;
}
