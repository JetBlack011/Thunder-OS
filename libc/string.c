#include "string.h"
#include "mem.h"

#include <stdint.h>

// K&R implementation
void itoa(int n, char s[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) s[i++] = '-';
    s[i] = '\0';

    reverse(s);
}

// K&R
int atoi(char s[])
{
    int i = 0, n = 0;
    for(i; s[i]>='0' && s[i]<='9'; i++)
        n = 10 * n + (s[i]-'0');
    return n;
}

void htoa(int n, char s[]) {
    strcat(s, '0');
    strcat(s, 'x');
    char zeros = 0;

    int32_t tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) strcat(s, tmp - 0xA + 'a');
        else strcat(s, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) strcat(s, tmp - 0xA + 'a');
    else strcat(s, tmp + '0');
}

// K&R
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

// K&R
int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void strcat(char s[], const char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

/* K&R
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2
 */
int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++)
        if (s1[i] == '\0')
            return 0;
    return s1[i] - s2[i];
}

char *strcpy(char *dest, const char *src)
{
    int i = 0;
    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char *strncpy(char *dest, const char *src, int n)
{
  char *tmp = dest;
  while (n-- && (*dest++ = *src++) != '\0');
  return tmp;
}

char **split(char *s, const char delim)
{
    int len = strlen(s);
    char **ret = kmalloc(len * sizeof(char*));
    ret[0] = kmalloc(len);
    int p = 0, j = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == delim) {
            ret[p][++j] = '\0';
            ret[++p] = kmalloc(len - i++);
            j = 0;
        }
        ret[p][j++] = s[i];
    }

    return ret;
}
/*
    arraylist_t *array;
    array_create(&array, strlen(s));
    char *begin = s;
    int size;

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == delim)
        {
            size = s + (i * sizeof(char)) - begin;
            array_add(array, (void*) kmalloc(size));
            strncpy(array->data[array->size], begin, size);
            begin = s + (i * sizeof(char)) + 1;
        }
    }

    size = strlen(s);
    array_add(array, (void*) kmalloc(size));
    strncpy(array->data[array->size], begin, size);

    return array;
*/

