#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <char_array_list.h>
#include "scanner.h"
char *next(FILE *file)
{
    while (1) {
        char input = fgetc(file);
        if (!isspace(input)) {
            if (input != EOF) {
                ungetc(input, file);
            }
            break;
        }
    }
    struct char_array_list *list = char_array_list_init();
    while (1) {
        char input = fgetc(file);
        if (isspace(input) || input == EOF) {
            break;
        }
        char_array_list_add(list, input);
    }
    char_array_list_add(list, '\0');
    char *ret = char_array_list_to_array(list);
    char_array_list_free(list);
    while (1) {
        char input = fgetc(file);
        if (!isspace(input) || input == EOF) {
            if (input != EOF) {
                ungetc(input, file);
            }
            break;
        }
    }
    return ret;
}
int next_int(FILE *file)
{
    char *before = next(file);
    char *rest;
    errno = 0;
    long after = strtol(before, &rest, 10);
    if (strcmp(rest, "")) {
        fprintf(stderr, "%sの%d行目：入力「%s」を整数に変換できませんでした。\n", __FILE__, __LINE__, before);
        exit(1);
    }
    if (errno == ERANGE || after < INT_MIN || after > INT_MAX) {
        errno = ERANGE;
        return 0;
    }
    return after;
}
int next_double(FILE *file)
{
    char *before = next(file);
    char *rest;
    errno = 0;
    double after = strtod(before, &rest);
    if (!strcmp(rest, "")) {
        fprintf(stderr, "%sの%d行目：入力「%s」を小数に変換できませんでした。\n", __FILE__, __LINE__, before);
        exit(1);
    }
    if (errno == ERANGE) {
        return 0;
    }
    return after;
}
char *next_line(FILE *file)
{
    struct char_array_list *list = char_array_list_init();
    while (1) {
        char input = fgetc(file);
        if (input == '\n' || input == EOF) {
            break;
        }
        char_array_list_add(list, input);
    }
    char_array_list_add(list, '\0');
    char *ret = char_array_list_to_array(list);
    char_array_list_free(list);
    return ret;
}