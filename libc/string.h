#ifndef STRINGS_H
#define STRINGS_H

#include "types/arraylist.h"

void itoa(int n, char s[]);
int atoi(char s[]);
void htoa(int n, char s[]);
void reverse(char s[]);
int strlen(char s[]);
void backspace(char s[]);
void strcat(char s[], char n);
int strcmp(char s1[], char s2[]);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, int n);
char **split(char *src, const char delim);

#endif
