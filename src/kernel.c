#include "kernel.h"
#include "libc.h"
#include "sbi.h"

void kernel_main(void) {
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);
    const char *s = "\n\nHello World!\n";

    for (int i = 0; s[i] != '\0'; i++) {
        putchar(s[i]);
    }

    for (;;) {
        long c = getchar();
        putchar(c);
        putchar(c - ('a'-'A'));
    }
}

