#include "pico/time.h"

static uint64_t uSecs() {
    return time_us_64();
}
static uint32_t mSecs() {
    return time_us_64() / 1000;
}
