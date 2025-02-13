#include "sbi.h"
#include "libc.h"

sbiret_t sbi_call(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5,
                  uint32_t fid, uint32_t eid) {
    register uint32_t a0 __asm__("a0") = arg0;
    register uint32_t a1 __asm__("a1") = arg1;
    register uint32_t a2 __asm__("a2") = arg2;
    register uint32_t a3 __asm__("a3") = arg3;
    register uint32_t a4 __asm__("a4") = arg4;
    register uint32_t a5 __asm__("a5") = arg5;
    register uint32_t a6 __asm__("a6") = fid;
    register uint32_t a7 __asm__("a7") = eid;

    __asm__ __volatile__("ecall"
        : "=r"(a0), "=r"(a1)
        : "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(a6), "r"(a7)
        : "memory");
    return (sbiret_t){.error = a0, .value = a1};
}

void putchar(const char ch) {
    sbi_call(ch, 0, 0, 0, 0, 0, 0, 1);
}

static int32_t getch() {
    return sbi_call(0, 0, 0, 0, 0, 0, 0, 2).error;
}

char getchar() {
    int32_t ch;
    while ((ch = getch()) < 0);
    return ch;
}

uint32_t sbi_get_impl_version() {
    return sbi_call(0, 0, 0, 0, 0, 0, 2, 0x10).value;
}

uint32_t sbi_hart_get_status(uint32_t hartid) {
    sbiret_t ret = sbi_call(hartid, 0, 0, 0, 0, 0, 2, 0x48534D);
    if (ret.error != 0) return -1;
    return ret.value;
}

void sbi_hart_stop() {
    sbi_call(0, 0, 0, 0, 0, 0, 1, 0x48534D);
}

void sbi_shutdown() {
    sbi_call(0, 0, 0, 0, 0, 0, 0, 0x08);
}
