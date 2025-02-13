#include "libc.h"

void *memset(void *dst, char val, size_t cnt) {
    char *cdst = dst;
    size_t i;
    for (i = 0; i < cnt; i++) {
        cdst[i] = val;
    }
    return dst;
}

void *memcpy(void *dst, const void *src, size_t n) {
    const char *s;
    char *d;

    if (n == 0)
        return dst;

    s = src;
    d = dst;
    if (s < d && s + n > d) {
        s += n;
        d += n;
        while (n-- > 0)
            *--d = *--s;
    } else
        while (n-- > 0)
            *d++ = *s++;

    return dst;
}

int memcmp(const void *v1, const void *v2, size_t cnt) {
    const char *s1, *s2;
    s1 = v1;
    s2 = v2;
    while (cnt-- > 0) {
        if (*s1 != *s2)
            return *s1 - *s2;
        s1++, s2++;
    }

    return 0;
}

int strncmp(const char *p, const char *q, size_t n) {
    while (n > 0 && *p && *p == *q)
        n--, p++, q++;
    if (n == 0)
        return 0;
    return (char) *p - (char) *q;
}

char *strncpy(char *s, const char *t, int n) {
    char *os = s;
    while (n-- > 0 && (*s++ = *t++) != 0);
    while (n-- > 0)
        *s++ = 0;
    return os;
}

int strlen(const char *s) {
    int n;
    for (n = 0; s[n]; n++);
    return n;
}

int atoi(const char *s) {
    int n = 0;
    while ('0' <= *s && *s <= '9')
        n = n * 10 + *s++ - '0';
    return n;
}

