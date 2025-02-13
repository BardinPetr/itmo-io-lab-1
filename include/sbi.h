#pragma once

#include "types.h"

struct sbiret {
    uint32_t error;
    uint32_t value;
};

typedef struct sbiret sbiret_t;

void putchar(char ch);

char getchar();

uint32_t sbi_get_impl_version();

uint32_t sbi_hart_get_status(uint32_t hartid);

void sbi_hart_stop();

void sbi_shutdown();

static const char *hart_status_names[] = {
    [0] = "STARTED",
    [1] = "STOPPED",
    [2] = "START_PENDING",
    [3] = "STOP_PENDING",
    [4] = "SUSPENDED",
    [5] = "SUSPEND_PENDING",
    [6] = "RESUME_PENDING"
};
