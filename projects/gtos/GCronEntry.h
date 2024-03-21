#ifndef __GCronEntry__
#define __GCronEntry__

#include "GObj.h"

// echo -n "ctry" | xxd -ps
// 63747279
#define GCronEntry_ID 0x63747279

#define GCronEntry_MEMBERS(Obj, SuperObj) \
    int (*callback)(struct GCronEntry *); \
    int msRepeat; \
    int msLast; \
    int flags; \
    void *context;

#define GCronEntry_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id, int msRepeat, FUNC(int, callback, GCronEntry*), void* context);

#define GCronEntry_METHODS(Obj, SuperObj)

CLASS(GCronEntry, GObj)

#define GCronEntryFlag_Enabled 1
extern GCronEntry *GCronEntry_new(int msRepeat, int (*callback)(), void *context);

#endif // __GCronEntry__
