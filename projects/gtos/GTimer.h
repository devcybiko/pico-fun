#ifndef __Timer__
#define __Timer__

#include "GDefines.h"

typedef struct _GTimer {
    uint64_t (*uSecs)();
    uint32_t (*mSecs)();
} _GTimer;

extern _GTimer GTimer;

#endif // __Timer__
