#ifndef _STRINGS_H
#define _STRINGS_H

#include <stdarg.h>
#include "types.h"

#define EQUAL_STRINGS 1
#define DIFFERENT_STRINGS 0


void rpi_itoa(int number, char *buffer);
char *itoh(unsigned int number, char *string);
uint32_t number_of_digits(int a);
void _sprintf(char *destination, const char *string, va_list arguments);
void rpi_sprintf(char *destination, const char *string, ...);
unsigned int rpi_strlen(char *string);
void rpi_strcpy(char *origin, char *destination, int length);
void concatenate_string(char *string1, char string1_length, char *string2, char string2_length, char *result);
int rpi_strcmp(char* str1, char* str2);
char* rpi_trim(char *str, char *ret);
void get_first_word(char* str, char* ret);
#endif
