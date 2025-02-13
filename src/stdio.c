#include "sbi.h"
#include "libc.h"

void readline(char *buf, int buf_size) {
    char c;
    while (--buf_size > 0 && (c = getchar()) != '\r') {
        *(buf++) = c;
        putchar(c);
    }
    putchar('\n');
    *buf = 0;
}
