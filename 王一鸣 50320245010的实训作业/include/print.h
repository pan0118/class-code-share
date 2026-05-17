#ifndef PRINT_H
#define PRINT_H
#include "types.h"

void print_string(const char *str);
void print_char(char c);
void printf(char *fmt, ...);
void panic(char *s);

#endif // PRINT_H