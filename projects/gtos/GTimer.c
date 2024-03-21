#include "GTimer.h"

#ifdef __PICO__
#include "pico/GTimer.c"
#endif
#ifdef __LINUX__
#include "linux/GTimer.c"
#endif

_GTimer GTimer = {
    .uSecs = uSecs,
    .mSecs = mSecs,
};
