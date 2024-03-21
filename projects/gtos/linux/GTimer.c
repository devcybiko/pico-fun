#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

uint64_t uSecs() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (uint64_t)tp.tv_sec * 1000000 + (uint64_t)tp.tv_nsec / 1000;
}
uint32_t mSecs() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    uint32_t msecs =  (uint64_t)tp.tv_sec * 1000 + (uint64_t)tp.tv_nsec / 1000000;
    return msecs;
}
