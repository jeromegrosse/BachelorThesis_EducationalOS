#include "strings.h"
#include "constants.h"
#include "malloc.h"
#include <stdio.h>

uint32_t number_of_digits(int a)
{
    int i = 0;
    while (a != 0)
    {
        i++;
        a /= 10;
    }

    return i;
}

/**
*   Integer to string
*/
void rpi_itoa(int number, char *buffer)
{
    if (number == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    char negative = 0;
    if (number < 0)
    {
        negative = 1;
        number = -number;
        buffer++;
    }

    int number2 = number;
    while (number2 != 0)
    {
        buffer++;
        number2 /= 10;
    }

    *buffer = '\0';

    while (number != 0)
    {
        *--buffer = '0' + (number % 10);
        number   /= 10;
    }

    if (negative)
    {
        *--buffer = '-';
    }
}


char *itoh(unsigned int number, char *string)
{
    string[0] = '0';
    string[1] = 'x';

    string[10] = '\0';
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        char c;
        if (number != 0)
        {
            int r = number % 16;
            c = r < 10 ? '0' + r : 'A' + r - 10;
        }
        else { c = '0'; }

        string[7 - i + 2] = c;
        number /= 16;
    }

    return string;
}


void _sprintf(char *destination, const char *string, va_list arguments)
{
    int is_percent = 0;
    char c;
    int temp;
    char int_temp[12];

    while ((c = *string) != '\0') {
        if ( c == '%') {
            if (is_percent == 1) {
                is_percent = 0;
                *destination++ = '%';
            } else is_percent = 1;
        } else {
            if (!is_percent) *destination++ = c;
            else {
                is_percent = 0;

                char *to_append = NULL;

                switch(c) {
                    case 'd':
                    case 'x':
                        temp = va_arg(arguments, int);
                        c == 'd' ? rpi_itoa(temp, &int_temp[0]) : itoh(temp, &int_temp[0]);
                        to_append = &int_temp[0];
                    break;

                    case 's':
                        to_append = va_arg(arguments, char *);
                        break;
                }

                if (to_append != NULL) {
                    while (*to_append != '\0') *destination++ = *to_append++;
                }

            }

        }

        string++;
    }

    destination = 0; // '\0'
}


void rpi_sprintf(char *destination, const char *string, ...)
{
    va_list arguments;
    va_start(arguments, string);

    _sprintf(destination, string, arguments);

    va_end(arguments);
}


unsigned int rpi_strlen(char *string)
{
    int count = 0;
    while (string[count] != '\0') count++;
    count++; // We count the '\0' character

    return count;
}


void rpi_strcpy(char *origin, char *destination, int length)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        destination[i] = origin[i];
    }
}


void concatenate_string(char *string1, char string1_length, char *string2, char string2_length, char *result)
{
    rpi_strcpy(string1, result, string1_length);
    rpi_strcpy(string2, result + string1_length, string2_length);
}


int rpi_strcmp(char* str1, char* str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i]) return DIFFERENT_STRINGS;
        i++;
    }

    if (str1[i] != str2[i]) return DIFFERENT_STRINGS;
    return EQUAL_STRINGS;
}


char* rpi_trim(char *str, char *ret)
{
    unsigned int length_str = rpi_strlen(str) - 1; //We don't want the count the '\0' character
    int start = 0;
    ret[0] = '\0';

    // Delete leading spaces
    while(str[start] == ' ') start++;

    if (str[start] != '\0') {
        // To find the trailing spaces, we need to go backward from the end of the string
        int end = length_str;

        while((str[end] == ' ' || str[end] == '\0') && end > 0) {
            end--;
        }

        //We now have the start and end of the string, we just perform a strcpy
        rpi_strcpy(str + start, ret, end - start + 1);
        ret[end - start + 1] = '\0';
    }

    return ret;
}


void get_first_word(char* str, char* ret)
{
    int buffer_size = rpi_strlen(str);
    char *str_trim = (char *)memory_alloc(buffer_size*sizeof(char));
    rpi_trim(str, str_trim);
    rpi_memset(ret, '\0', rpi_strlen(ret));

    int counter = 0;
    char c;
    while(counter < buffer_size && (c = str_trim[counter]) != ' ' && c != '\0') {
        ret[counter] = c;
        counter++;
    }

    memory_free(str_trim);
}
