#pragma once

#include "types.h"

void *memset(void *buf, char c, size_t n);

void *memcpy(void *dst, const void *src, size_t n);

int memcmp(const void *, const void *, size_t);

int strlen(const char *);

int strncmp(const char *, const char *, size_t);

char *strncpy(char *, const char *, int);

int printf(char *fmt, ...);

void readline(char *buf, int buf_size);

int atoi(const char*);
