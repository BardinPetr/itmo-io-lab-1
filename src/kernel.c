#include "kernel.h"
#include "libc.h"

void kernel_main(void) {
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

    printf("Boot done\n");

    main();
    printf("panic\n");
    for (;;);
}

