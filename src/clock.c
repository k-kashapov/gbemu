#include "clock.h"

#include <time.h>
int nanosleep(const struct timespec *req, struct timespec *rem);

void wait(uint32_t cycles) {
    struct timespec req = {.tv_sec = 0, .tv_nsec = cycles * 50000000};
    nanosleep(&req, NULL);
}
