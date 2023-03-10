#include "clock.h"

#include <unistd.h>

void wait(uint32_t cycles) {
    usleep(cycles * 50000);
}
