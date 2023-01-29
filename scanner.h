#pragma once
#include <stdio.h>
int has_next(FILE*);
char *next(FILE*);
int next_int(FILE*);
int next_double(FILE*);
char *next_line(FILE*);