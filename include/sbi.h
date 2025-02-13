#pragma once

struct sbiret {
    long error;
    long value;
};

typedef struct sbiret sbiret_t;

void putchar(char ch);
char getchar();
