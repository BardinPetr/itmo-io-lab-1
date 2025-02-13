#define NBUF 32
#include "libc.h"
#include "sbi.h"

void cmd_version() {
    uint32_t v = sbi_get_impl_version();
    printf("SBI version: 0x%x\n", v);
}

void cmd_hart_status(uint32_t i) {
    uint32_t res = sbi_hart_get_status(i);
    if (res == -1)
        printf("hart %d status: error\n", i);
    else
        printf("hart %d status: %d text: %s\n", i, res, hart_status_names[res]);
}

void cmd_hart_stop() {
    printf("stopping hart\n");
    sbi_hart_stop();
}

void cmd_shutdown() {
    printf("doing shutdown\n");
    sbi_shutdown();
}

void main() {
    while (1) {
        printf("> ");
        char cmd[NBUF];
        readline(cmd, NBUF);
        if (strncmp(cmd, "version", NBUF) == 0) {
            cmd_version();
        } else if (strncmp(cmd, "status", NBUF) == 0) {
            printf("hart# > ");
            char hart_id[NBUF];
            readline(hart_id, NBUF);
            int id = atoi(hart_id);
            cmd_hart_status(id);
        } else if (strncmp(cmd, "stop", NBUF) == 0) {
            cmd_hart_stop();
        } else if (strncmp(cmd, "shutdown", NBUF) == 0) {
            cmd_shutdown();
        } else {
            printf("commands: version, status, stop, shutdown\n");
        }
    }
}
