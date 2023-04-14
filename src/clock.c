#include "clock.h"

#include <time.h>

#define CYCLE_TIME_NANO ((1000000000 / CPU_FREQ) * TIME_SCALE)

void wait(uint32_t cycles) {
    struct timespec req = {.tv_sec = 0, .tv_nsec = cycles * CYCLE_TIME_NANO};
    nanosleep(&req, NULL);
}
